/** @file Main.c
 *  @brief This is the main file of the Smart Air Pollution Monitor.
 *
 *  @author Jose Jorge Figueroa Figueroa
 */
/*******************************************************************************
* Includes
*******************************************************************************/
#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include "pico/stdlib.h"
#include <string.h>
#include "log_system.h"

/*******************************************************************************
* Static Global Variables
*******************************************************************************/

/*******************************************************************************
* Function Declaration
*******************************************************************************/
void TaskLEDBlinkvoid(void * pvParameters);

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
    log_init();
    //*** Queues Creation and setup ***/ 

    /*** FreeRTOS tASKS ***/
    xTaskCreate(TaskLEDBlinkvoid,"Ledblink",256,NULL,2,NULL);
    xTaskCreate(TaskLoggingVoid,"Logging",256,NULL,2,NULL);
    /*Start FreeRTOS Scheduler */
    vTaskStartScheduler();
    
    while(1);
}

/*
 * @name Debug_LEDBlink 
 * @Type Example Task
*/
void TaskLEDBlinkvoid(void * pvParameters)
{
    const uint8_t LED_PIN = 3;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    int8_t msg[4] = "OFF";
    uint8_t LedState = 0;
    while(true)
    {
        log_message(LOG_LEVEL_DEBUG,"Debug: %s/n",msg);
        vTaskDelay(2500/portTICK_PERIOD_MS);
        gpio_put(LED_PIN,LedState);
        if(LedState == 1)
        {
            LedState = 0;
            strcpy(msg,"OFF");
        }
        else
        {
            LedState = 1;
            strcpy(msg,"ON");
        }
    }
}
