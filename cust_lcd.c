#include<lpc21xx.h>
#include "lcd_defines.h"
void cust_lcd()
{
	char cus[]={0X0C,0X12,0X12,0X0C,0X00,0X00,0X00,0X00};
	cmd_lcd(0x40);
	cus_char(cus);
}
