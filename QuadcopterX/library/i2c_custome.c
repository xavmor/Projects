#include "i2c_custome.h"
#include "driverlib/gpio.h"

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


void i2cWriteData(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length)
{
    I2C_setSlaveAddress(I2CmoduleInstance, addr);
    I2C_setMode(I2CmoduleInstance, EUSCI_B_I2C_TRANSMIT_MODE);  // Master in transmit mode

    /* Initiate start and send register address */
    I2C_masterSendMultiByteStart(I2CmoduleInstance, regAddr);

    int i;
    for (i = 0; i < length; i++)
    {
        I2C_masterSendMultiByteNext(I2CmoduleInstance, data[i]);
    }

    I2C_masterSendMultiByteStop(I2CmoduleInstance);
}


void i2cInit()
{
    //
    // Step 1: Initialize SDA and SCL Pins
    //

    // Using Pins 1.6 and 1.7, SDA and SCL respectively
    if (I2CmoduleInstance == EUSCI_B0_BASE)
    {
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN6,
                                                    GPIO_PRIMARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN7,
                                                    GPIO_PRIMARY_MODULE_FUNCTION);
    }
        // Using Pins 6.4 and 6.5, SDA and SCL respectively
    else if (I2CmoduleInstance == EUSCI_B1_BASE)
    {
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN4,
                                                    GPIO_PRIMARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN5,
                                                    GPIO_PRIMARY_MODULE_FUNCTION);
    }
    // Using pins 3.6 and 3.7, SDA and SCL respectively
    else if (I2CmoduleInstance == EUSCI_B2_BASE)
    {
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN6,
                                                            GPIO_PRIMARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN7,
                                                            GPIO_PRIMARY_MODULE_FUNCTION);
    }
    // Default to port 10 pins 2 and 3, SDA and SCL respectively
    else
    {
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10, GPIO_PIN2,
                                                            GPIO_PRIMARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10, GPIO_PIN3,
                                                            GPIO_PRIMARY_MODULE_FUNCTION);
    }

    //
    // Step 2: Set eusci stuff
    //
    I2C_disableModule(I2CmoduleInstance);
    I2C_initMaster(I2CmoduleInstance, &i2cConfig);
    I2C_enableModule(I2CmoduleInstance);
}
