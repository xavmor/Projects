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
#ifndef __types_h__
#define __types_h__

#include "stdio.h"
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef union
{
    struct
    {
        int16_t X, Y, Z;
    } __attribute__((packed)) axis;
    int16_t data[3];
} sensorRaw_t;

typedef union
{
    struct
    {
        float X, Y, Z;
    } __attribute__((packed)) axis;
    float data[3];
} sensor_t;

typedef union
{
    struct
    {
        float roll, pitch, yaw;
    } __attribute__((packed)) axis;
    float data[3];
} angle_t;

#ifdef __cplusplus
}
#endif

#endif
