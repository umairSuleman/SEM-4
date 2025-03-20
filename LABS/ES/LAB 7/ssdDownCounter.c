#include <LPC17xx.h>

// Mapping of digits 0-9 to their 7-segment display encoding
unsigned char tohex[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

unsigned int counter = 9999; // Start at 9999

// Initialize Timer0 for delay generation
void initTimer0(void) {
    LPC_SC->PCONP |= (1 << 1);          // Power up Timer0
    LPC_SC->PCLKSEL0 &= ~(0x3 << 3);      // Clear bits first
    LPC_SC->PCLKSEL0 |= (0x1 << 3);       // Set clock for Timer0 to CCLK

    LPC_TIM0->CTCR = 0x0;               // Timer mode: timer mode (not counter)
    LPC_TIM0->PR = 999;                 // Prescaler: assuming 25MHz clock for ~1ms tick
    LPC_TIM0->TCR = 0x02;               // Reset timer
}

// Delay function using Timer0. Delay is in milliseconds.
void delay(unsigned int millisec) {
    LPC_TIM0->TCR = 0x02;               // Reset Timer
    LPC_TIM0->TCR = 0x01;               // Enable Timer
    while (LPC_TIM0->TC < millisec);    // Wait until the timer counter reaches the desired delay
    LPC_TIM0->TCR = 0x00;               // Disable Timer
}

int main(void) {
    unsigned int temp;  // Temporary variable to extract digits

    SystemInit();
    SystemCoreClockUpdate();

    initTimer0();

    // Configure GPIO0 pins 4 to 11 as outputs for the 7-segment display segments
    LPC_GPIO0->FIODIR |= 0xFF0;
    
    // Configure GPIO1 pins 23 to 26 as outputs for selecting the 7-segment digit
    LPC_GPIO1->FIODIR |= (0xF << 23);

    while (1) {
        // Use Timer0 to create an overall delay of approximately 1 second 
        // during which the multiplexing occurs continuously.
        LPC_TIM0->TCR = 0x02; // Reset Timer
        LPC_TIM0->TCR = 0x01; // Enable Timer
        
        // Multiplex for 1000ms before decrementing the counter
        while (LPC_TIM0->TC < 1000) {
            temp = counter;
            
            // Display digit in position 0 (least significant)
            LPC_GPIO1->FIOPIN = (0 << 23);
            LPC_GPIO0->FIOPIN = tohex[temp % 10] << 4;
            delay(1);  // 1ms delay for this digit

            temp /= 10;
            // Display digit in position 1
            LPC_GPIO1->FIOPIN = (1 << 23);
            LPC_GPIO0->FIOPIN = tohex[temp % 10] << 4;
            delay(1);

            temp /= 10;
            // Display digit in position 2
            LPC_GPIO1->FIOPIN = (2 << 23);
            LPC_GPIO0->FIOPIN = tohex[temp % 10] << 4;
            delay(1);

            temp /= 10;
            // Display digit in position 3 (most significant)
            LPC_GPIO1->FIOPIN = (3 << 23);
            LPC_GPIO0->FIOPIN = tohex[temp % 10] << 4;
            delay(1);
        }
        
        LPC_TIM0->TCR = 0x00; // Disable Timer after multiplexing loop

        // Decrement the counter; if it reaches 0, wrap around to 9999
        counter--;
        if (counter == 0)
            counter = 9999;
    }
}
