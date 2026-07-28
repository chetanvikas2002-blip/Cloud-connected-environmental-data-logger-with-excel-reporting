#include<lpc21xx.h>
#include "interrupt.h"
void init_interrupt()
{
	PINSEL1=PINSEL1&~(3<<(16-EINT0_PIN));
	PINSEL1=PINSEL1|(1<<(16-EINT0_PIN));
	VICIntEnable|=(1<<EINT0_CH);
	VICVectCntl1=(EINT0_CH)|(1<<5);
	VICVectAddr1=(unsigned int)sw_pressed;
	EXTINT=1<<0;
	EXTMODE=1<<0;
	EXTPOLAR=0<<0;
}
/*void init_mq2_int()
{
		PINSEL1=PINSEL1&~(3<<(2*(30-16)));
		PINSEL1=PINSEL1|(2<<28);
		VICIntEnable|=(1<<EINT3_CH);
		VICVectCntl2=(EINT3_CH)|(1<<5);
		VICVectAddr2=(unsigned)smoke_alert;
		EXTINT=1<<3;
		EXTMODE=1<<3;
		EXTPOLAR=1<<3;	
}*/
