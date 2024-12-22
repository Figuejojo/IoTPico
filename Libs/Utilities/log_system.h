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

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "hardware/uart.h"

/*******************************************************************************
* Type definitions
*******************************************************************************/

/**
 * @enum log_level_t
 * @brief Enumeration for log levels.
 */
typedef enum 
{
    LOG_LEVEL_DEBUG, /**< Debug log level. */
    LOG_LEVEL_INFO,  /**< Info log level. */
    LOG_LEVEL_WARN,  /**< Warning log level. */
    LOG_LEVEL_ERROR, /**< Error log level. */
    LOG_LEVEL_FATAL  /**< Fatal log level. */
} log_level_t;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief Initializes the logging system.
 *
 * Sets up resources such as the queue and UART for output.
 */
void log_init(void);

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
