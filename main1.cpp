#include "mbed.h"
#include "platform/mbed_thread.h"
#include <arm_acle.h>

#define Temp_Reg 0x00
#define Config_Reg 0x01
#define TLow_Reg 0x02
#define THigh_Reg 0x03

I2C tmpi2c(D0, D1);
InterruptIn button(D8, PullDown);
const int tmp102_addr = 0x90;
char ConfigRegisterTMP102[3];
char TemperatureRegister[2];
float temperature;
int flag = 0;

void ConfigureTMP()
{
    ConfigRegisterTMP102[0] = Config_Reg;
    //ConfigRegisterTMP102[1] = 0x60;
    ConfigRegisterTMP102[1] = 0x61; //For SD
    ConfigRegisterTMP102[2] = 0xA0;
    tmpi2c.write(tmp102_addr, ConfigRegisterTMP102, 3);
}

// void Set_Termostat_Temp_Low()
// {
//     ConfigRegisterTMP102[0] = TLow_Reg;
//     ConfigRegisterTMP102[1] = 0x14;
//     ConfigRegisterTMP102[2] = 0x00;
//     tmpi2c.write(tmp102_addr, ConfigRegisterTMP102, 3);
// }

// void Set_Thermostat_Temp_High()
// {
//     ConfigRegisterTMP102[0] = THigh_Reg;
//     ConfigRegisterTMP102[1] = 0x16;
//     ConfigRegisterTMP102[2] = 0x00;
//     tmpi2c.write(tmp102_addr, ConfigRegisterTMP102, 3);
// }

void One_shot()
{
    ConfigRegisterTMP102[0] = Config_Reg;
    ConfigRegisterTMP102[1] = 0x81;
    ConfigRegisterTMP102[2] = 0x00;
    tmpi2c.write(tmp102_addr, ConfigRegisterTMP102, 3);
    thread_sleep_for(50);
}

void interupt()
{
    flag = 1;
}

int main()
{
    ConfigureTMP();
    // Set_Termostat_Temp_Low();
    // Set_Thermostat_Temp_High();
    ConfigRegisterTMP102[0] = Temp_Reg;
    tmpi2c.write(tmp102_addr, ConfigRegisterTMP102, 1);

    printf("Temperature Sensor TMP102\n");
    button.rise(&interupt);
    
    while(1)
    {
        float tem_sum = 0;
        
        if(flag)
        {
            for(int i=0; i < 4; i++)
            {
                One_shot();
                ConfigRegisterTMP102[0] = Temp_Reg;
                tmpi2c.write(tmp102_addr, ConfigRegisterTMP102, 1);
                tmpi2c.read(tmp102_addr, TemperatureRegister, 2);
                temperature = (int16_t((TemperatureRegister[0] << 4) | (TemperatureRegister[1] >> 4)) * 0.0625);
                printf("Temperature: %.2f\n", temperature);
                thread_sleep_for(200);
                tem_sum += temperature;
        }
            printf("Mean Temperature = %.2f\n", tem_sum/4.0);
        }
        flag = 0;
    }

    // while(1)
    // {
    //     float tem_sum = 0;
    //     for(int i=0; i < 4; i++)
    //         {
    //             //One_shot();
    //             ConfigRegisterTMP102[0] = Temp_Reg;
    //             tmpi2c.write(tmp102_addr, ConfigRegisterTMP102, 1);
    //             tmpi2c.read(tmp102_addr, TemperatureRegister, 2);
    //             temperature = (int16_t((TemperatureRegister[0] << 4) | (TemperatureRegister[1] >> 4)) * 0.0625);
    //             printf("Temperature: %.2f\n", temperature);
    //             thread_sleep_for(200);
    //             tem_sum += temperature;
    //         }
    //     printf("Mean Temperature = %.2f\n", tem_sum/4.0);
        
    // }
}

