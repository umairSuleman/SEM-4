#include <LPC17xx.h>

// Array for mapping digits 0-9 to their 7-segment display encoding
unsigned char tohex[10] = {0x3F, 0X06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// Variables used for controlling the countdown and loop indices
unsigned int i = 0, j = 0, temp, counter=9999, switchState=1, flag = 1;

// Array to store the digits for each of the four 7-segment display positions

void initTimer0(void){
	LPC_SC->PCONP |= (1<<1); //Power up TIM0
	LPC_SC->PCLKSEL0 &= (0x3 << 3);  // Set clock for Timer 0 to CCLK
	
	LPC_TIM0->CTCR = 0x0;
	LPC_TIM0->PR = 999;
	//25000 clck @25Mhz = 1ms
	LPC_TIM0->TCR = 0x02; //Reset timer
}
/*
void delay(unsigned int millisec){
	LPC_TIM0->TCR = 0x02; //Reset Timer
	LPC_TIM0->TCR = 0x01; //Enable Timer
	while (LPC_TIM0->TC < millisec); 
	LPC_TIM0->TCR = 0x00; //Disable timer
	
}
*/
int main(){
    // Initialize the system and update the system core clock (usually required for LPC17xx setup)
    SystemInit();
    SystemCoreClockUpdate();
  
    initTimer0();

    //Using CND for key => 7th pin is P2.0
    LPC_PINCON->PINSEL4 &= 0xFFFFFFFC; //For Key
    LPC_GPIO2->FIODIR &= 0xFFFFFFFE //~0x00000001 
	
    // Configure GPIO pins for the 7-segment displays
    // LPC_GPIO0 pins 0 to 7 are set as outputs to control the 7-segment display (8 bits)
    LPC_GPIO0->FIODIR |= 0xFF0;  // Set bits 4 to 11 as output (8 bits for 7-segment display)
    
    // LPC_GPIO1 pins 23 to 26 are set as outputs to select which 7-segment digit to control
    LPC_GPIO1->FIODIR |= 0xF << 23; // Set bits 23-26 as output (4 bits for digit select) - Not sure why yet, mux => 23 and 24th bit only

		while (1){
			
			LPC_TIM0->TCR = 0x02; //Reset Timer
			LPC_TIM0->TCR = 0x01; //Enable Timer
			while (LPC_TIM0->TC < 1000){
				temp = counter;
				LPC_GPIO1->FIOPIN =	0 << 23;
				LPC_GPIO0->FIOPIN = tohex[temp%10] << 4;
				for(i=0; i<1000; i++);
				
				temp /= 10;
				
				LPC_GPIO1->FIOPIN =	1 << 23;
				LPC_GPIO0->FIOPIN = tohex[temp%10] << 4;
				for(i=0; i<1000; i++);
				
				temp /= 10;
				
				LPC_GPIO1->FIOPIN =	2 << 23;
				LPC_GPIO0->FIOPIN = tohex[temp%10] << 4;
				for(i=0; i<1000; i++);
				
				temp /= 10;
				
				LPC_GPIO1->FIOPIN =	3 << 23;
				LPC_GPIO0->FIOPIN = tohex[temp%10] << 4;
				for(i=0; i<1000; i++);
			}
			LPC_TIM0->TCR = 0x00; //Disable timer
			
			switchState = (LPC_GPIO2->FIOPIN >> 12) & 1;
			if (switchState == 0){
				flag = !flag;
				if (flag) counter = 9999;
				else counter = 0;
			}
			if (flag)	
				counter--;
			else counter++;
			if (counter == 0)
				counter = 9999;

		} 
}
