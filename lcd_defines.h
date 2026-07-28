#include<lpc21xx.h>
#define RS 18
#define RW 19
#define EN 20
#define LED 8
void init_lcd(void);
void cmd_lcd(char num);
void data_lcd(char num);
void char_lcd(char data);
void int_lcd(int num);
void string_lcd(char *);
void cus_char(char *p);
