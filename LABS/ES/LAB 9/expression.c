#include<LPC17xx.h>
//variable declarations
unsigned char A, B, operator, equal, tens, ones;

unsigned int result, row, flag;

unsigned char var1, key;

unsigned char scan_codes[]={0x11, 0x21, 0x41, 0x81, 
                            0x12, 0x22, 0x42, 0x82, 
                            0x14, 0x24};

unsigned char ascii_codes[]={'0', '1', '2', '3',
                             '4', '5', '6', '7', 
                             '8', '9'};


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

    SystemInit();
    SystemCoreClockUpdate();


    //Initialise Keyboard

    //Initialise rows as output (P2.10-P2.13)
    LPC_GPIO2->FIODIR |= 0X00003C00;
    
    //Initialise cols as input (P1.23-P1.26)
    LPC_GPIO1->FIODIR &= 0xF87FFFFF;

    //Set lcd as output
    LPC_GPIO0->FIODIR |= 0X0F<<23 | 1<<27 | 1<<28;
    clear_ports();
    delay_lcd(32000);

    lcd_init();

    lcd_comdata(0x80,0);    //points to first line of LCD
    delay_lcd(800);

    do{
        A=readKeyboard();
    }while(A<'0' || A>'9');

    lcd_puts(&A[0]);

    do{
        operator=readKeyboard();
    }while(operator != '+' || operator != '-');

    lcd_puts(&operator[0]);

    do{
        B=readKeyboard();
    }while(B<'0' || B>'9');

    lcd_puts(&B[0]);

    do {
        equal=readKeyboard();
    } while (equal != '=');

    lcd_data(&equal[0]);

    // Convert ASCII to Integer
    A -= '0';
    B -= '0';

    // Perform Calculation
    if (operator == '+')
        result = A + B;
    else if (operator == '-')
        result = A - B;

    tens=result/10 + '0';
    ones=result%10 +'0';
    lcd_cmd(0xC0,0);
    delay_lcd(800);
    lcd_puts(&tens[0]);
    lcd_puts(&ones[0]); 
}   

unsigned char readKeyboard(){
    for(row=1; row<=3; row++){
        if(row==1)
            var1=0x400;
        else if(row==2)
            var1=0x800;
        else 
            var1=0x1000;

        temp1=var1;

        LPC_GPIO2->FIOCLR=0X3C00;
        LPC_GPIO2->FIOSET=var1;

        flag=0;
        scan(temp1);
        if(flag)
            break;
    }
    for(i=0; i<10; i++){
        if(key==scan_code[i]){
            key=ascii_code[i];
            break;
        }
    }

    return key;
}

void scan(unsigned char temp1){
    temp3=LPC_GPIO1->FIOPIN;
    temp3 &= 0x07800000;
    if(temp3 != 0x0){
        flag=1;
        temp3 >>=19;
        temp1 >>=10;
        key= temp3 | temp;
    }
}
