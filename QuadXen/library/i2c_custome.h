//#include <stdint.h>
//#include <stdbool.h>
//#include "ti/devices/msp432p4xx/driverlib/i2c.h"

#ifndef __i2c_custome_h__
#define __i2c_custome_h__

//
//#define I2CmoduleInstance    EUSCI_B1_BASE
//
//
//
//// Struct that we will use for I2C configuration
//eUSCI_I2C_MasterConfig i2cConfig =
//{
//    EUSCI_B_I2C_CLOCKSOURCE_SMCLK,          // Clock that we will source from
//    12000000,                                // Desired System Clock Rate 3MHz
//    EUSCI_B_I2C_SET_DATA_RATE_400KBPS,      // Desired I2C Clock Rate
//    0,                                      // No byte counter threshold
//    EUSCI_B_I2C_NO_AUTO_STOP                // No Autostop
//};
//
//
///* Read data using I2C protocol
// *
// * Parameters:
// *  addr -> address of I2C device
// *  regAddr -> address of register found in the I2C device
// *  *data -> array to store data in
// *  length -> # of times we will read from I2C device
// *
// */
//void i2cReadData(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length);
//
//
///* Writes data using I2C protocol
// *
// * Parameters:
// *  addr -> address of I2C device
// *  regAddr -> address of register found in the I2C device
// *  data -> array with data to write into I2C device
// *  length -> # of times we will write to I2C device / size of *data
// *
// */
//void i2cWriteData(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length);
//
//
///* Initializes I2C module
// *
// * Note:
// *      To change module base, there are 4 bases, simply edit the
// *      #define I2CmoduleInstance    EUSCI_B1_BASE valid options are
// *      EUSCI_B0_BASE, EUSCI_B1_BASE, EUSCI_B2_BASE, EUSCI_B3_BASE
// *
// */
//void i2cInit();


#endif  // __i2c_custome_h__
