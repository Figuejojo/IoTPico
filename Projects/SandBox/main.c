/** @file Main.c
 *  @brief This is the main file of the Smart Air Pollution Monitor.
 *
 *  @author Jose Jorge Figueroa Figueroa
 */
/*******************************************************************************
* Includes
*******************************************************************************/
#include "log_system.h"
#include "SEN0515.h"

/*******************************************************************************
* Static Global Variables
*******************************************************************************/


/*******************************************************************************
* Function Declaration
*******************************************************************************/
void vTaskLEDBlinkvoid(void * pvParameters);
void vTaskSensorTest(void * pvParameters);
/*******************************************************************************
* Function Definition
*******************************************************************************/

/**
  * @name main
  * @Type Main Function
*/
int main() 
{
    //*** Hardware Initializations (If needed) ***/
    stdio_init_all();
    log_init(uart0,LOG_TX,LOG_RX);
    log_message(LOG_LEVEL_DEBUG,"Starting...");

    //** Peripherals setup **//
    vSetupSEN0515(ENS_I2C,ENS_I2C1_SDA,ENS_I2C1_SCL);

    //*** Queues Creation and setup ***/ 

    /*** FreeRTOS tASKS ***/
    // Lib Tasks
    xTaskCreate(TaskLoggingVoid,"Logging",256,NULL,2,NULL); // Recommended for debugging
    xTaskCreate(vTaskSEN0515,"AM2320",256,NULL,2,NULL);     // SEN0515 Sensor.

    // Tasks for this project.
    xTaskCreate(vTaskLEDBlinkvoid,"Ledblink",256,NULL,2,NULL);
    xTaskCreate(vTaskSensorTest,"SensorTest",256,NULL,2,NULL);

    /*Start FreeRTOS Scheduler */
    log_message(LOG_LEVEL_DEBUG,"FreeRTOS Boot-up");
    vTaskStartScheduler();
    
    while(1);
}

/*
 * @name Debug_LEDBlink 
 * @Type Example Task
*/
void vTaskLEDBlinkvoid(void * pvParameters)
{
    const uint8_t LED_PIN = 3;

    //Ideally these gpio functions should be in a the peripheral setup
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    int8_t msg[4] = "ON";
    uint8_t LedState = 0;
    while(true)
    {
        vTaskDelay(2000/portTICK_PERIOD_MS);
        gpio_put(LED_PIN,LedState);
        if(LedState == 1)
        {
            LedState = 0;
            strcpy(msg,"ON");
        }
        else
        {
            LedState = 1;
            strcpy(msg,"OFF");
        }
    }
}

void vTaskSensorTest(void * pvParameters)
{
    EnsData_t SenVal = {0};
    while(true)
    {
        vTaskDelay(30100/portTICK_PERIOD_MS);
        if(getSEN0515Val(&SenVal))
        {
            log_message(LOG_LEVEL_DEBUG,"Co2: %0.2f \tTVOC: %0.2f",SenVal.Co2,SenVal.Tvoc);
        }
        else
        {
            log_message(LOG_LEVEL_WARN,"Sensor is not Updating");
        }
    }
}