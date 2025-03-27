#include<LPC17xx.h>

unsigned char tohex[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6d, 0x7d, 0x07};

unsigned char scan_code[]={0x11, 0x21, 0x41, 0x81, 0x12, 0x22, 0x42, 0x82};

unsigned int row, flag, i, j;

unsigned char upper_nibble, key, var1;

void initSSD(){

    //Setting p2.0-p2.7 as outputs for display
    LPC_GPIO2->FIODIR |= 0xFF;

    //Setting p1.15-p1.18 as outputs for display
    LPC_GPIO1->FIODIR |= (0xF << 15);
}

void initKeyboard(){

    //Setting p0.8-p0.11 as outputs for display
    LPC_GPIO0->FIODIR |= 0xF00;

    //Setting p0.4-p0.7 as outputs for display
    LPC_GPIO0->FIODIR &= ~(0XF0);
}

void scan(unsigned char lower_nibble){

    upper_nibble=LPC_GPIO0->FIOPIN;
    upper_nibble &= 0xF0;                       //extract values

    if(upper_nibble != 0x0){
        flag=1;
        lower_nibble >>=8;                      //shift to lower_nibble 
        key= upper_nibble | lower_nibble;       //combine to get scan_code
    }
}

int main(void){

    SystemInit();
    SystemCoreClockUpdate();

    initSSD();
    initKeyboard();

    while(1){
        while(1){
            for(row=1; row<=2; row++){
                if(row==1){
                    var1=0x100;
                else
                    var1=0x200;

                LPC_GPIO0->FIOCLR=(0XF << 8);
                LPC_GPIO0->FIOSET= var1;

                flag=0;
                scan(var1);
                if(flag==1)     //breaks out for for loop when value is pressed
                    break;
        
                }
            }
            if(flag==1)         //break out of inner while(1)
                break
        }

        for(i=0; i<8; i++){
            if(key==scan_code[i]){
                key=tohex[i];
                break;
            }
        }
        LPC_GPIO1->FIOPIN =(0<<15);
        LPC_GPIO2->FIOPIN = key;
        for(j=0; j<10000; j++);
    }
}
