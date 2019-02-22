//#include "msp.h"


#include "msp.h"
#include "driverlib/cs.h"
#include "library/i2c_custome.h"
#include "library/uart_print.h"
#include "MPLibrary/driver/eMPL/inv_mpu.h"
#include <gpio.h>
#include <interrupt.h>
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
	struct int_param_s * basic_params;

    /*  Step 1: Initialize MSP432p401r hardware  */
	CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);
    i2cInit(I2CModuleBase);  // Set up I2C Module
    I2C_setSlaveAddress(I2CModuleBase, addr);
    UART0_Init();   // Set up terminal communication
    //InitClockTime();


    /* Testing Phase */
    //basic_params->pin = 0x01;

//
    mpu_init(basic_params);
//
//
//    short gyro[3];
//    short accel[3];
//    unsigned long * timeStamp;
//    unsigned long stuff[3];
//    unsigned char sensor[3];
//    unsigned char more[3];
//    while (1)
//    {
//        mpu_read_fifo(gyro, accel, timeStamp, sensor, more);
//        //mpu_get_gyro_reg(buffer, &stuff);
//        //I2CReadMultipleByte(I2CModuleBase, 59, &buffer, 1);
//        UART0_OutUDec(gyro[0]);
//        UART0_OutString(" - ");
//        UART0_OutUDec(gyro[1]);
//        UART0_OutString(" - ");
//        UART0_OutUDec(gyro[2]);
//        UART0_OutString("\n");
//
//        gyro[0] =0;
//    }
//
//    while(1);






    /*  Step 2: Initialize software stuff   */
    //initPID();
    //initEEPROM();     <----- Work on
    //initPPM();
    //initMPU6500(&mpu6500);


    uint8_t buffer[3];
    //I2C_setSlaveAddress(I2CModuleBase, addr);


    while(1)
    {
        int i = 0;
        for (;i < 65000; i++);
        buffer[0] = I2CReadSingleByte(I2CModuleBase, 59);
//        I2CReadMultipleByte(I2CModuleBase, 59, buffer, 3);
        UART0_OutUDec(buffer[0]);
//        UART0_OutString(" - ");
//        UART0_OutUDec(buffer[1]);
//        UART0_OutString(" - ");
//        UART0_OutUDec(buffer[2]);
        UART0_OutString("\n");
//
//        buffer[0] = 1;
//        buffer[1] = 1;
//        buffer[2] = 1;
    }
}


/* GPIO ISR */
void PORT5_IRQHandler(void)
{
    uint32_t status;

    // Read interrupt status
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P5);
    // Clear interrupt status
    GPIO_clearInterruptFlag(GPIO_PORT_P5, status);

    // We can now read the data from the MPU6500


}


// Returns a time stamp kind of weird way of doing it sorry
//void InitClockTime()
//{
//    // Assuming DCO is 12 MHz, Initialize MCLK to be 12MHz/128 = 93,750 Hz
//    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_128);
//
//    // Set our timer, further divide 93,750 Hz / 16 = 5.859 kHz
//    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_16,
//                       TIMER32_32BIT, TIMER32_FREE_RUN_MODE);
//
//    // Set clock count
//    Timer32_setCount(TIMER32_0_BASE, UINT32_MAX);
//
//    // Start clock
//    Timer32_startTimer(TIMER32_0_BASE, true);
//}
