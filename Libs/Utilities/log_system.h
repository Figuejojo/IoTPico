/**
 * @file log_system.h
 * @brief Header file for RTOS-based logging library.
 *
 * This library provides logging functionality for embedded systems
 * running in an RTOS environment. It supports different log levels
 * and output backends.
 */
#ifndef _LOG_SYSTEM_H_
#define _LOG_SYSTEM_H_

/*******************************************************************************
* Includes
*******************************************************************************/

#include "lib_common.h"

/*******************************************************************************
* Macro Definitions
*******************************************************************************/

#define MSG_LEN (128)

/*******************************************************************************
* Type definitions
*******************************************************************************/

/**
 * @enum log_level_t
 * @brief Enumeration for log levels.
 */
typedef enum 
{
    LOG_LEVEL_DEBUG  = 0,  /**< Debug log level.   */
    LOG_LEVEL_INFO,        /**< Info log level.    */
    LOG_LEVEL_WARN,        /**< Warning log level. */
    LOG_LEVEL_ERROR,       /**< Error log level.   */
    LOG_LEVEL_FATAL,       /**< Fatal log level.   */
    LOG_LEVEL_END,         /**< End of log levels. */

    // LOG ERRORS
    LOG_ERR_MSGLEN,  /**< Invalid MSG Len.   */
    LOG_ERR_INVALID, /**< Invalid Log level. */
    LOG_ERR_END      /**< End of Log Errors. */
} log_level_t;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief Initializes the logging system.
 *
 * Sets up resources such as the queue and UART for output.
 *
 * @param uart_inst_t* Pointer to specified UART.
 * @param pinTX Specify the pin used for TX.
 * @param pinRX Specify the pin used for RX.
 */
void log_init(uart_inst_t *pUart, uint8_t pinTX, uint8_t pinRX);

/**
 * @brief The logging task to be run in the RTOS environment.
 *
 * This task continuously reads log messages from a queue and outputs
 * them to the appropriate backends.
 *
 * @param pvParameters Task parameters (unused).
 */
void TaskLoggingVoid(void *pvParameters);

/**
 * @brief Logs a message with a specified log level.
 *
 * This function uses variadic arguments to allow flexible formatting.
 *
 * @param level The log level of the message.
 * @param format The format string (similar to printf).
 * @param ... The variadic arguments matching the format string.
 */
void log_message(log_level_t level, const char *format, ...);

#endif //_LOG_SYSTEM_H_
