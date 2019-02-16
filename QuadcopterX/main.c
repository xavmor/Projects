#include "inc/msp.h"
#include "library/MPU6500.h"
#include "driverlib/driverlib.h"


// Global Variables
static angle_t angle; // Struct used to store angles
static mpu6500_t mpu6500; // Gyro and accelerometer readings
static sensor_t mag = { .data = { 1.0f, 0.0f, 0.0f } }; // If no magnetometer is used, then just use a vector with a x-component only

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    uint8_t addr = 0x68;

    /*  Step 1: Initialize MSP432p401r hardware  */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);    // Set system speed to 48MHz
    i2cInit();                                          // Set up I2C Module

    /*  Step 2: Initialize software stuff   */
    //initPID();
    //initEEPROM();     <----- Work on
    //initPPM();
    initMPU6500(&mpu6500);


    uint8_t * buffer;
    i2cReadData(addr, 0x70, buffer, 1);

    while(1);
    //IntMasterEnable(); // Enable all interrupts

//    if (dataReadyMPU6500())
//    {
//        uint32_t now = micros();
//        static uint32_t timer = 0; // Used to keep track of the time
//        float dt = (float)(now - timer) / 1e6f; // Convert to seconds
//        //UARTprintf("%d\n", now - timer);
//        timer = now;
//
//        // Read IMU
//        getMPU6500Data(&mpu6500); // Get accelerometer and gyroscope values
//        getAngles(&mpu6500, &mag, &angle, dt); // Calculate pitch, roll and yaw

        // Motors routine

//        if (runMotors)
//        {
//            float aileron = getRXChannel(RX_AILERON_CHAN);
//            float elevator = -getRXChannel(RX_ELEVATOR_CHAN); // Invert so it follows the right hand rule for the NED-coordinate system
//            float rudder = getRXChannel(RX_RUDDER_CHAN);
//            //UARTprintf("%d\t%d\t%d\n", (int16_t)aileron, (int16_t)elevator, (int16_t)rudder);
//            float setpointRoll, setpointPitch; // Roll and pitch control can both be gyro or accelerometer based
//            const float setpointYaw = rudder * cfg.stickScalingYaw; // Yaw is always gyro controlled
//
//            if (angleMode)
//            { // Angle mode
//                const uint8_t maxAngleInclination = cfg.maxAngleInclination; // If in altitude mode the angle has to be limited to the capability of the sonar
//                setpointRoll = constrain(aileron, -maxAngleInclination, maxAngleInclination) - angle.axis.roll;
//                setpointPitch = constrain(elevator, -maxAngleInclination, maxAngleInclination) - angle.axis.pitch;
//                setpointRoll *= cfg.angleKp; // A cascaded P controller is used in self level mode, as the output from the P controller is then used as the set point for the acro PID controller
//                setpointPitch *= cfg.angleKp;
//
//            }
//            else    // Acro mode
//            {
//                setpointRoll = aileron * cfg.stickScalingRollPitch;
//                setpointPitch = elevator * cfg.stickScalingRollPitch;
//            }

}
