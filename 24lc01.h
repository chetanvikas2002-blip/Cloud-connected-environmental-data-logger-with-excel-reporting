#include<lpc21xx.h>
#define SA 0X50
void byte_write(char addr,short int baddr,char ch);
char byte_read(char addr,short int baddr);
void page_write(char addr,short int baddr,char *p);
void seq_read(char addr,short int baddr,char *ch);
