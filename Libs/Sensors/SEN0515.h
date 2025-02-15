/** @file SEN0515.h
 *  @brief TVOC and CO2 sensor
 *         - SEN0515/ENS160 file for collecting TVOC and CO2 data.
 *         - This file contains the task, and static functions declarations,
 *              macro definitions and the machine states
 *         - The behaviour of the sensor is handle throughout a state machine.
 *         - The data collection is thru the I2C protocol.
 *
 *  @author Jose Jorge Figueroa Figueroa
 */

#ifndef _SEN0515_H_
#define _SEN0515_H_

/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "lib_common.h"
#include "hardware/i2c.h"

/*******************************************************************************
 * Macro Definitions
 *******************************************************************************/
#define ENS_CYCLE_T   (30000)/*!< Data collection time [ms] (Normal Mode) */
#define SEN_QUEUE_SZ  (5)   /*!< SensorData Queue Element size */

#define ENS_I2C_ADDR  (0x53)
/* Default i2c coinfiguration*/
#define ENS_I2C       (i2c1)/*!< I2c channel */
#define ENS_I2C1_SDA  (18)  /*!< Raspberry Pi Pico Pin for TXD */
#define ENS_I2C1_SCL  (19)  /*!< Raspberry Pi Pico Pin for RXD */
#define ENS_I2C1_FREQ (100000) /*!< I2C bus frequency in Hz 100K for Std mode. */

/*******************************************************************************
 * Type definitions
 *******************************************************************************/
/**
 * @name E_ENS_STATES
 * @type enum
 * @brief States for the ENS sensor state machine.
 */
typedef enum ENS_States
{
/*@{*/
    EENS_CHECK_ID = 0,  /*!< Initial State, Check ID */
    EENS_CHECK_ST = 1,  /*!< Sensor State Check      */
    EENS_NORMAL   = 2,  /*!< Normal Sensor State     */
    EENS_END,           /*!< End of States           */
/*@}*/
}E_ENS_STATES;

typedef struct EnsData
{
    float Co2;
    float Tvoc;
}EnsData_t;

/*******************************************************************************
 * Function Prototypes
 *******************************************************************************/
/** @name 	setupSEN0515
 *   @brief  Setup the i2C1 for the SEN0515/ENS160
 *              - Pico I2C Pin setup.
 *              - Pico I2C Frequency setup as define above.
 *
 *   @param 	Void
 *   @return Void
 */
void vSetupSEN0515(i2c_inst_t * nI2C, uint8_t pinSDA, uint8_t pinSDL);

/** @name 	getSEN0515Val
 *   @brief  Get collected values from SEN0515 task.
 *
 *   @param EnsData_t* ptr to Sen0515 data values. 
 *   @return bool True is values where found, False otherwise.
 */
bool getSEN0515Val(EnsData_t * pSen);

/** @name 	vTaskSEN0515
 *   @brief  Collect data from the SEN0515/ENS160 sensor
 *               - Every \ref ENS_CYCLE_T
 *               - Send data out by using the process task. 
 *
 *   @param 	Void * parameters
 *   @return Void
 */
void vTaskSEN0515(void * pvParameters);

#endif //_SEN0515_H_
