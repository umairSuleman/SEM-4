#include<LPC17xx.h>

//Say Pclk=25 MHz, Tres=1 micro second

void initTimer0(void){
  LPC_TIM0->CTCR=0x0;      //set to timer mode
  LPC_TIM0->TCR=0x2;       //reset timer
  LPC_TIM0->PR=24;         //PR=(Pclk * Tres)-1 =(25 * 10^6 * 10^-6)-1 = 25-1= 24
}

void delay(unsigned int ms){
  LPC_TIM0->MR0=1000*ms;                      //set the delay time
  LPC_TIM0->TCR=0x1;                          //start timer
  while(LPC_TIM0->TC < LPC_TIM0->MR0);        //wait until delay is over
  LPC_TIM0->TCR=0x0;                          //stop timer
  LPC_TIM0->TCR=0x2;                          //reset timer
}

int main(void){
  initTimer0();
  while(1){
    delay(100);    //generate a delay of 100ms=0.1s
  }
}
  

