#include "main.h"
void timer(uint32_t delay); //defining the delay function
# define led_delay 80000
# define high_delay 160000
int main(void)
{
	volatile uint8_t taraf = 0;
	volatile uint8_t together = 0x07;

	 RCC ->APB2ENR |= RCC_APB2ENR_IOPAEN;/*Clock has been opened for port A,
		                                      it is now active. APB2ENR = Advanced peripheral 2 bus was used to access GIO,
		                                      Enable register worked to switch to Clock mode. */

		 GPIOA -> CRL &=~(0xF << 0);//CF and MOD bits of pin A0 are cleared.(CF[00],MOD[00])
		 GPIOA -> CRL |= (0x1 << 0);//The A0 pin 10 mhz output is set to pull-push.(CF[00],MOD[01])

		 GPIOA -> CRL &=~(0xF << 4);//CF and MOD bits of pin A1 are cleared.(CF[00],MOD[00])
		 GPIOA -> CRL |= (0x1 << 4);//The A1 pin 10 mhz output is set to pull-push.(CF[00],MOD[01])

		 GPIOA -> CRL &=~(0xF << 8);//CF and MOD bits of pin A2 are cleared.(CF[00],MOD[00])
		 GPIOA -> CRL |= (0x1 << 8);//The A2 pin 10 mhz output is set to pull-push.(CF[00],MOD[01])

	     GPIOA -> CRL &=~(0xF << 12);//CF and MOD bits of pin A3 are cleared.(CF[00],MOD[00])
		 GPIOA -> CRL |= (0x1 << 12);//The A3 pin 10 mhz output is set to pull-push.(CF[00],MOD[01])

		 GPIOA -> CRL &=~(0xF << 16);//CF and MOD bits of pin A4 are cleared.(CF[00],MOD[00])
		 GPIOA -> CRL |= (0x1 << 16);//The A4 pin 10 mhz output is set to pull-push.(CF[00],MOD[01])

		 GPIOA -> CRL &=~(0xF << 20);//CF and MOD bits of pin A5 are cleared.(CF[00],MOD[00])
		 GPIOA -> CRL |= (0x1 << 20);//The A5 pin 10 mhz output is set to pull-push.(CF[00],MOD[01])

		 GPIOA -> CRL &=~(0xF << 24);//CF and MOD bits of pin A6 are cleared.(CF[00],MOD[00])
		 GPIOA -> CRL |= (0x1 << 24);//The A6 pin 10 mhz output is set to pull-push.(CF[00],MOD[01])

		 GPIOA -> CRL &=~(0xF << 28);//CF and MOD bits of pin A7 are cleared.(CF[00],MOD[00])
		 GPIOA -> CRL |= (0x1 << 28);//The A7 pin 10 mhz output is set to pull-push.(CF[00],MOD[01])

		 GPIOA ->CRH &=~(0xF << 0);//CF and MOD bits of pin A8 are cleared.(CF[00],MOD[00])
		 GPIOA -> CRH |= (0x8 << 0);//The A8 pin İNPUT is set to pull-push for button.(CF[10],MOD[00])
		 GPIOA ->ODR |=(1 << 8);

  while (1)
  {
	 GPIOA -> ODR &=~(0xFF);
	 GPIOA -> ODR |= together;
	 timer(led_delay);
     if(!(GPIOA ->IDR & (1 << 8))) {
    	 taraf ^= 1;
    	 timer(high_delay);
     }
     if (taraf == 0) // left go
    	 if(together == 0xE0){
    		 together = 0x07;
    	 }
    	 else{
    		 together <<= 1;
    	 }
     else if (taraf == 1) // right go
     {
    	 if (together == 0x07){
    		 together = 0xE0;
    	 }
    	 else{
    		 together >>=1;
    	 }
     }
	    }
	}
void timer(uint32_t delay)//delay function for 1 second delay
{
	for ( uint32_t i = 0 ; i < delay ; i++){
		__NOP(); //Wait 1 clock cycle without doing anything(No operation)
	}

}

