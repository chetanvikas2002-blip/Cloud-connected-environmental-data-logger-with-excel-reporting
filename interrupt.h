#include<lpc21xx.h>
#define EINT0_CH 14
#define EINT0_PIN 16
#define EINT3_CH 17
#define EINT3_PIN 30
void init_interrupt(void);
void sw_pressed(void) __irq;
void init_mq2_int(void);
void smoke_alert(void) __irq;
