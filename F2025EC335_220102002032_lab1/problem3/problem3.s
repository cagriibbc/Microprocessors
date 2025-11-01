.syntax unified @specify that you will use the modern arm language
.thumb @specify that you will be using the thumb 2 set

.equ clk_zero , 0x40021000 @I assigned the clock reset control unit to clk_zero.
.equ clk_evo ,clk_zero + 0x18 @It assigns the peripheral clocks to the exact address of the record that activates them.

.equ base_gpio , 0x40010800 @The general purpose PA is the basic entry and exit address

.equ crl_gpio ,  base_gpio + 0x00 @Port allocation assigns lower register addresses. From PA0 to PA7

.equ out_gpio , base_gpio + 0x0C @Keeps the output data record

.equ open_clk , (1<<2) @Holds the bit that opens the GPIO clock

.equ pa_all , 0x1E @It represents the PA1, PA2, PA3 and PA4 bins collectively.

.equ pa_clean ,0xFFF0000F @Resets the pin's setting bits from PA1 to PA4.

.equ pa_light ,0x00033330 @The value that sets all pins from PA1 to PA4 to push-pull 50 mHz.

.global main @Provides access to the connector from outside the main function


main :@Start execution
LDR R0,=clk_evo @Load to clok_evo R0 register
LDR R1,[R0]     @R0 read the current value R1 load (clock setting)
ORR R1,R1, #open_clk @Add the open_clk value to the value in R1 with the OR operation.
STR R1,[R0] @Write back the new value R1 to R0 (GPIO is now operational)

LDR R0 , =crl_gpio @Load address R0 in circle_gpio
LDR R1 , [R0] @Read R0 current value and load R1

LDR R2 ,= pa_clean @It resets the bit settings of PA1,PA2,PA3 and PA4 by masking.
AND R1,R1,R2 @Clear the setting bits of PA1 using the AND command. (The settings of other pins are preserved.)

LDR R2, = pa_light @It represents the setting MODE1=0b11 (50Mhz) and CNF1=0b00 (Push-Pull).
ORR R1 ,R1 ,R2 @The new R1 in R2 is added to the R2 with the OR operation, this sets the PA1,PA2,PA3 and PA4 50 mhz push-out output.
STR R1 , [R0] @PA1,PA2,PA3 and PA4 are out now

LDR R0, =out_gpio @load out_gpio to R0
LDR R1, [R0] @Read the current value R0 and load it into R1.
ORR R1 ,R1 ,#pa_all @Or logical operations set the PA1,PA2,PA3 and PA4  bit value to 1.
STR R1 ,[R0] @The PA1,PA2,PA3 and PA4  pin become High and the LED lights up

loop: @Prevent the program from running randomly and terminating
  B loop
