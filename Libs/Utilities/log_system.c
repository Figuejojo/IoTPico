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
// Define the debug log messages
const static uint8_t *LOG_LEVEL[] = {"[DEBUG]","[INFO]","[WARN]" ,"[ERROR]", "[FATAL]"};
// Define the debug log errors
const static uint8_t *LOG_ERR[] =  {"INVALID","MSGLEN"};
// UART interface
static uart_inst_t *LogUart = NULL;

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
    char message[MSG_LEN]; /**< The formatted log message. */
} log_message_t;

void log_init(uart_inst_t *pUart, uint8_t pinTX, uint8_t pinRX)
{
    // Initialize the UART and the log queue
    LogUart = pUart;
    uart_init(LogUart, 115200);
    gpio_set_function(pinTX, GPIO_FUNC_UART);
    gpio_set_function(pinRX, GPIO_FUNC_UART);
    log_queue = xQueueCreate(10, sizeof(log_message_t));
}

void log_message(log_level_t level, const char *format, ...) 
{
    log_message_t log = {0};
    //@TODO: Add message length check
    if(level >= LOG_LEVEL_DEBUG && level <= LOG_LEVEL_FATAL)
    {
        log.level = level;
        // Format the message using variadic arguments
        va_list args;
        va_start(args, format);
        vsnprintf(log.message, sizeof(log.message), format, args);
        va_end(args);
        if(sizeof(log.message) > MSG_LEN)
        {
            log.level = LOG_ERR_MSGLEN;
        }
    }
    else
    {
        log.level = LOG_ERR_INVALID;
    }
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
            // Check if the log level is valid.
            switch(log.level)
            {
                case LOG_ERR_MSGLEN:
                case LOG_ERR_INVALID:
                    uart_puts(LogUart,LOG_ERR[log.level - LOG_ERR_MSGLEN]);
                    break;
                case LOG_LEVEL_DEBUG:
                case LOG_LEVEL_INFO:
                case LOG_LEVEL_WARN:
                case LOG_LEVEL_ERROR:
                case LOG_LEVEL_FATAL: 
                    uart_puts(LogUart, LOG_LEVEL[log.level]);
                    uart_puts(LogUart, log.message);
                    break;
                default:
                    uart_puts(LogUart,"Invalid Log ENUM");
                    break;
            }
            uart_puts(LogUart, "\r\n");
        }
    }
}