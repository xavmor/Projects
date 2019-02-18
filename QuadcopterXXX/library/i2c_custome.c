#include "i2c_custome.h"
#include "driverlib/gpio.h"
#include "ti/devices/msp432p4xx/driverlib/i2c.h"



// Struct that we will use for I2C configuration
eUSCI_I2C_MasterConfig i2cConfig =
{
    EUSCI_B_I2C_CLOCKSOURCE_SMCLK,          // Clock that we will source from
    12000000,                                // Desired System Clock Rate 3MHz
    EUSCI_B_I2C_SET_DATA_RATE_400KBPS,      // Desired I2C Clock Rate
    0,                                      // No byte counter threshold
    EUSCI_B_I2C_NO_AUTO_STOP                // No Autostop
};



/******************************************************************************
 * Description: Initializes the I2C module on the MSP432.
 *
 * Parameters:
 *      moduelInstance ->   indicates the I2C module that will be used
 *                           appropriate values are one of the following:
 *                           EUSCI_B0_BASE,
 *                           EUSCI_B1_BASE,
 *                           EUSCI_B2_BASE,
 *                           EUSCI_B3_BASE
 *      regAddr ->  Address of register to read from I2C device
 *
 * Returned:
 *      byte value read from I2C device
 *****************************************************************************/
void i2cInit(uint32_t moduleInstance)
{
    //
    // Step 1: Initialize SDA and SCL Pins
    //

    // Using Pins 1.6 and 1.7, SDA and SCL respectively
    if (moduleInstance == EUSCI_B0_BASE)
    {
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN6,
                                                    GPIO_PRIMARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN7,
                                                    GPIO_PRIMARY_MODULE_FUNCTION);
    }
    // Using Pins 6.4 and 6.5, SDA and SCL respectively
    else if (moduleInstance == EUSCI_B1_BASE)
    {
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN4,
                                                    GPIO_PRIMARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN5,
                                                    GPIO_PRIMARY_MODULE_FUNCTION);
    }
    // Using pins 3.6 and 3.7, SDA and SCL respectively
    else if (moduleInstance == EUSCI_B2_BASE)
    {
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN6,
                                                            GPIO_PRIMARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN7,
                                                            GPIO_PRIMARY_MODULE_FUNCTION);
    }
    // Default to port 10 pins 2 and 3, SDA and SCL respectively
    else if (moduleInstance == EUSCI_B3_BASE)
    {
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10, GPIO_PIN2,
                                                            GPIO_PRIMARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P10, GPIO_PIN3,
                                                            GPIO_PRIMARY_MODULE_FUNCTION);
    }
    else
        while(1);   // Invalid module

    //
    // Step 2: Initialize I2C module
    //

    /* Disable I2C module to make changes */
    I2C_disableModule(moduleInstance);
    I2C_initMaster(moduleInstance, &i2cConfig);
    I2C_enableModule(moduleInstance);
}


/******************************************************************************
 * Description: Reads a single byte of data from some register. Master will
 *      send start bit with write bit+slave address. The master will then send
 *      address of the register it wants to access from the I2C slave. The master
 *      will then send a Repeat signal with read bit+slave address. I2C slave
 *      device will then send data from its register.
 *
 * Parameters:
 *      moduelInstance ->   indicates the I2C module that will be used
 *                           appropriate values are one of the following:
 *                           EUSCI_B0_BASE,
 *                           EUSCI_B1_BASE,
 *                           EUSCI_B2_BASE,
 *                           EUSCI_B3_BASE
 *      regAddr ->  Address of register to read from I2C device
 *
 * Returned:
 *      byte value read from I2C device
 *****************************************************************************/
uint8_t I2CReadSingleByte(uint32_t moduleInstance, uint8_t regAddr)
{
    // Set to Transmit Mode
    EUSCI_B_CMSIS(moduleInstance)->CTLW0 = (EUSCI_B_CMSIS(moduleInstance)->CTLW0
            & (~EUSCI_B_I2C_TRANSMIT_MODE)) | EUSCI_B_I2C_TRANSMIT_MODE;

    // Point to the correct register
    I2C_masterSendSingleByte(moduleInstance, regAddr);

    // Set to Receiver Mode
    EUSCI_B_CMSIS(moduleInstance)->CTLW0 = (EUSCI_B_CMSIS(moduleInstance)->CTLW0
            & (~EUSCI_B_I2C_TRANSMIT_MODE)) | EUSCI_B_I2C_TRANSMIT_MODE;

    //Set USCI in Receive mode
    BITBAND_PERI(EUSCI_B_CMSIS(moduleInstance)->CTLW0, EUSCI_B_CTLW0_TR_OFS) = 0;

    /* The eUSCI_B module checks if the bus is available, generates the START condition,
        and transmits the slave address. */
    EUSCI_B_CMSIS(moduleInstance)->CTLW0 |= (EUSCI_B_CTLW0_TXSTT + EUSCI_B_CTLW0_TXSTP);

    // The UCTXSTT flag is cleared as soon as the complete address is sent.
    // Make sure START/Address was sent
    while(BITBAND_PERI(EUSCI_B_CMSIS(moduleInstance)->CTLW0, EUSCI_B_CTLW0_TXSTT_OFS));

    // Set STOP bit. Note stop will not send until RX is received.
    BITBAND_PERI(EUSCI_B_CMSIS(moduleInstance)->CTLW0, EUSCI_B_CTLW0_TXSTP_OFS) = 1;

    //Poll for receive interrupt flag.
    while (!BITBAND_PERI(EUSCI_B_CMSIS(moduleInstance)->IFG,
            EUSCI_B_IFG_RXIFG_OFS));

    //Send single byte data.
    return (EUSCI_B_CMSIS(moduleInstance)->RXBUF & EUSCI_B_RXBUF_RXBUF_MASK);
}


/******************************************************************************
 * Description: Reads multiple bytes of data from the I2C slave device.
 *
 * Parameters:
 *      moduelInstance ->   indicates the I2C module that will be used
*                           appropriate values are one of the following:
*                           EUSCI_B0_BASE,
*                           EUSCI_B1_BASE,
*                           EUSCI_B2_BASE,
*                           EUSCI_B3_BASE
 *      regAddr ->  Address of register to read from I2C device
 *      *data ->    an array to store data
 *      length ->   the # of bytes to read
 *
 *****************************************************************************/
void I2CReadMultipleByte(uint32_t moduleInstance, uint8_t regAddr,
                         uint8_t * data, uint8_t length)
{
    // Set to Transmit Mode
    EUSCI_B_CMSIS(moduleInstance)->CTLW0 = (EUSCI_B_CMSIS(moduleInstance)->CTLW0
            & (~EUSCI_B_I2C_TRANSMIT_MODE)) | EUSCI_B_I2C_TRANSMIT_MODE;

    // Point to the correct register
    I2C_masterSendSingleByte(moduleInstance, regAddr);

    //Set USCI in Receive mode
    BITBAND_PERI(EUSCI_B_CMSIS(moduleInstance)->CTLW0, EUSCI_B_CTLW0_TR_OFS) = 0;

    // Set to Receiver Mode
    EUSCI_B_CMSIS(moduleInstance)->CTLW0 = (EUSCI_B_CMSIS(moduleInstance)->CTLW0
            & (~EUSCI_B_I2C_TRANSMIT_MODE)) | EUSCI_B_I2C_TRANSMIT_MODE;

    //Set USCI in Receive mode
    BITBAND_PERI(EUSCI_B_CMSIS(moduleInstance)->CTLW0, EUSCI_B_CTLW0_TR_OFS) = 0;

    /* The eUSCI_B module checks if the bus is available, generates the START condition,
        and transmits the slave address with a read bit. */
    EUSCI_B_CMSIS(moduleInstance)->CTLW0 |= (EUSCI_B_CTLW0_TXSTT + EUSCI_B_CTLW0_TXSTP);

    // The UCTXSTT flag is cleared as soon as the complete address is sent.
    // Make sure START/Address was sent
    while(BITBAND_PERI(EUSCI_B_CMSIS(moduleInstance)->CTLW0, EUSCI_B_CTLW0_TXSTT_OFS));

    int i;
    length--;   // Need to offset by one
    for (i = 0; i < length; i++)
    {
        // Receive one byte
        data[i] = (EUSCI_B_CMSIS(moduleInstance)->RXBUF & EUSCI_B_RXBUF_RXBUF_MASK);
    }

    // Set STOP bit. Note stop will not send until RX is received.
    BITBAND_PERI(EUSCI_B_CMSIS(moduleInstance)->CTLW0, EUSCI_B_CTLW0_TXSTP_OFS) = 1;

    //Poll for receive interrupt flag.
    while (!BITBAND_PERI(EUSCI_B_CMSIS(moduleInstance)->IFG,
            EUSCI_B_IFG_RXIFG_OFS));

    // Grab the last byte of data
    data[i] = (EUSCI_B_CMSIS(moduleInstance)->RXBUF & EUSCI_B_RXBUF_RXBUF_MASK);
}


/******************************************************************************
 * Description: Writes a single byte of data to the I2C slave device.
 *
 * Parameters:
 *      moduelInstance ->   indicates the I2C module that will be used
*                           appropriate values are one of the following:
*                           EUSCI_B0_BASE,
*                           EUSCI_B1_BASE,
*                           EUSCI_B2_BASE,
*                           EUSCI_B3_BASE
 *      regAddr ->  Address of register to read from I2C device
 *      data ->     data to write into selected register
 *
 *****************************************************************************/
void I2CWriteSingalByte(uint32_t moduleInstance, uint8_t regAddr, uint8_t data)
{
    // Set to Transmit Mode
    EUSCI_B_CMSIS(moduleInstance)->CTLW0 = (EUSCI_B_CMSIS(moduleInstance)->CTLW0
            & (~EUSCI_B_I2C_TRANSMIT_MODE)) | EUSCI_B_I2C_TRANSMIT_MODE;

    // Send startbit, writebit + slaveAddress, registerAddress
    I2C_masterSendMultiByteStart(moduleInstance, regAddr);
    // Send data to register Address, Stopbit
    I2C_masterSendMultiByteFinish(moduleInstance, data);
}


/******************************************************************************
 * Description: Writes multiple bytes of data to the I2C slave device.
 *
 * Parameters:
 *      moduelInstance ->   indicates the I2C module that will be used
*                           appropriate values are one of the following:
*                           EUSCI_B0_BASE,
*                           EUSCI_B1_BASE,
*                           EUSCI_B2_BASE,
*                           EUSCI_B3_BASE
 *      regAddr ->  Address of register to read from I2C device
 *      data ->     data to write into selected register
 *      length ->   the # of bytes to read
 *
 *****************************************************************************/
void I2CWriteMultipleByte(uint32_t moduleInstance, uint8_t regAddr,
                          uint8_t * data, uint8_t length)
{
    // Set to Transmit Mode
   EUSCI_B_CMSIS(moduleInstance)->CTLW0 = (EUSCI_B_CMSIS(moduleInstance)->CTLW0
           & (~EUSCI_B_I2C_TRANSMIT_MODE)) | EUSCI_B_I2C_TRANSMIT_MODE;

   // Point to correct register
    I2C_masterSendMultiByteStart(moduleInstance, regAddr);

    int i;
    length--;   // Need to offset by one
    for (i = 0; i < length; i++)
        I2C_masterSendMultiByteNext(moduleInstance, data[i]);

    // Send last Byte of data and Stop Bit
    I2C_masterSendMultiByteFinish(moduleInstance, data[i]);
}






























































