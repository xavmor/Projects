/* Copyright (C) 2015 Kristian Sloth Lauszus. All rights reserved.

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").

 Contact information
 -------------------

 Kristian Sloth Lauszus
 Web      :  http://www.lauszus.com
 e-mail   :  lauszus@gmail.com
*/

#include <stdint.h>
#include <stdbool.h>

//#include "Buzzer.h"
#include "EEPROM.h"

//#include "eeprom.h"
#include "ti/devices/msp432p4xx/driverlib/sysctl.h"
#include "ti/devices/msp432p4xx/driverlib/cs.h"
#include "ti/devices/msp432p4xx/driverlib/flash.h"
#include "ti/devices/msp432p4xx/driverlib/pcm.h"
//#if UART_DEBUG
//#include "utils/uartstdio.h" // Add "UART_BUFFERED" to preprocessor
//#endif

#define MEMORY_ADDRESS  0x0003F000


static const uint32_t configVersion = 21; // Must be bumped every time config_t is changed
config_t cfg;

void initEEPROM(void)
{
    //SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0); // Enable EEPROM peripheral
    //SysCtlDelay(2); // Insert a few cycles after enabling the peripheral to allow the clock to be fully activated
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    FlashCtl_setWaitState(FLASH_BANK0, 1);
    FlashCtl_setWaitState(FLASH_BANK1, 1);
    //MAP_CS_setDCOCenterdFrequency(CS_DCO_FREQUENCY_48);


    // Make sure config_t is a multiple of 4 - the compiler should pack structs to 4 bytes, but I added this check to be 100% sure
    if (sizeof(config_t) % 4 != 0)
    {
//#if UART_DEBUG
//        UARTprintf("Config size error: %u\n", sizeof(config_t));
//#endif
        //buzzer(true);
        while (1);
    }

    uint32_t rcode = EEPROMInit();

    if (rcode)
    {
//#if UART_DEBUG
//        UARTprintf("EEPROMInit error: %u\n", rcode);
//#endif
        //buzzer(true);
        while (1);
    }

//    uint32_t version;
//    //EEPROMRead(&version, 0, sizeof(version));
//    if (version != configVersion)
//    {
//        setDefaultConfig();
//        //beepLongBuzzer();
//    } else
//        EEPROMRead((uint32_t*)&cfg, sizeof(configVersion), sizeof(config_t)); // Read config from EEPROM
}

void setDefaultConfig(void)
{
    cfg.pidRollPitchValues.Kp = 0.310f;
    cfg.pidRollPitchValues.Ki = 1.65f;
    cfg.pidRollPitchValues.Kd = 0.00040f * 3.0f;
    cfg.pidRollPitchValues.integrationLimit = 5.85f; // Prevent windup
    cfg.pidRollPitchValues.Fc = 150.0f; // 150 Hz

    cfg.pidYawValues.Kp = 1.000f;
    cfg.pidYawValues.Ki = 6.00f;
    cfg.pidYawValues.Kd = 0.00040f * 3.0f;
    cfg.pidYawValues.integrationLimit = 10.0f; // Prevent windup
    cfg.pidYawValues.Fc = 150.0f; // 150 Hz

    cfg.pidSonarAltHoldValues.Kp = 0.040f;
    cfg.pidSonarAltHoldValues.Ki = 0.03f;
    cfg.pidSonarAltHoldValues.Kd = 0.00330f * 3.0f;
    cfg.pidSonarAltHoldValues.integrationLimit = 10.0f; // Prevent windup
    cfg.pidSonarAltHoldValues.Fc = 150.0f; // 150 Hz

    cfg.pidBaroAltHoldValues.Kp = 0.006f;
    cfg.pidBaroAltHoldValues.Ki = 0.00f;
    cfg.pidBaroAltHoldValues.Kd = 0.00450f * 3.0f;
    cfg.pidBaroAltHoldValues.integrationLimit = 10.0f; // Prevent windup
    cfg.pidBaroAltHoldValues.Fc = 150.0f; // 150 Hz

    resetPIDRollPitchYaw();
    resetPIDAltHold();

    cfg.angleKp = 4.50f;
    cfg.headKp = 0.65f;
    cfg.maxAngleInclination = 50; // Max angle in self level mode
    cfg.maxAngleInclinationDistSensor = 25; // Max angle when using sonar or LIDAR-Lite v3 in altitude hold mode
    cfg.stickScalingRollPitch = 4.69f;
    cfg.stickScalingYaw = 2.0f;

    cfg.calibrateESCs = false;

    uint8_t axis = 0;
    for (;axis < 3; axis++)
    {
        cfg.accZero.data[axis] = 0;
        cfg.magZero.data[axis] = 0;
    }

    //uint32_t rcode = EEPROMProgram((uint32_t*)&configVersion, 0, sizeof(configVersion)); // Write version number to EEPROM
//    if (rcode)
//    {
////#if UART_DEBUG
////        UARTprintf("Error writing version number to EEPROM: %u\n", rcode);
////#endif
//        //buzzer(true);
//    } else
//        updateConfig(); // Write values to EEPROM
}

void updateConfig(void)
{
//    uint32_t rcode = EEPROMProgram((uint32_t*)&cfg, sizeof(configVersion), sizeof(config_t)); // Write config to EEPROM
//
//    if (rcode)
//    {
////#if UART_DEBUG
////        UARTprintf("Error writing config to EEPROM: %u\n", rcode);
////#endif
//        //buzzer(true);
//    }
}


// Verify memory integrity
uint32_t EEPROMInit()
{
    bool status;
    status = FlashCtl_verifyMemory((void*)MEMORY_ADDRESS, 4096, 0xA5);

    if (status)
        ;//FlashCtl_enableReadBuffering(FLASH_BANK1, FLASH_DATA_READ);

    // TODO: Add a way to repair the memory if possible

    // if successful then return false
    return (uint32_t) !status;
}


uint32_t EEPROMRead(uint32_t *pui32Data, uint32_t ui32Address, uint32_t ui32Count)
{
    return 0;//FlashCtl_enableReadBuffering();
}
