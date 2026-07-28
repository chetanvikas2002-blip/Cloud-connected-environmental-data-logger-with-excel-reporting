#include<lpc21xx.h>
#include "24lc01.h"
#include "i2c.h"
#include "delay.h"
void byte_write(char addr,short int baddr,char ch)
{
	start();
	write(addr<<1);
	write(baddr>>8);
	write(baddr);
	write(ch);
	stop();
	delay_ms(10);
}
char byte_read(char addr,short int baddr)
{
	char store;
	start();
	write(addr<<1);
	write(baddr>>8);
	write(baddr);
	rep_start();
	write(addr<<1|1);
	store=nack();
	stop();
	return store;
}
void page_write(char addr,short int baddr,char *p)
{
	start();
	write(addr<<1);
	write(baddr>>8);
	write(baddr);
	while(*p)
	{
		write(*p);
		p++;
	}
	write(*p);
	stop();
	delay_ms(10);
}
void seq_read(char addr,short int baddr,char *ch)
{
	int i,j=0;
	ch[0]='a';
	start();
	write(addr<<1);
	write(baddr>>8);
	write(baddr);
	rep_start();
	for(i=0;ch[i];i++)
	{
		ch[j++]=mack();
	}
	nack();
	stop();
}

