#include "mbed.h"
#include "platform/mbed_thread.h"
#include "tmp.h"
#include "adxl.h"

// SPI adxlSPI(SPI_MOSI1, SPI_MISO1, SPI_SCK1);
// DigitalOut cs(SPI_CS1);
//I2C tmpi2c(D0, D1);
InterruptIn button(D8, PullDown);
const int tmp102_addr = 0x90;
//char ConfigRegisterTMP102[3];
//char TemperatureRegister[2];
float temperature;
int flag = 0;
DigitalOut led(D7);
float *x_acceleration, *y_acceleration, *z_acceleration;

void interupt()
{
    flag = 1;
}

int main()
{
    ConfigureTMP();
    ADXL345_SPI_Initialise();
    button.rise(&interupt);
    while(1)
    {
        if (flag == 1)
        {
            tmp(&temperature);
        }
        acceleration(x_acceleration, y_acceleration, z_acceleration);
    }
}