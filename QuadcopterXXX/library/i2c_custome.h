#ifndef __i2c_custome_h__
#define __i2c_custome_h__

#include <stdint.h>
//#include <stdbool.h>

uint8_t I2CReadSingleByte(uint32_t moduleInstance, uint8_t regAddr);
void I2CReadMultipleByte(uint32_t moduleInstance, uint8_t regAddr, uint8_t * data, uint8_t length);
void I2CWriteSingalByte(uint32_t moduleInstance, uint8_t regAddr, uint8_t data);
void I2CWriteMultipleByte(uint32_t moduleInstance, uint8_t regAddr, uint8_t *data, uint8_t length);


/* Initializes I2C module
 *
 * Note:
 *      To change module base, there are 4 bases, simply edit the
 *      #define I2CmoduleInstance    EUSCI_B1_BASE valid options are
 *      EUSCI_B0_BASE, EUSCI_B1_BASE, EUSCI_B2_BASE, EUSCI_B3_BASE
 *
 */
void i2cInit(uint32_t moduleInstance);


#endif  // __i2c_custome_h__
