#include<lpc21xx.h>
#include "adc.h"
#include "lcd_defines.h"
#include "delay.h"
#include "rtc.h"
#include "cust_lcd.h"
#include "interrupt.h"
#include "keypad_defines.h"
#include "menu.h"
#include "i2c.h"
#include "24lc01.h"
#include "uart.h"
#include "mq2.h"
#include "esp01.h"
#define BUZ 30
#define S_BUZ 24
static int prev_min=-1,prev_gas=1,current=0;
int dval,adc,sw=0,triggered=0,old_min=0;
char sp=32;
float aval;
int main()
{
    int s=0,m=45,h=6,d=11,mo=3,y=2026,w=3;
    int i,len;
    char str[]="CLOUD-CONNECTED ENVIRONMENTAL DATA LOGGER WITH EXCEL REPORTING";
    prev_min=m;
    //int s=0,m=45,h=6,d=11,mo=3,y=2026,w=3;
        prev_min=m;
        PINSEL1=PINSEL1&~(3<<2*(BUZ-16));
        PINSEL2=PINSEL2&~(3<<(2*(S_BUZ-16)));
        IODIR1|=1<<S_BUZ;
        IODIR0|=1<<BUZ;
        init_lcd();
        init_uart();
        init_adc();
        init_rtc();
        cust_lcd();
        init_i2c();
        init_interrupt();
        init_inter();
        init_keypad();
        init_mq2();
	/* Welcome Screen */
cmd_lcd(0x01);
delay_ms(2);

cmd_lcd(0x80);
string_lcd("P.CHETAN VIKAS");

cmd_lcd(0xC0);
string_lcd("24NU1D7704");

delay_ms(1500);

/* Project Title Scrolling */
len = 31-1;

for(i = 0; i <= len; i++)
{
    //lcd_print_window(str, i);
    delay_ms(100);
}

delay_ms(1000);
cmd_lcd(0x01);
delay_ms(2);
        set_time_info(&s,&m,&h);
        set_date_info(&d,&mo,&y);
        set_week(&w);
        //byte_write(0x50,0x77,35);
        sp=byte_read(0x50,0x77);
		cmd_lcd(0x01);
        read_adc(1,&dval,&aval);
        cmd_lcd(0x01);
        delay_ms(2);
        string_lcd("Starting");
        cmd_lcd(0xc0);
        string_lcd("ESP01");
        init_esp01();
        cmd_lcd(0x01);
        delay_ms(2);
        while(1)
        {
                get_info(&s,&m,&h,&d,&mo,&y,&w);
                display_info(s,m,h,d,mo,y,w);
                read_adc(1,&dval,&aval);
                temp_display(aval);
				if((((m-prev_min+60)%60)==3)&&(s==0))
                {
                        prev_min=m;
                        cmd_lcd(0x01);
                        delay_ms(2);
                        update_data(1,(aval*100));
                }
                if(sw==1)
                {
                        sw=0;
						old_min=m;
                        menu(&sp,&s,&m,&h,&d,&mo,&y,&w);
                        cmd_lcd(0x01);
                        delay_ms(2);
						if(old_min!=m)
						{
							prev_min=m;
						}
                }
                if(((int)(aval*100))>sp)
                {
                        IOSET0=1<<BUZ;
                        update_data(4,(aval*100));
                }
                else
                {
                        IOCLR0=1<<BUZ;
                }
                cmd_lcd(0xC8);
                string_lcd(" SMOKE:");
                current=(((IOPIN0>>29)&1));
                if((current==1)&&(prev_gas==0))
                {
                        data_lcd('1');
                        cmd_lcd(0x01);
                        delay_ms(2);
                        string_lcd("uploading...");
                        cmd_lcd(0xc0);
                        string_lcd("SMOKE RELEASE");
                        update_data(3,0);
                }
                if((current==0)&&(prev_gas==1))
                {
                        data_lcd('0');
                        cmd_lcd(0x01);
                        delay_ms(2);
                        string_lcd("uploading...");
                        cmd_lcd(0xc0);
                        string_lcd("SMOKE ALERT");
                        update_data(3,1);
                }
                if(current==0)
                {
                        IOSET1=1<<S_BUZ;
                        data_lcd('1');
                }
                else
                {
                        IOCLR1=1<<S_BUZ;
                        data_lcd('0');
                }
                prev_gas=current;
        }
}
void sw_pressed(void)__irq
{
        sw=1;
        EXTINT=1<<0;
        VICVectAddr=0;
}
