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

    //*** Queues Creation and setup ***/ 

    /*** FreeRTOS tASKS ***/
    xTaskCreate(TaskLEDBlinkvoid,"Ledblink",256,NULL,2,NULL);

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
    int8_t msg[] = "DebugCycleYES";
    while(true)
    {
        vTaskDelay(2500/portTICK_PERIOD_MS);
        gpio_put(LED_PIN,1);
        vTaskDelay(2500/portTICK_PERIOD_MS);
        gpio_put(LED_PIN,0);
    }
}