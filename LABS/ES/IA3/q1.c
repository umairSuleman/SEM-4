#include<LPC17xx.h>

unsigned int LED={255, 126, 60, 24, 24, 60, 126, 255};

unsigned int i,j;

int main(void){
  SystemInit();
  SystemCoreClockUpdate();
  
  LPC_PINCON->PINSEL0 &= 0xFF0000FF;
  LPC_GPIO0->FIODIR |= 0x0FF0;

  LPC_PINCON->PINSEL3 &= 0xFFCFFFFF;
  LPC_GPIO1->FIODIR &= ~(1<<26);

  i=0;

  while(1){
    while((LPC_GPIO1->FIOPIN >> 26) & 1){
      LPC_GPIO1->FIOPIN=LED[i]<<4;
      for(j=0; j<10000; j++);
      i++;
      if(i>7)
        i=0;
    }
  }
}

  
