//#include "msp.h"


#include "ti/devices/msp432p4xx/inc/msp.h"
#include "ti/devices/msp432p4xx/driverlib/cs.h"
#include "library/MPU6500.h"

// Global Variables
static angle_t angle; // Struct used to store angles
static mpu6500_t mpu6500; // Gyro and accelerometer readings
static sensor_t mag = { .data = { 1.0f, 0.0f, 0.0f } }; // If no magnetometer is used, then just use a vector with a x-component only



/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	
	uint8_t addr = 0x68;

    /*  Step 1: Initialize MSP432p401r hardware  */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);    // Set system speed to 48MHz
    //i2cInit();                                          // Set up I2C Module

    /*  Step 2: Initialize software stuff   */
    //initPID();
    //initEEPROM();     <----- Work on
    //initPPM();
    //initMPU6500(&mpu6500);


    uint8_t * buffer;
    //i2cReadData(addr, 0x70, buffer, 1);

    while(1);
}
