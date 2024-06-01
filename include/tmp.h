#ifndef TMP_H
#define TMP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mbed.h"
#include "platform/mbed_thread.h"
#include <arm_acle.h>

// Define the TMP102 register addresses
#define Temp_Reg 0x00
#define Config_Reg 0x01
#define TLow_Reg 0x02
#define THigh_Reg 0x03

// TMP102 I2C Address
extern const int tmp102_addr;

// Function declarations
void ConfigureTMP(void);
void One_shot(void);
void interupt(void);
void tmp(float *tmp);

#ifdef __cplusplus
}
#endif

#endif // TMP102_H