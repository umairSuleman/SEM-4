#include <LPC17xx.h>

// Array for converting digits 0-9 to their 7-segment display encoding
unsigned char tohex[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// Array to represent the digits we want to display ("1234")
unsigned char digits[4] = {4,3,2,1};

unsigned int i = 0, j = 0;

int main() {
    SystemInit();
    SystemCoreClockUpdate();

    // Configure GPIO pins for the 7-segment displays
    // GPIO0 pins 0 to 7 will be used for the 7-segment segment control (8 bits)
    LPC_GPIO0->FIODIR |= 0xFF0;  // Set bits 4-11 as output for the segments of 7-segment

    // GPIO1 pins 23 to 26 will be used for digit selection (4 bits for 4 digits)
    LPC_GPIO1->FIODIR |= 0xF << 23;  // Set bits 23-26 as output for selecting digits
    
    while(1) {
        for(i = 0; i < 4; i++) {
            // Select the current digit (activate the appropriate digit by shifting 1 to the correct bit)
            LPC_GPIO1->FIOPIN = (i << 23);  // Activate one of the four digits (0-3), behaves like a mux - 00, 01, 10, 11 (NOT one hot encoded)
            
            // Send the corresponding 7-segment pattern for the current digit
            LPC_GPIO0->FIOPIN = tohex[digits[i]] << 4;  // Shift the 7-segment pattern for the current digit

            for(j = 0; j < 100000; j++);  // random delay
        }
    }
    return 0;
}
