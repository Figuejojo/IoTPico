/**
 * @file lib_common.h
 * @brief Header file for the common utilities library.
 *
 * This library provides logging functionality for embedded systems
 * running in an RTOS environment. It supports different log levels
 * and output backends.
 */
#ifndef _LIB_COMMON_H_
#define _LIB_COMMON_H_

/*******************************************************************************
* Includes
*******************************************************************************/
// Standard Libraries
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
// Pico Libraries
#include "pico/stdlib.h"
#include "hardware/uart.h"
// RTOS Libraries
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#endif
