/** @file  AM2320.c
 *  @brief AM2320 - Temperature and humidity sensor.
 *
 *  @author Jose Jorge Figueroa Figueroa
 */
/*******************************************************************************
* Includes
*******************************************************************************/
#include "AM2320.h"

/*******************************************************************************
* Static Global Variables
*******************************************************************************/
static QueueHandle_t sgqAm2320Data; /*!< SensorData FreeRTOS Queue */

/*******************************************************************************
* Static Function Declarations
*******************************************************************************/
/** @name 	bCheckCRC16
 *  @brief  statcic function to only be used in this file.
 *             - Calculate the 16bit CRC according to the Datasheet.
 *               
 *  @param  Void
 *  @return 16bit CRC calculation 
 */
static uint16_t bCheckCRC16(const uint8_t * ptrBuff, uint8_t lenBuff);

/*******************************************************************************
* Function Definition
*******************************************************************************/
/** @name 	getSEN0515Val
 *	@brief 	Get sensor data when ready (Temperature and Humidity sensor)
 *
 *  @param 	AmData_t* ptr to Sen0515 data values
 *  @return bool True is values where found, False otherwise.
 */
bool geAM2320Val(AmData_t * pAmSen)
{   
    AmData_t AmValues = {0};
    if(xQueueReceive(sgqAm2320Data,&AmValues,0))
    {
        pAmSen->Hum  = AmValues.Hum;
        pAmSen->Temp = AmValues.Temp;
        return true;
    }
    return false;
}

/**
 *	@name vTaskAM2320
 *  @Type void Task 
 */
void vTaskAM2320(void * pvParameters)
{
    const uint8_t readCmd[] = {0x03,0x00,0x04};
    const uint8_t wakeCmd = 0x00;
    AmData_t sAM = {0};
    while(true)
    {
        uint8_t cbuff[8] = {0};
        int state = PICO_OK;
        taskENTER_CRITICAL();
        // Wake-up device
        i2c_write_blocking(AM_I2C,AM_ADR,&wakeCmd,1,true);
        // Read four registers starting from zero.
        state |= i2c_write_blocking(AM_I2C,AM_ADR,readCmd,3,false);
        // Get readings. 
        state |= i2c_read_blocking(AM_I2C,AM_ADR,cbuff,8,false);
        taskEXIT_CRITICAL();

        if(PICO_OK <= state)
        {
            uint16_t CRC = cbuff[7]<<8|cbuff[6];
            if(CRC == bCheckCRC16(cbuff,sizeof(cbuff)-2))
            {
                sAM.Hum = (cbuff[2]<<8|cbuff[3])/10.0;
                sAM.Temp = (cbuff[4]<<8|cbuff[5])/10.0;   
                xQueueSendToBack(sgqAm2320Data,&sAM,0);
            }
        }
        vTaskDelay(AM_CYCLE_T/portTICK_PERIOD_MS);
    }
}

/**
 *	@name  vSetupAM2320
 *  @Type  function
 */
void vSetupAM2320(i2c_inst_t * nI2C, uint8_t pinSDA, uint8_t pinSDL)
{
    // Initialize the I2C peripheral for the AM2320
    i2c_init(nI2C, AM_I2C0_FRQ);

    // Initialize the GPIO peripherals in I2C mode.
    gpio_set_function(pinSDA, GPIO_FUNC_I2C);
    gpio_set_function(pinSDL, GPIO_FUNC_I2C);
    gpio_pull_up(pinSDA);
    gpio_pull_up(pinSDL);
    sgqAm2320Data = xQueueCreate(AM_QUEUE_SZ, sizeof(AmData_t));
}

static uint16_t bCheckCRC16(const uint8_t * ptrBuff, uint8_t lenBuff)
{
    uint16_t crc = 0xFFFF;
    uint8_t sizeBuff = lenBuff;
    while (sizeBuff--)
    {
        crc ^= *ptrBuff++;
        for(int idxBuff = 0; idxBuff < 8; idxBuff++)
        {
            if(crc & 0x01)
            {
                crc >>= 1;
                crc ^= 0xA001; //Datasheet value for CRC calculation.
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}
