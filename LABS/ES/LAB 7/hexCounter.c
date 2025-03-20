#include <LPC17xx.h>

// Mapping for hexadecimal digits 0–F to seven-segment encodings.
// Adjust these codes as needed for your seven-segment wiring.
unsigned char hexTo7Seg[16] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // b
    0x39, // C
    0x5E, // d
    0x79, // E
    0x71  // F
};

unsigned int counter = 0x0000;  // 4-digit hex counter, start at 0000
unsigned int countDown = 0;     // 0 = count up; 1 = count down

//---------------------------------------------------------
// Initialize Timer0 for generating 1 ms ticks
//---------------------------------------------------------
void initTimer0(void) {
    LPC_SC->PCONP |= (1 << 1);         // Power up Timer0
    LPC_SC->PCLKSEL0 &= ~(0x3 << 3);     // Clear bits for Timer0 clock
    LPC_SC->PCLKSEL0 |=  (0x1 << 3);     // Set clock for Timer0 to CCLK

    LPC_TIM0->CTCR = 0x0;              // Timer mode: timer mode (not counter)
    LPC_TIM0->PR = 999;                // Prescaler: assuming a 25MHz clock gives a 1 ms tick
    LPC_TIM0->TCR = 0x02;              // Reset Timer0
}

//---------------------------------------------------------
// Read the switch state (assumes active low on P2.10)
//---------------------------------------------------------
unsigned int readSwitch(void) {
    return (LPC_GPIO2->FIOPIN & (1 << 10)) ? 1 : 0;
}

//---------------------------------------------------------
// Main function
//---------------------------------------------------------
int main(void) {
    unsigned int temp;  // Used for digit extraction

    SystemInit();
    SystemCoreClockUpdate();

    initTimer0();

    // Setup GPIO:
    // Configure GPIO0 pins 4 to 11 as outputs for seven-segment segments.
    LPC_GPIO0->FIODIR |= 0xFF0;
    // Configure GPIO1 pins 23 to 26 as outputs for digit selection.
    LPC_GPIO1->FIODIR |= (0xF << 23);
    // Configure GPIO2 pin 10 as input for the switch.
    LPC_GPIO2->FIODIR &= ~(1 << 10);
    // (Optional: configure pull-up resistors for P2.10 as needed.)

    while (1) {
        // Check switch state to determine counting direction.
        // Assume: switch pressed (logic 0) means count down; released (logic 1) means count up.
        if (readSwitch() == 0) {
            countDown = 1;
        } else {
            countDown = 0;
        }
        
        // Reset and start Timer0 to measure a 1-second period.
        LPC_TIM0->TCR = 0x02;  // Reset Timer
        LPC_TIM0->TCR = 0x01;  // Start Timer

        // Continue multiplexing the display until 1 second has elapsed.
        while (LPC_TIM0->TC < 1000) {
            temp = counter;

            // Display digit 0 (least significant)
            LPC_GPIO1->FIOPIN = (0 << 23);
            LPC_GPIO0->FIOPIN = hexTo7Seg[temp & 0xF] << 4;
            for(i=0; i<1000; i++);
          
            temp >>= 4;
            // Display digit 1
            LPC_GPIO1->FIOPIN = (1 << 23);
            LPC_GPIO0->FIOPIN = hexTo7Seg[temp & 0xF] << 4;
            for(i=0; i<1000; i++);
          
            temp >>= 4;
            // Display digit 2
            LPC_GPIO1->FIOPIN = (2 << 23);
            LPC_GPIO0->FIOPIN = hexTo7Seg[temp & 0xF] << 4;
            for(i=0; i<1000; i++);
            
            temp >>= 4;
            // Display digit 3 (most significant)
            LPC_GPIO1->FIOPIN = (3 << 23);
            LPC_GPIO0->FIOPIN = hexTo7Seg[temp & 0xF] << 4;
            for(i=0; i<1000; i++);
        }
        
        LPC_TIM0->TCR = 0x00;  // Stop Timer0 after 1 second period

        // Update the counter based on the counting direction.
        if (countDown) {
            // Count down; wrap from 0x0000 to 0xFFFF.
            if (counter == 0)
                counter = 0xFFFF;
            else
                counter--;
        } else {
            // Count up; wrap from 0xFFFF to 0x0000.
            if (counter == 0xFFFF)
                counter = 0;
            else
                counter++;
        }
    }
    
    // The program never reaches here.
    return 0;
}
