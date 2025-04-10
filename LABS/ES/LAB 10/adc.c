/*
Write a C program to display the digital value representing the difference in 
analog voltages at ADC channel 4 and channel 5 on LCD using BURST and 
Software mode. 
*/

#include <LPC17xx.h>
#include <stdio.h>
#include "AN_LCD.h"
#define Ref_Vtg 3.300    // Reference voltage (3.3V)
#define Full_Scale 0xFFF // 12-bit ADC scale (4095 in decimal)

int main(void)
{
    unsigned long adc_temp1, adc_temp2;
    unsigned int i;
    float in_vtg1, in_vtg2, in_vdiff;
    unsigned char vtg1[6], vtg2[6], vdiff[6];
    unsigned char Msg3[] = {"CH4,5:"};
    unsigned char Msg4[] = {"V Diff: "};
    
		SystemInit();
    SystemCoreClockUpdate();
    
		LPC_SC->PCONP |= (1 << 15); // Power for GPIO block
    lcd_init();
    
		LPC_PINCON->PINSEL3 |= 0x30000000; // P1.30 as AD0.4
    LPC_PINCON->PINSEL3 |= 0xC0000000; // P1.31 as AD0.5
    
		LPC_SC->PCONP |= (1 << 12);        // enable the peripheral ADC
    
		SystemCoreClockUpdate();
		
    //Displaying CH4,5: in line 1 at the beginning
		lcd_comdata(0x80, 0);
    delay_lcd(800);
    lcd_puts(&Msg3[0]);
		
    //Displaying V Diff: in line 2 at the beginning
		lcd_comdata(0xC0, 0);
    delay_lcd(800);
    lcd_puts(&Msg4[0]);
    
		// Burst mode and software trigger configuration
		// Burst mode - ADC performs multiple conversions in rapid succession without requiring a separate trigger for each
		LPC_ADC->ADCR = (1 << 4) | (1 << 5) | (1 << 21) | (1 << 16);
										//CH4,		CH5,		Enables ADC clock, starts the ADC conversion using software triggering
		while (1){
				// wait till 'done' bit is 1, indicates conversion complete
        while (!(LPC_ADC->ADDR5 & (1 << 31)));
        
        adc_temp1 = LPC_ADC->ADDR4;	//reads the ADC result from ch4
        adc_temp1 >>= 4; //Data is stored from 4th bit onwards => right shift
        adc_temp1 &= 0xFFF; //Extracting the 12-bit ADC data
        
				adc_temp2 = LPC_ADC->ADDR5;
        adc_temp2 >>= 4;
        adc_temp2 &= 0x00000FFF; // 12 bit ADC
        
				//Calculating input analog voltage and their difference
				in_vtg1 = (((float)adc_temp1 * (float)Ref_Vtg)) / ((float)Full_Scale);
        in_vtg2 = (((float)adc_temp2 * (float)Ref_Vtg)) / ((float)Full_Scale);
        in_vdiff = in_vtg1 - in_vtg2;
			
				//Converting value into a string
        sprintf(vtg1, "%3.2f", in_vtg1);
        sprintf(vtg2, "%3.2f", in_vtg2);
				sprintf(vdiff, "%3.2f", in_vdiff);
			
        for (i = 0; i < 2000; i++); //Delay
        
				lcd_comdata(0x86, 0); //Displaying V1 in line 1 after string
        delay_lcd(800);
        lcd_puts(&vtg1[0]);
        
				lcd_comdata(0x8B, 0); //Displaying V2 in line 1 after V1
        delay_lcd(800);
        lcd_puts(&vtg2[0]);
				
				lcd_comdata(0xC8, 0); //Displaying V1-V2 in line 2 after string
        delay_lcd(800);
        lcd_puts(&vdiff[0]);
				
        for (i = 0; i < 200000; i++); //Delay
        
				//Resetting
				for (i = 0; i < 7; i++)
            vtg1[i] = vtg2[i] = 0;
        
				adc_temp1 = 0;
        in_vtg1 = 0;
        adc_temp2 = 0;
        in_vtg2 = 0;
    }
}
