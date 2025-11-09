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

#include "main.h"


int main(void)
{
	 RCC ->APB2ENR |= RCC_APB2ENR_IOPCEN;/*Clock has been opened for port C,
	                                      it is now active. APB2ENR = Advanced peripheral 2 bus was used to access GIO,
	                                      Enable register worked to switch to Clock mode. */
	 RCC ->APB2ENR |= RCC_APB2ENR_IOPAEN;/*Clock has been opened for port A,
	                                      it is now active. APB2ENR = Advanced peripheral 2 bus was used to access GIO,
	                                      Enable register worked to switch to Clock mode. */


	 GPIOA -> CRL &=~(0xF << 0);//CF and MOD bits of pin A0 are cleared.(CF[00],MOD[00])
	 GPIOA -> CRL |= (0x8 << 0);//The A0 pin input  is set to pull-push for button .(CF[10],MOD[00])
	 GPIOA ->ODR  |= (1 << 0);

	 GPIOC -> CRH &=~(0xF << 20);//CF and MOD bits of pin 13 are cleared.(CF[00],MOD[00])
	 GPIOC -> CRH |= (0x1 << 20);//The 13 pin 10 mhz output is set to pull-push.(CF[00],MOD[01])

  while (1)
  {
    if(!(GPIOA ->IDR & (1 << 0))){
    	GPIOC ->ODR &=~(1 << 13);
    }
    else{
    	GPIOC ->ODR |=(1 << 13);
  }

}
}






































