#ifndef __i2c_custome_h__
#define __i2c_custome_h__

#include <stdint.h>
#include <stdbool.h>


#define I2CmoduleInstance    EUSCI_B1_BASE


/* Read data using I2C protocol
 *
 * Parameters:
 *  addr -> address of I2C device
 *  regAddr -> address of register found in the I2C device
 *  *data -> array to store data in
 *  length -> # of times we will read from I2C device
 *
 */
void i2cReadData(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length);


#endif  // __i2c_custome_h__
