#include <lpc21xx.h>
#include "keypad_defines.h"
#include "lcd_defines.h"
#include "menu.h"
#include "delay.h"
#include "cust_lcd.h"
#include "rtc.h"
#include "i2c.h"
#include "24lc01.h"
#include "esp01.h"
#include "uart.h"

void menu(char *temp, int *sec, int *min, int *hour,
          int *day, int *mon, int *year, int *dow)
{
        int ch, tmenu,dtemp,itemp;

        string_uart("****editing mode activated****\r\n");
        while (1)
        {
                cmd_lcd(0x01);

                cmd_lcd(0x80);
                string_lcd("1.ERI  2.TEMP");

                cmd_lcd(0xc0);
                string_lcd("3.DTEMP  4.EXIT");

                while (col_stat());

                ch = key_val();

                if (ch == 1)
                {
                        string_uart("****time editing mode activated****\r\n");

                        while (!col_stat());

                        while (1)
                        {
                                cmd_lcd(0x01);

                                cmd_lcd(0x80);
                                string_lcd("1.H 2.M 3.S 4.D");

                                cmd_lcd(0xc0);
                                string_lcd("5.M6.Y 7.DAY 8.E");

                                while (col_stat());

                                tmenu = key_val();

                                if (tmenu == 1)
                                {
                                        while (!col_stat());

                                        cmd_lcd(0x01);
                                        cmd_lcd(0x80);
                                        string_lcd("enter hour");

                                        *hour = ip_keypad();

                                        if (*hour > 23)
                                        {
                                                cmd_lcd(0x01);
                                                cmd_lcd(0x80);
                                                string_lcd("out of range");
                                                cmd_lcd(0xc0);
                                                string_lcd("range is (0-23)");

                                                delay_ms(300);
                                        }
                                        else if((*hour)!=-1)
                                        {
                                                set_time_info(sec,min,hour);
                                        }
                                }

                                else if (tmenu == 2)
                                {
                                        while (!col_stat());

                                        cmd_lcd(0x01);
                                        cmd_lcd(0x80);
                                        string_lcd("enter min");

                                        *min = ip_keypad();

                                        if (*min > 59)
                                        {
                                                cmd_lcd(0x01);
                                                cmd_lcd(0x80);
                                                string_lcd("out of range");
                                                cmd_lcd(0xc0);
                                                string_lcd("range is (0-59)");
                                                delay_ms(300);
                                        }
                                        else if((*min)!=-1)
                                        {
                                                 set_time_info(sec,min,hour);
                                        }
                                }

                                else if (tmenu == 3)
                                {
                                        while (!col_stat());

                                        cmd_lcd(0x01);
                                        cmd_lcd(0x80);
                                        string_lcd("enter seconds");

                                        *sec = ip_keypad();

                                        if (*sec > 59)
                                        {
                                                cmd_lcd(0x01);
                                                cmd_lcd(0x80);
                                                string_lcd("out of range");
                                                cmd_lcd(0xc0);
                                                string_lcd("range is (0-59)");
                                                delay_ms(300);
                                        }
                                        else if((*sec)!=-1)
                                        {
                                                set_time_info(sec,min,hour);
                                        }
                                }

                                else if (tmenu == 4)
                                {
                                        while (!col_stat());

                                        cmd_lcd(0x01);
                                        cmd_lcd(0x80);
                                        string_lcd("enter day");

                                        *day = ip_keypad();

                                        if (*day > 31)
                                        {
                                                cmd_lcd(0x01);
                                                cmd_lcd(0x80);
                                                string_lcd("out of range");
                                                cmd_lcd(0xc0);
                                                string_lcd("range is (1-31)");
                                                delay_ms(300);
                                        }
                                        else if((*day)!=-1)
                                        {
                                                set_date_info(day, mon, year);
                                        }
                                }

                                else if (tmenu == 5)
                                {
                                        while (!col_stat());

                                        cmd_lcd(0x01);
                                        cmd_lcd(0x80);
                                        string_lcd("enter month");

                                        *mon = ip_keypad();

                                        if (*mon > 12)
                                        {
                                                cmd_lcd(0x01);
                                                cmd_lcd(0x80);
                                                string_lcd("out of range");
                                                cmd_lcd(0xc0);
                                                string_lcd("range is (1-12)");
                                                delay_ms(300);
                                        }
                                        else if((*mon)!=-1)
                                        {
                                                set_date_info(day, mon, year);
                                        }
                                }

                                else if (tmenu == 6)
                                {
                                        while (!col_stat());

                                        cmd_lcd(0x01);
                                        cmd_lcd(0x80);
                                        string_lcd("enter year");

                                        *year = ip_keypad();

                                        set_date_info(day, mon, year);
                                }

                                else if (tmenu == 7)
                                {
                                        while (!col_stat());

                                        cmd_lcd(0x01);
                                        cmd_lcd(0x80);
                                        string_lcd("enter week(0-6)");

                                        *dow = ip_keypad();

                                        if (*dow > 6)
                                        {
                                                cmd_lcd(0x01);
                                                cmd_lcd(0x80);
                                                string_lcd("out of range");
                                                cmd_lcd(0xc0);
                                                string_lcd("range is (0-6)");
                                                delay_ms(300);
                                        }
                                        else if((*dow)!=-1)
                                        {
                                                set_week(dow);
                                        }
                                }

                                if (tmenu == 8)
                                {
                                        string_uart("****time editing mode ended****\r\n");
                                        break;
                                }
                        }
                }

                else if (ch == 2)
                {
                        while (!col_stat());

                        cmd_lcd(0x01);
                        cmd_lcd(0x80);
                        string_lcd("enter temp");

                        itemp = ip_keypad();
                        if(itemp==-1)
                                continue;
                        else if(itemp>150)
                        {
                                cmd_lcd(0x01);
                                cmd_lcd(0x80);
                                string_lcd("out of range");
                                cmd_lcd(0xc0);
                                string_lcd("range is (0-150)");
                                delay_ms(300);
                        }
                        else
										{
                                *temp=itemp;
										cmd_lcd(0x01);
										string_lcd("uploading...");
										cmd_lcd(0xc0);
										string_lcd("set point");
										byte_write(0x50,0x77,*temp);
										update_data(2,(*temp));
										cmd_lcd(0x01);
										}
                }

                else if (ch == 3)
                {
                        while (!col_stat());
                        cmd_lcd(0x01);
                        while(1)
                        {
                                while(!col_stat());
                                cmd_lcd(0x80);
                                string_lcd("Threshold:");
                                int_lcd((*temp));
                                data_lcd(0);
                                data_lcd('C');
                                cmd_lcd(0xc0);
                                string_lcd("14.EXIT");
                                while(col_stat());
                                dtemp=key_val();
                                while(!col_stat());
                                if(dtemp==14)
                                        break;
                        }
                }
                else if (ch == 4)
                {
                        while (!col_stat());
                        string_uart("****editing mode ended****\r\n");
                        break;
                }
        }
}

int ip_keypad(void)
{
        int val = 0;
        int stop;
        int typed=0;

        cmd_lcd(0xc0);

        while (1)
        {
                while (col_stat());

                stop = key_val();

                while (!col_stat());

                if (stop == 14)
                        break;
                if(stop==15)
                {
                        val=val/10;
                        cmd_lcd(0xc0);
                        string_lcd("                ");
                        cmd_lcd(0xc0);
                        int_lcd(val);
                        if(typed>0)
                                typed--;
                        continue;
                }

                val = val * 10 + stop;

                cmd_lcd(0xc0);
                string_lcd("                ");

                cmd_lcd(0xc0);
                int_lcd(val);
                typed++;
        }

        if(typed==0)
                return -1;
        else
                return val;
}
