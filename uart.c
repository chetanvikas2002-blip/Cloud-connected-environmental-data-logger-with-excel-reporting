#include <LPC21xx.H> 

#include "uart.h"
#include "lcd_defines.h"
void init_uart (void) 
{  
            		
  PINSEL0 = PINSEL0&~(15<<0); 
	PINSEL0=PINSEL0|(5<<0);
  U0LCR = 0x83;         
  U0DLL = 97 ;        
	U0DLM = 0;
  U0LCR = 0x03;         
  
  #if UART_INT_ENABLE > 0

  VICIntSelect = 0x00000000; 
  VICVectAddr0 = (unsigned)UART0_isr;
  VICVectCntl0 = 0x20 | 6; 
  VICIntEnable = 1 << 6;  
 
  U0IER = 0x03;      
             
  #endif
						
}

void tx_uart(char ch) 
{ 
	U0THR = ch;  
  while (!(U0LSR & 0x20));              
}

char rx_uart(void)    
{                     
  while (!(U0LSR & 0x01));
  return (U0RBR);
}

void string_uart(char *s)
{
   while(*s)
	 {
       tx_uart(*s);
				s++;
	 }
}

void int_uart(unsigned int num)
{
 int rev=0,temp,zero=0;
	temp=num;
	if(num==0)
	{
		tx_uart('0');
		return ;
	}
	if((temp%1000)==0)
	{
		zero=3;
	}
	else if((temp%100)==0)
	{
		zero=2;
	}
	else if((temp%10)==0)
	{
		zero=1;
	}
	for(;temp!=0;temp/=10)
	{
		rev=rev*10+(temp%10);
	}
	temp=rev;
	for(;temp!=0;temp/=10)
	{
		tx_uart((temp%10)+'0');
	}
	while(zero--)
	{
		tx_uart('0');
	}
}

void float_uart(float f)
{
  int x;
  float temp;
  x=f;
  int_uart(x);
  tx_uart('.');
  temp=(f-x)*100;
  x=temp;
  int_uart(x);
}
void disp_time(int h,int m,int s)
{
	string_uart("Time:");
	int_uart(h);
	tx_uart(':');
	int_uart(m);
	tx_uart(':');
	int_uart(s);
	string_uart("\r\n");
}
