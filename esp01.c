#include <string.h>
#include "uart.h"
#include "delay.h"
#include "lcd_defines.h"

extern char buff[300];
extern int i;

int esp01_connectAP_AT()
{
	int time_out=0;
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd("AT");
	//delay_ms(1000);
	string_uart("AT\r\n");
	i=0;memset(buff,'\0',300);
	while((i<3)&&(time_out<20))
	{
		delay_ms(10);
		time_out++;
	}
	if(time_out>=20)
	{
		return -1;
	}
	delay_ms(500);
	buff[i] = '\0';
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd(buff);
	delay_ms(2000);
	if(strstr(buff,"OK"))
	{
			return 1;
		//cmd_lcd(0xC0);
		//string_lcd("OK");
		//delay_ms(1000);		
	}
	else
	{
		//cmd_lcd(0xC0);
		//string_lcd("ERROR");
		//delay_ms(1000);		
		return 0;
	}
	//return 1;
}	
int esp01_connectAP_ATE0()	
{
	int time_out=0;
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd("ATE0");
	//delay_ms(1000);
	string_uart("ATE0\r\n");
	i=0;memset(buff,'\0',300);
	while((i<4)&&(time_out<20))
	{
		delay_ms(10);
		time_out++;
	}
	if(time_out>=20)
	{
		return -1;
	}
	delay_ms(500);
	buff[i] = '\0';
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd(buff);
	delay_ms(2000);
	if(strstr(buff,"OK"))
	{
		//cmd_lcd(0xC0);
		//string_lcd("OK");
		//delay_ms(1000);		
		return 1;
	}
	else
	{
		//cmd_lcd(0xC0);
		//string_lcd("ERROR");
		//delay_ms(1000);		
		return 0;
	}
	//return 1;
}
int esp01_connectAP_TCP_MODE()
{
	int time_out=0;
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd("AT+CIPMUX");
	//delay_ms(1000);
	string_uart("AT+CIPMUX=0\r\n");
	i=0;memset(buff,'\0',300);
	while((i<4)&&(time_out<20))
	{
		delay_ms(10);
		time_out++;
	}
	if(time_out>=20)
	{
		return -1;
	}
	delay_ms(500);
	buff[i] = '\0';
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd(buff);
	delay_ms(2000);
	if(strstr(buff,"OK"))
	{
		//cmd_lcd(0xC0);
		//string_lcd("OK");
		//delay_ms(1000);		
		return 1;
	}
	else
	{
		//cmd_lcd(0xC0);
		//string_lcd("ERROR");
		//delay_ms(1000);		
		return 0;
	}
	//return 1;
}
int esp01_connectAP_QUIT_AP()
{
	int time_out=0;
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd("AT+CWQAP");
	delay_ms(1000);
	string_uart("AT+CWQAP\r\n");
	i=0;memset(buff,'\0',300);
	while((i<4)&&(time_out<20))
	{
		delay_ms(10);
		time_out++;
	}
	if(time_out>=20)
	{
		return -1;
	}
	delay_ms(1500);
	buff[i] = '\0';
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd(buff);
	delay_ms(2000);
	if(strstr(buff,"OK"))
	{
		//cmd_lcd(0xC0);
		//string_lcd("OK");
		//delay_ms(1000);		
		return 1;
	}
	else
	{
		//cmd_lcd(0xC0);
		//string_lcd("ERROR");
		//delay_ms(1000);		
		return 0;
	}
	//return 1;
}
	
int esp01_connectAP_JOIN_AP()
{
	int time_out=0;
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd("AT+CWJAP");
	//delay_ms(1000);
	//need to change the wifi network name and password
	string_uart("AT+CWJAP=\"bhagya,\"123456789\"\r\n");
	i=0;memset(buff,'\0',300);
	while((i<4)&&(time_out<20))
	{
		delay_ms(10);
		time_out++;
	}
	if(time_out>=20)
	{
		return -1;
	}
	delay_ms(2500);
	buff[i] = '\0';
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd(buff);
	delay_ms(2000);
	if(strstr(buff,"WIFI CONNECTED"))
	{
		//cmd_lcd(0xC0);
		//string_lcd("OK");
		//delay_ms(1000);		
		return 1;
	}
	else
	{
		//cmd_lcd(0xC0);
		//string_lcd("ERROR");
		//delay_ms(1000);		
		return 0;
	}
		//return 1;
}

int esp01_sendToThingspeak(int field,int num)
{
	int len=0,temp,time_out=0;
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd("AT+CIPSTART");
	//delay_ms(1000);
	string_uart("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
	i=0;memset(buff,'\0',300);
	while((i<5)&&(time_out<20))
	{
		delay_ms(10);
		time_out++;
	}
	if(time_out>=20)
	{
		return -1;
	}
	time_out=0;
	delay_ms(2500);
	buff[i] = '\0';
	//cmd_lcd(0x01);
	//cmd_lcd(0x80);
	//string_lcd(buff);
	delay_ms(2000);
	if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
	{
		//cmd_lcd(0xC0);
		//string_lcd("OK");
		//delay_ms(1000);
		
		//cmd_lcd(0x01);
		//cmd_lcd(0x80);
		//string_lcd("AT+CIPSEND");
		//delay_ms(1000);
		temp=num;
		for(;temp!=0;temp/=10)
		{
			len++;
		}		
		if(num==0)
		{
			len=1;
		}
		string_uart("AT+CIPSEND=");
		int_uart(48+len);
		string_uart("\r\n");								
		i=0;memset(buff,'\0',300);
		delay_ms(500);
		string_uart("GET /update?api_key=4ZSWECQKOEYFW3ZT&field");
		int_uart(field);
		tx_uart('=');
		int_uart(num);
		string_uart("\r\n\r\n");
		//string_uart("AT\r\n");
		delay_ms(5000);
		//delay_ms(2000);
		buff[i] = '\0';
		//cmd_lcd(0x01);
		//cmd_lcd(0x80);
		//string_lcd(buff);
		delay_ms(2000);
		if(strstr(buff,"SEND OK"))
		{
			//cmd_lcd(0x01);
			//string_lcd("DATA UPDATED");
			//delay_ms(1000);			
			return 1;
		}
		else
		{
			//cmd_lcd(0x01);
			//string_lcd("DATA NOT UPDATED");
			//delay_ms(1000);	
			return 0;
		}
		
	}
	else
	{
		//cmd_lcd(0xC0);
		//string_lcd("ERROR");
		//delay_ms(1000);		
		return 0;
	}
}
