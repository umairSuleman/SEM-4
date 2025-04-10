// Write a C program to rotate the stepper motor in the clockwise direction when SW2 is 
// high and anticlockwise direction when SW2 is low.

#include <LPC17xx.H> 

void clock_wise(void); 
void anti_clock_wise(void); 

unsigned long int var1,var2; 
unsigned int i=0,j=0,k=0; 

unsigned int switchState=1;

int main(void) { 
	SystemInit(); 
	SystemCoreClockUpdate(); 
	
	LPC_PINCON->PINSEL0 = 0xFFFF00FF; //P0.4 to P0.7 GPIO 
	LPC_GPIO0->FIODIR = 0x000000F0; //P0.4 to P0.7 output 
	
	LPC_PINCON->PINSEL4 &= 0xFCFFFFFF; //For Key
	LPC_GPIO2->FIODIR &= ~(1<<12);//0x00001000;
	
	while(1){ 
		switchState = (LPC_GPIO2->FIOPIN >> 12) & 1;
		if (switchState == 0)
				clock_wise();
		else
			anti_clock_wise(); 

		for(k=0;k<1300;k++);        // Delay to show clock Rotation  

	} // End of while(1) 
} // End of main 

void clock_wise(void) { 
	var1 = 0x00000008;         //For Clockwise 
	for(i=0;i<=3;i++)         // for A B C D Stepping 
	{ 
		var1 = var1<<1;        //For Clockwise 
		LPC_GPIO0->FIOPIN = var1; 

		for(k=0;k<3000;k++); //for step speed variation          
	} 
} 

void anti_clock_wise(void) 
{ 
	var1 = 0x00000100;      //For Anticlockwise 
	for(i=0;i<=3;i++)       // for A B C D Stepping 
	{ 
		var1 = var1>>1;      //For Anticlockwise 
		LPC_GPIO0->FIOPIN = var1; 

		for(k=0;k<3000;k++); //for step speed variation  
	}
}
