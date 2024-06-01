#ifndef ADXL_H
#define ADXL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mbed.h"

#define SPI_MOSI1 D11
#define SPI_MISO1 D12
#define SPI_SCK1 D13
#define SPI_CS1 A3

void ADXL345_SPI_Initialise(void);
void acceleration(float *x, float *y, float *z);

#ifdef __cplusplus
}
#endif

#endif
