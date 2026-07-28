#include "clock.h"

void init_uart(void); 
void tx_uart(char ch);  
char rx_uart(void); 
void string_uart(char *);
void int_uart(unsigned int);
void float_uart(float);
void disp_time(int h,int m,int s);
void init_inter(void);
