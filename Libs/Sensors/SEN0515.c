/** @file sen0515.c
 *  @brief TVOC and CO2 sensor
 *         - SEN0515/ENS160 file for collecting TVOC and CO2 data.
 *         - This file contains the task, and static functions definition.
 *         - The behaviour of the sensor is handle throughout a state machine.
 *         - The data collection is thru the I2C protocol.
 * 
 *  @author Jose Jorge Figueroa Figueroa
 */
/*******************************************************************************
* Includes
*******************************************************************************/
#include "SEN0515.h"

/*******************************************************************************
* Static Global Variables
*******************************************************************************/
#define ENS_CMD_ID  (0x00)  /*!< ENS Command ID Register */
#define ENS_OPM_MD  (0x10)  /*!< Opeation Mode Register  */
#define ENS_DATA_S  (0x20)  /*!< Data State Register     */
#define ENS_CAQI_D  (0x21)  /*!< CO2 AirQualityIndex Reg */
#define ENS_TVOC_D  (0x22)  /*!< TVOC data register      */
#define ENS_ECO2_D  (0x24)  /*!< ECO2 data register      */

#define ENS_OPM_NOR (0x02)  /*!< Normal Operation Mode */ 

/*******************************************************************************
* Static Global Variables
*******************************************************************************/
static QueueHandle_t sgqSensorData; /*!< SensorData FreeRTOS Queue */

/*******************************************************************************
* Static Function Declarations
*******************************************************************************/
/** @name 	eCheckEnsID
*   @brief  Statuc function to only be used in this file.
*              - This is the initial state function.
*              - Request the sensor ID and verify that is correct.
*              - Returns the next state.
*               
*   @param 	Void
*   @return E_ENS_STATES 
*/
static E_ENS_STATES eCheckEnsID(void);

/** @name 	eCheckEnsST
*   @brief  statcic function to only be used in this file.
*              - Request the sensor State acording to the datasheet:
*                    (WarmUp, Initial Start-Up, Normal Operation).
*              - Returns the next state.
*               
*   @param 	Void
*   @return E_ENS_STATES 
*/
static E_ENS_STATES eCheckEnsST(void);

/** @name 	eGetEnsVal
*   @brief  statcic function to only be used in this file.
*              - Get values from the ENS sensor including:
*                  (TVOC, eCO2) // AQI is possible as well in future implement.
*              - Returns the next state.
*               
*   @param 	ptr to SAPMS_t struct. 
*   @return E_ENS_STATES 
*/
static E_ENS_STATES eGetEnsVal(EnsData_t * pSen);

/*******************************************************************************
* Function Definition
*******************************************************************************/
/**
*	@name getSEN0515Val
*   @type Get sensor values if ready.
*/
bool getSEN0515Val(EnsData_t * pSen)
{   
    EnsData_t EnValues = {0};
    if(xQueueReceive(sgqSensorData,&EnValues,0))
    {
        pSen->Co2 = EnValues.Co2;
        pSen->Tvoc = EnValues.Tvoc;
        return true;
    }
    return false;
}

/**
*	@name vTaskGPS
*   @type Task
*/
void vTaskSEN0515(void * pvParameters)
{
    EnsData_t sSEN = {0};
    uint16_t CycleTimeMs = 1000;
    E_ENS_STATES eEnsState = EENS_CHECK_ID;
    uint8_t msg[25] = {0};
    while(1)
    {
        switch (eEnsState)
        {
            // This is the initial state and check for the ID of the sensor.
            case EENS_CHECK_ID: 
                eEnsState = eCheckEnsID();
                if(eEnsState == EENS_CHECK_ID)
                {
                    CycleTimeMs = 60000;    //If the ID does not match it sleeps for a minute
                }
                break;

            // This state set the operation mode and check for if the sensor state.
            case EENS_CHECK_ST:
                eEnsState = eCheckEnsST();
                //If the sensor is on Warm-up it will loop here and check each minute. 
                //If the sensor is in the First time, it will be called each minute until ready.
                CycleTimeMs = (eEnsState == EENS_NORMAL)?(ENS_CYCLE_T):(60000);
                break;

            case EENS_NORMAL:
                eEnsState = eGetEnsVal(&sSEN);
                if(eEnsState == EENS_NORMAL)
                {
                    if(sSEN.Co2 >= 0 && sSEN.Tvoc >= 0)
                    {
                        xQueueSendToBack(sgqSensorData,&sSEN,0);
                    }
                }
                CycleTimeMs = (ENS_CYCLE_T); 
                break;

            default:
                CycleTimeMs = 1000;
                eEnsState = EENS_CHECK_ID;
                break;
        }
        vTaskDelay(CycleTimeMs/portTICK_PERIOD_MS);
    }
}

/**
*	@name  setupSEN0515
*   @Type  function
*/
void vSetupSEN0515(i2c_inst_t * nI2C, uint8_t pinSDA, uint8_t pinSDL)
{
    i2c_init(nI2C, ENS_I2C1_FREQ);
    gpio_set_function(pinSDA, GPIO_FUNC_I2C);
    gpio_set_function(pinSDL, GPIO_FUNC_I2C);
    gpio_pull_up(pinSDA);
    gpio_pull_up(pinSDL);
    sgqSensorData = xQueueCreate(SEN_QUEUE_SZ, sizeof(EnsData_t));
}

/**
*	@name  eCheckEnsID
*   @Type  static function
*/
E_ENS_STATES eCheckEnsID(void)
{
    uint8_t const IDcmd = ENS_CMD_ID;
    uint8_t cBuff[2] = {0};
    int state = PICO_OK;

    taskENTER_CRITICAL();
    // Request Sensor ID
    state |= i2c_write_blocking(ENS_I2C, ENS_I2C_ADDR, &IDcmd, 1, true);
    state |= i2c_read_blocking(ENS_I2C, ENS_I2C_ADDR, cBuff, 2, false); 
    taskEXIT_CRITICAL();

    if(PICO_OK <= state)
    {  
        if(0x0160 != (cBuff[0]|cBuff[1]<<8))    // Check that the ID match.
        {
            //Print_debug("ENS - No Maching ID");
            return EENS_CHECK_ID;//ER_I2C_ID;
        }
    }
    else
    {
        return EENS_CHECK_ID;//ER_I2C_GEN;
    }
    return EENS_CHECK_ST;
}

/**
*	@name  eCheckEnsST
*   @Type  static function
*/
E_ENS_STATES eCheckEnsST(void)
{
    uint8_t const DScmd = ENS_DATA_S;   // ENS Status.
    uint8_t const OPcmd[2] = {ENS_OPM_MD,ENS_OPM_NOR}; //Opeation state
    uint8_t cBuff[2] = {0};
    uint8_t msg[25];
    int state = PICO_OK;

    taskENTER_CRITICAL();
    //Set the Sensor to normal operation state 
    state |= i2c_write_blocking(ENS_I2C, ENS_I2C_ADDR, OPcmd, 2, false);
    state |= i2c_write_blocking(ENS_I2C, ENS_I2C_ADDR, OPcmd, 1, true);
    state |= i2c_read_blocking(ENS_I2C, ENS_I2C_ADDR, cBuff, 1, false);
    taskEXIT_CRITICAL();

    // Check for any error on the I2C bus
    if(0 > state)   
    {
        return EENS_CHECK_ID;
    }
    
    // Check if the Opration mode was set to normal.
    if(ENS_OPM_NOR != cBuff[0]) 
    {
        return EENS_CHECK_ST;
    }

    taskENTER_CRITICAL();
    // Request the ENS status 
    state |= i2c_write_blocking(ENS_I2C, ENS_I2C_ADDR, &DScmd, 1, true);    
    state |= i2c_read_blocking(ENS_I2C, ENS_I2C_ADDR, cBuff, 1, false);
    taskEXIT_CRITICAL();

    // Check for any error on the I2C bus
    if(0 > state)   
    {
        return EENS_CHECK_ID;
    }

    // Change if the ENS state is normal. If not it might be on WarmUp or InitialStartUp.
    if(0 == (cBuff[0] & (3u<<2)))
    {
        return EENS_NORMAL;
    }

    return EENS_CHECK_ST;
}

/**
*	@name  eGetEnsVal
*   @Type  static function
*/
E_ENS_STATES eGetEnsVal(EnsData_t * pSen)
{
    const uint8_t cmdCO2 = ENS_ECO2_D;
    const uint8_t cmdTVOC= ENS_TVOC_D;
    uint8_t cBuff[2] = {0};
    int state = PICO_OK;

    taskENTER_CRITICAL();
    // Get CO2
    state = i2c_write_blocking(ENS_I2C, ENS_I2C_ADDR, &cmdCO2, 1, true);
    state|= i2c_read_blocking(ENS_I2C, ENS_I2C_ADDR, cBuff, 2, false);
    pSen->Co2 = (0<=state) ? (cBuff[0]|(cBuff[1]<<8u)) : (-1);

    // Get TVOC
    state = i2c_write_blocking(ENS_I2C, ENS_I2C_ADDR, &cmdTVOC, 1, true);
    state|= i2c_read_blocking(ENS_I2C, ENS_I2C_ADDR, cBuff, 2, false);
    pSen->Tvoc = (0<=state) ? (cBuff[0]|(cBuff[1]<<8u)) : (-1);
    taskEXIT_CRITICAL();

    if(PICO_OK > state)
    {
        return EENS_CHECK_ID;
    }
    return EENS_NORMAL;
}

