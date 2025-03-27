#include<LPC17xx.h>

unsigned int temp1, temp2, type, i=0;

unsigned char temp3;

void delay(unsigned int ms){
    LPC_TIM0->CTCR= 0X0;
    LPC_TIM0->TCR=0X2;
    LPC_TIM0->PR=119;
    LPC_TIM0->MR0 =ms*100;
    LPC_TIM0->MCR=2;
    LPC_TIM0->TCR=0X1;

    while(LPC_TIM0->TC < LPC_TIM0-> MR0);
    LPC_TIM0->TCR= 0X0;
}

void lcd_init(){

	//Ports initialized as GPIO 
 	LPC_PINCON->PINSEL1 &= 0xFC003FFF; //P0.23 to P0.28
	//Setting the directions as output 
 	LPC_GPIO0->FIODIR |= 0x0F<<23 | 1<<27 | 1<<28;      //23-26:D4-D7  27:RS  28:EN
 
 	clear_ports();
	delay_lcd(3200);

	lcd_comdata(0x33, 0);   //Ensures proper set up of 8 bit mode
	delay_lcd(30000); 

	lcd_comdata(0x32, 0);   //Converts from 8 bit mode to 4 bit mode (D4/DL=0)
	delay_lcd(30000);

	lcd_comdata(0x28, 0);   //Function set  (0010 1111)(d7-d0)
    delay_lcd(30000);

    lcd_comdata(0x0c, 0);   //Display(D): on(1) cursor(C): off(0) == (0000 1100) (0000 1DCB) {B:Cursor Blink}
    delay_lcd(800);

    lcd_comdata(0x06, 0);   //Entry mode set increment(I/D==1) cursor right == (0000 0110) (0000 01 I/D S)
    delay_lcd(800);

    lcd_comdata(0x01, 0);   //Display clear (0000 0001)
    delay_lcd(10000);

    return;
}

void lcd_comdata(int temp1, int type){
    int temp2 = temp1 & 0xf0;       //Upper Nibble 
    temp2 = temp2 << 19;            //Shift to data lines (23-4=19)
    write(temp2, type);

    temp2 = temp1 & 0x0f;           //Lower Nibble
    temp2 = temp2 << 23;            // Shift to data lines (23-0=23)
    write(temp2, type);

    delay_lcd(1000);
    return;
}

//write to command/data reg
void write(int temp2, int type){
    clear_ports();
    LPC_GPIO0->FIOPIN = temp2;      // Assign the value to the data lines 

    if(type==0){
        LPC_GPIO0->FIOCLR = 1<<27;  // RS=0 : COMMAND REGISTER
    }
    else{
        LPC_GPIO0->FIOSET = 1<<27;  // RS=1 : DATA REGISTER
    }

    // Send Throbbing Signal to Latch 
    LPC_GPIO0->FIOSET = 1<<28;      // EN=1
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = 1<<28;      // EN =0
    return;
}

//random delays
void delay_lcd(unsigned int r1){
    unsigned int r;
    for(r=0;r<r1;r++);
    return;
}

void clear_ports(void){
    /* Clearing the lines at power on */
    LPC_GPIO0->FIOCLR = 0x0F<<23;       //Clearing data lines
    LPC_GPIO0->FIOCLR = 1<<27;          //Clearing RS line
    LPC_GPIO0->FIOCLR = 1<<28;          //Clearing Enable line
 
    return;
}

void lcd_puts(unsigned char *buf1){
    unsigned int i=0;
    unsigned int temp3;
    while(buf1[i]!='\0')
    {
        temp3 = buf1[i];
        lcd_comdata(temp3, 1);
        i++;
        if(i==16)
        {
            lcd_comdata(0xc0, 0);   //move to next line if space over in first line
        }

    }
    return;
}

int main(void){
    
    unsigned char Msg[]={"Hello world"};

    SystemInit();
    SystemCoreClockUpdate();

    lcd_init();

    lcd_comdata(0x80, 0);
    delay_lcd(800);
    lcd_puts(&Msg[0]);

    delay(5000);

    lcd_comm(0x1,0)
}
