#include<lpc21xx.h>
#include "uart.h"
char buff[300],store,ch;
int i;
void uart_rx(void) __irq
{
	if(U0IIR&0X04)
	{
		ch=U0RBR;
		if(i<299)
			buff[i++]=ch;
	}
	else
	{
		store=U0IIR;
	}
		VICVectAddr=0;
}
void init_inter()
{
	VICIntSelect = 0x00000000; // IRQ
  VICVectAddr0 = (unsigned)uart_rx;
  VICVectCntl0 = 0x20 | 6; /* UART0 Interrupt */
  VICIntEnable = 1 << 6;   /* Enable UART0 Interrupt */
  U0IER = 0x03;  
}
