.syntax unified @specify that you will use the modern arm language
.thumb @specify that you will be using the thumb 2 set

.equ clk_zero , 0x40021000 @I assigned the clock reset control unit to clk_zero.
.equ clk_evo ,clk_zero + 0x18 @It assigns the peripheral clocks to the exact address of the record that activates them.

.equ base_gpio , 0x40010800 @The general purpose PA is the basic entry and exit address

.equ crl_gpio , base_gpio + 0x00 @Port allocation assigns lower register addresses. From PA0 to PA7

.equ out_gpio ,base_gpio + 0x0C @Keeps the output data record

.equ open_clk , (1<<2) @Holds the bit that opens the GPIO clock

.equ pa_1_pin , (1<<1) @The bit value representing PA1 thousand was assigned

.equ out_loop ,70 @The number of external loops was assigned a value of 70

.equ in_loop ,26600 @The number of inner loops was assigned a value of 26600.

.global main @Provides access to the connector from outside the main function


main :@Start execution
 LDR R0,=clk_evo @Load to clok_evo R0 register
 LDR R1,[R0]     @R0 read the current value R1 load (clock setting)
 ORR R1,R1, #open_clk @Add the open_clk value to the value in R1 with the OR operation.
 STR R1,[R0] @Write back the new value R1 to R0 (GPIO is now operational)

 LDR R0 , =crl_gpio @Load address R0 in circle_gpio
 LDR R1 , [R0] @Read R0 current value and load R1

 LDR R2 ,= 0xFFFFFF0F @It resets the bit settings of PA1 by masking.
 AND R1,R1,R2 @Clear the setting bits of PA1 using the AND command. (The settings of other pins are preserved.)

 LDR R2, = 0x30 @It represents the setting MODE1=0b11 (50Mhz) and CNF1=0b00 (Push-Pull).
 ORR R1 ,R1 ,R2 @The new R1 in R2 is added to the R2 with the OR operation, this sets the PA1 50 mhz push-out output.
 STR R1 , [R0] @PA1 is out now

 LDR R3, =out_gpio @load out_gpio to R3

loop:
@ Light ON
 LDR R1, [R3] @Read the current value R3 and load it into R1.
 ORR R1 ,R1 ,#pa_1_pin @Or logical operations set the PA1 bit value to 1.
 STR R1 ,[R3] @The PA1 pin becomes High and the LED lights up

 BL delay_1s @1 second delay

@ Light OFF
 LDR R1, [R3] @Read the current value R3 and load it into R1.
 BIC R1 ,R1 ,#pa_1_pin @Sets the bit of R1 to zero
 STR R1 ,[R3] @The PA1 pin becomes Low and the LED lights down

 BL delay_1s @1 second delay

 B loop @Prevent the program from running randomly and terminating

.type delay_1s ,%function @we have defined that delays_1 is a function
delay_1s:
 LDR R1 ,=out_loop @Load the value out_loop into register R1

 .outer_loop:
 LDR R2 ,=in_loop @Load the value in_loop into register R2

.inner_loop:
  SUBS R2,R2, #1 @Reduce the value in R2 by 1
  BNE .inner_loop @If R2 is not zero after the subtraction, return to in_loop (repeat the inner loop).

  SUBS R1,R1, #1 @Reduce the value in R2 by 1
  BNE .outer_loop @If R1 is not zero after the subtraction, return to out_loop (repeat the outer loop).

  BX lr @Returns to the address held in the Lr register. Delay completed

.size delay_1s, .-delay_1s
