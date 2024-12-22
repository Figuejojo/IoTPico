/**
 * @file rtos_logger.c
 * @brief Implementation file for RTOS-based logging library.
 */

/*******************************************************************************
* Includes
*******************************************************************************/
#include "log_system.h"

/*******************************************************************************
* Static Global Variables
*******************************************************************************/

// Define a queue for log messages
static QueueHandle_t log_queue;

/*******************************************************************************
* Function Definition
*******************************************************************************/

/**
 * @struct log_message_t
 * @brief Structure representing a log message.
 */
typedef struct 
{
    log_level_t level; /**< The log level of the message. */
    char message[128]; /**< The formatted log message. */
} log_message_t;

void log_init(void) 
{
    // Initialize the UART and the log queue
    uart_init(uart0, 115200);
    log_queue = xQueueCreate(10, sizeof(log_message_t));
}

void log_message(log_level_t level, const char *format, ...) 
{
    log_message_t log;
    log.level = level;

    // Format the message using variadic arguments
    va_list args;
    va_start(args, format);
    vsnprintf(log.message, sizeof(log.message), format, args);
    va_end(args);

    // Send the log message to the queue
    xQueueSend(log_queue, &log, portMAX_DELAY);
}

void TaskLoggingVoid(void *pvParameters) 
{
    log_message_t log;
    while (true) 
    {
        // Receive a log message from the queue
        if (xQueueReceive(log_queue, &log, portMAX_DELAY)) 
        {
            // Output the log message to UART
            uart_puts(uart0, log.message);
            uart_puts(uart0, "\n");
        }
    }
}