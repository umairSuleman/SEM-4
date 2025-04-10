#include <LPC17xx.h>
#include <stdio.h>
#include "AN_LCD.h"

#define Ref_Vtg 3.300    // Reference voltage (3.3V)
#define Full_Scale 0xFFF // 12-bit ADC scale (4095)

volatile unsigned int adc_result4 = 0, adc_result5 = 0;
volatile unsigned int channel = 0;

void ADC_IRQHandler(void) {
    unsigned long adc_data = LPC_ADC->ADGDR;
    channel = (adc_data >> 24) & 0x7;
    unsigned int result = (adc_data >> 4) & 0xFFF;

    if (channel == 4) adc_result4 = result;
    else if (channel == 5) adc_result5 = result;
}

int main(void) {
    float in_vtg1, in_vtg2, in_vdiff;
    char vtg1[6], vtg2[6], vdiff[6];
    char Msg3[] = "CH4,5:";
    char Msg4[] = "V Diff: ";

    SystemInit();
    SystemCoreClockUpdate();
    LPC_SC->PCONP |= (1 << 15); // Power GPIO
    lcd_init();

    // Configure P1.30 (AD0.4) and P1.31 (AD0.5)
    LPC_PINCON->PINSEL3 |= (3 << 28) | (3 << 30);

    LPC_SC->PCONP |= (1 << 12); // Power ADC
    LPC_ADC->ADCR = (1 << 4) | (1 << 5) | (1 << 16) | (1 << 21); // Burst mode
    LPC_ADC->ADINTEN = (1 << 4) | (1 << 5); // Enable interrupts
    NVIC_EnableIRQ(ADC_IRQn);

    // Display static messages
    lcd_comdata(0x80, 0);
    delay_lcd(800);
    lcd_puts(Msg3);
    lcd_comdata(0xC0, 0);
    delay_lcd(800);
    lcd_puts(Msg4);

    while (1) {
        // Calculate voltages
        in_vtg1 = ((float)adc_result4 * Ref_Vtg) / Full_Scale;
        in_vtg2 = ((float)adc_result5 * Ref_Vtg) / Full_Scale;
        in_vdiff = in_vtg1 - in_vtg2;

        // Convert to strings
        sprintf(vtg1, "%3.2f", in_vtg1);
        sprintf(vtg2, "%3.2f", in_vtg2);
        sprintf(vdiff, "%3.2f", in_vdiff);

        // Display on LCD
        lcd_comdata(0x86, 0); // CH4 value
        delay_lcd(800);
        lcd_puts(vtg1);
        lcd_comdata(0x8B, 0); // CH5 value
        delay_lcd(800);
        lcd_puts(vtg2);
        lcd_comdata(0xC8, 0); // Voltage difference
        delay_lcd(800);
        lcd_puts(vdiff);

        for (volatile int i = 0; i < 200000; i++); // Delay

        // --- Reset Values for Next Iteration ---
        adc_result4 = 0;
        adc_result5 = 0;
        in_vtg1 = 0;
        in_vtg2 = 0;
        in_vdiff = 0;
        for (int i = 0; i < 6; i++) {
            vtg1[i] = 0;
            vtg2[i] = 0;
            vdiff[i] = 0;
        }
    }
}
