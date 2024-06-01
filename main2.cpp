#include "mbed.h"
#include "platform/mbed_thread.h"

#define SPI_MOSI1 D11
#define SPI_MISO1 D12
#define SPI_SCK1 D13
#define SPI_CS1 A3

SPI adxlSPI(SPI_MOSI1, SPI_MISO1, SPI_SCK1);
DigitalOut cs(SPI_CS1);
DigitalOut yup2(D3, PullDown);
DigitalOut yup1(D5, PullDown);
DigitalOut ydown1(D6, PullDown);
DigitalOut ydown2(D0, PullDown);
DigitalOut xup1(D4, PullDown);
DigitalOut xup2(D2, PullDown);
DigitalOut xdown1(D9, PullDown);
DigitalOut xdown2(D10, PullDown);
float x, y, z;

void ADXL345_SPI_Initialise() {
  cs = 1;                     // Ensure CS is high when not in use
  adxlSPI.format(8, 3);       // Setup SPI: 8 bits per frame, mode 3
  adxlSPI.frequency(2000000); // SPI clock rate: 2 MHz

  // Start configuration sequence
  cs = 0;
  adxlSPI.write(0x31); // Write to DATA_FORMAT register
  adxlSPI.write(0x0B); // 4-wire SPI, full resolution, +/-16g
  cs = 1;

  cs = 0;
  adxlSPI.write(0x2D); // Write to POWER_CTL register
  adxlSPI.write(0x08); // Set to measure mode
  cs = 1;

  cs = 0;
  adxlSPI.write(0x2C); // Write to BW_RATE register
  adxlSPI.write(0x06); // Set data rate to 8 Hz (low power)
  cs = 1;
}

int main() {
  ADXL345_SPI_Initialise(); // Initialize ADXL345
  while (true) 
  {
    cs = 0;
    adxlSPI.write(0x80 | 0x40 | 0x32); // Read command for DATAX0 with MB and R/W bits set
    int16_t dataX0 = adxlSPI.write(0x00); // Dummy write to read data
    int16_t dataX1 = adxlSPI.write(0x00); // Dummy write to read next byte
    int16_t dataY0 = adxlSPI.write(0x00); // Read DATAY0
    int16_t dataY1 = adxlSPI.write(0x00); // Read DATAY1
    int16_t dataZ0 = adxlSPI.write(0x00); // Read DATAY0
    int16_t dataZ1 = adxlSPI.write(0x00); // Read DATAY1

    cs = 1;

    int16_t accelX = (dataX1 << 8) | dataX0; // Combine bytes to get the actual acceleration value
    int16_t accelY = (dataY1 << 8) | dataY0; // Combine bytes for Y-axis
    int16_t accelZ = (dataZ1 << 8) | dataZ0; // Combine bytes for Y-axis
    x=0.004*accelX; 
    y=0.004*accelY; 
    z=0.004*accelZ;
    printf("hello");
    printf("x = %d\t y = %d\t z = %d\n\r", accelX, accelY, accelZ); // print
    // Example thresholds for turning on LEDs, adjust as needed
    int16_t thresholdHigh = 102; // Approximately +1g in a ±2g range or +0.25g in a ±8g range
    int16_t thresholdLow = -102; // Approximately -1g

    xup1 = 0;
    xup2 = 0;
    xdown1 = 0;
    xdown2 = 0;
    yup1 = 0;
    yup2 = 0;
    ydown1 = 0;
    ydown2 = 0;
    // X-axis acceleration LED control
    if (accelX < thresholdHigh && accelX >= 0) 
    {
        xup1 = 1;
        xup2 = 0;
        xdown1 = 0;
        xdown2 = 0;
    } else if (accelX > thresholdHigh) 
    {
        xup1 = 1;
        xup2 = 1;
        xdown1 = 0;
        xdown2 = 0;
    } else if (accelX > thresholdLow && accelX <= 0) 
    {
        xup1 = 0;
        xup2 = 0;
        xdown1 = 1;
        xdown2 = 0;
    } else if (accelX < thresholdHigh) 
    {
        xup1 = 0;
        xup2 = 0;
        xdown1 = 1;
        xdown2 = 1;
    }


    // Y-axis acceleration LED control
    if (accelY < thresholdHigh && accelY >= 0) 
    {
        yup1 = 1;
        yup2 = 0;
        xdown1 = 0;
        xdown2 = 0;
    } else if (accelY > thresholdHigh) 
    {
        yup1 = 1;
        yup2 = 1;
        xdown1 = 0;
        xdown2 = 0;
    } else if (accelY > thresholdLow && accelY <= 0) 
    {
        yup1 = 0;
        yup2 = 0;
        ydown1 = 1;
        ydown2 = 0;
    } else if (accelY < thresholdHigh) 
    {
        yup1 = 0;
        yup2 = 0;
        ydown1 = 1;
        ydown2 = 1;
    }
    thread_sleep_for(10);
    }
}



