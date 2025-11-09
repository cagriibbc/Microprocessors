/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
void timer(uint32_t delay); //defining the delay function
# define led_delay 800000

int main(void)
{
 RCC ->APB2ENR |= RCC_APB2ENR_IOPCEN;/*Clock has been opened for port C,
                                      it is now active. APB2ENR = Advanced peripheral 2 bus was used to access GIO,
                                      Enable register worked to switch to Clock mode. */


 GPIOC -> CRH &=~(0xF << 20);//CF and MOD bits of pin 13 are cleared.(CF[00],MOD[00])
 GPIOC -> CRH |= (0x1 << 20);//The 13 pin 10 mhz output is set to pull-push.(CF[00],MOD[01])

  while (1) // infinite loop
  {
	  GPIOC -> ODR ^=(1 << 13); //If pin 13 is on, turn it off, if it is off, turn it on.(Toggle MOD)
      timer(led_delay); //make a 1 second delay
  }

}


void timer(uint32_t delay)//delay function for 1 second delay
{
	for ( uint32_t i = 0 ; i < delay ; i++){
		__NOP(); //Wait 1 clock cycle without doing anything(No operation)
	}

}




















































