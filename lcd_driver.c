#include "lcd_defines.h"
#include "delay.h"
void init_lcd(void)
{
	IODIR0|=(1<<RS)|(1<<RW)|(1<<EN);
	IODIR0|=(0XFF<<LED);
	delay_ms(20);
	cmd_lcd(0x30);
	delay_ms(10);
	cmd_lcd(0x30);
	delay_ms(5);
	cmd_lcd(0x30);
	delay_ms(5);
	cmd_lcd(0x38);
	cmd_lcd(0x10);
	cmd_lcd(0x01);
	cmd_lcd(0x06);
	cmd_lcd(0x0c);
}
void cmd_lcd(char num)
{
	IOCLR0=0XFF<<LED;
	IOCLR0=1<<RS;
	IOSET0=num<<LED;
	IOSET0=1<<EN;
	delay_ms(2);
	IOCLR0=1<<EN;
}
void data_lcd(char num)
{
	IOCLR0=0XFF<<LED;
	IOSET0=1<<RS;
	IOCLR0=1<<RW;
	IOSET0=num<<LED;
	IOSET0=1<<EN;
	delay_ms(2);
	IOCLR0=1<<EN;
}
void char_lcd(char data)
{
	data_lcd(data);
}
void int_lcd(int num)
{
	int rev=0,temp,zero=0;
	temp=num;
	if(num==0)
	{
		char_lcd('0');
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
		char_lcd((temp%10)+'0');
	}
	while(zero--)
	{
		char_lcd('0');
	}
}
void string_lcd(char *p)
{
	while(*p)
	{
		char_lcd(*p);
		p++;
	}
}
void cus_char(char *p)
{
	int i;
	for(i=0;i<8;i++)
	{
		char_lcd(p[i]);
	}
}
