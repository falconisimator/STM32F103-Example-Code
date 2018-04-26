/*
 * GPIO_Example_Code.c
 *
 * The content of this script has been written by Eric Falcon based on:
 *  https://sites.google.com/site/learningeclipsearm/5-using-stm32-std-lib/b-digital-io-pins
 *  No attribution is necessary when using this code as it's all very easy :D
 */



#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"



GPIO_InitTypeDef GPIO_InitStruct;

#define OUT_A0       GPIOA, GPIO_Pin_0
#define IN_A1       GPIOA, GPIO_Pin_1

//Reading and writing bits can be simplified by redefining the functions
#define GPIO_Write(pin, value)  GPIO_WriteBit(pin, value)
#define GPIO_Read(pin)          GPIO_ReadInputDataBit(pin)

int main(void)
{
    // Enable clock for GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // Configure Pin 0
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    //Set Pin rise/fall time, should be set as low as possible for the application to avoid noise
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    //set pin to output push/pull to be actively raised or lowered
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    //initialize GPIOA with settings in &GPIO_InitStruct
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configure pin 1
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    //Set speed to 2mhz
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    //Set mode to input with a pull-up resistor
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    //Initialize gpio pin A1 with above settings
    GPIO_Init(GPIOA, &GPIO_InitStruct);



    while (1)
    {
        // If button on PA1 is pressed (button circuit is active low)
        if (!(GPIO_Read(IN_A1)))
        {
        	// Turn on output on PA0
            GPIO_Write(OUT_A0,1);
        }
        else
        {
            // Turn off output on PA0
        	GPIO_Write(OUT_A0,0);
        }
    }
}