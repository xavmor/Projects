#include "i2c_custome.h"
#include "driverlib/i2c.h"

void i2cReadData(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length)
{
    // TODO: Does the module need to be reseted???
    I2C_setSlaveAddress(I2CmoduleInstance, addr);
    I2C_setMode(I2CmoduleInstance, EUSCI_B_I2C_TRANSMIT_MODE);  // Master in transmit mode
    I2C_masterSendSingleByte(I2CmoduleInstance, regAddr);
    I2C_setMode(I2CmoduleInstance, EUSCI_B_I2C_RECEIVE_MODE);   // Master in receive mode

    I2C_masterReceiveStart(I2CmoduleInstance);  // Initiate reading I2C slave device

    // TODO: will this read one byte or only multiple bytes???
    uint8_t i;
    for (i = 0; i < length; i++)
    {
        data[i] = I2C_masterReceiveMultiByteNext(I2CmoduleInstance);    // Read from slave
    }

    I2C_masterReceiveMultiByteStop(I2CmoduleInstance);  // Stop reading from I2C slave
}
