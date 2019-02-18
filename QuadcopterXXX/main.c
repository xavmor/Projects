//#include "msp.h"


#include "msp.h"
#include "driverlib/cs.h"
#include "library/i2c_custome.h"
#include "library/uart_print.h"
//#include "library/MPU6500.h"

// Global Constants
#define I2CModuleBase   EUSCI_B0_BASE

// Global Variables
//static angle_t angle; // Struct used to store angles
//static mpu6500_t mpu6500; // Gyro and accelerometer readings
//static sensor_t mag = { .data = { 1.0f, 0.0f, 0.0f } }; // If no magnetometer is used, then just use a vector with a x-component only

//TODO: LInker has two different paths to driverlib Need to fix this before issues arise.

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	
	uint8_t addr = 0x68;

    /*  Step 1: Initialize MSP432p401r hardware  */
	CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);
    i2cInit(I2CModuleBase);                                          // Set up I2C Module

    /*  Step 2: Initialize software stuff   */
    //initPID();
    //initEEPROM();     <----- Work on
    //initPPM();
    //initMPU6500(&mpu6500);
    UART0_Init();

    uint8_t * buffer;
    I2C_setSlaveAddress(I2CModuleBase, addr);
    *buffer = I2CReadSingleByte(I2CModuleBase, 117);
    UART0_OutUDec(*buffer);

    while(1);
}
