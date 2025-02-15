/** @file AM2320.h
 *  @brief AM2320. Temperature and humidity sensor.
 *
 *  @author Jose Jorge Figueroa Figueroa
 */

 #ifndef _AM2320_H_
 #define _AM2320_H_
 
 /*******************************************************************************
 * Includes
 *******************************************************************************/
 #include "lib_common.h"
 #include "hardware/i2c.h"
 
 /*******************************************************************************
 * Macro Definitions
 *******************************************************************************/
 #define AM_CYCLE_T  (10000)  /*!< Data Collection time[ms] */
 #define AM_QUEUE_SZ (5)     /*!< SensorData Queue Element size */

 #define AM_ADR      (0x5C)   /*!< AM2320 I2C ADDRESS  0xB8  5C*/
 #define AM_I2C0_FRQ (100000) /*!< I2C bus frequency in 100K Hz for std mode */
 //I2C AM2320 Defaults
 #define AM_I2C      (i2c0)  /*!< I2C channel */
 #define AM_I2C0_SDA (12)    /*!< Raspberry Pi Pico Pin for SDA */ 
 #define AM_I2C0_SCL (13)    /*!< Raspberry Pi Pico Pin for SCL */
 
 
 /*******************************************************************************
 * Type definitions
 *******************************************************************************/
 /**
 * @name AmData_t
 * @type enum
 * @brief AM2320 Sensor structure
 */
typedef struct AmData
{
/*@{*/
    float Temp;
    float Hum;
/*@}*/
}AmData_t;

 /*******************************************************************************
 * Function Prototypes
 *******************************************************************************/
/** @name 	geAM2320Val
 *	@brief 	Get sensor data when ready (Temperature and Humidity sensor)
 *
 *  @param 	AmData_t* ptr to Sen0515 data values
 *  @return bool True is values where found, False otherwise.
 */
bool geAM2320Val(AmData_t * pAmSen);

/** @name 	vTaskAM2320
 *	@brief 	Task fro the AM2320 module (Temperature and Humidity sensor)
 *
 *  @param  Void
 *  @return Void
 */
void vTaskAM2320(void * pvParameters);

/** @name 	vSetupAM2320
 *   @brief Setup the i2C1 for the AM2320
 *              - Pico I2C Pin setup.
 *              - Pico I2C Frequency setup as define above.
 *
 *   @param  Void
 *   @return Void
 */
void vSetupAM2320(i2c_inst_t * nI2C, uint8_t pinSDA, uint8_t pinSDL);
 
#endif //_AM2320_H_
 