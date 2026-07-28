#include<lpc21xx.h>
#include "i2c.h"
void init_i2c()
{
	PINSEL0=PINSEL0&~(15<<4);
	PINSEL0=PINSEL0|(1<<(SCL)*2)|(1<<(SDA*2));
	//I2CONCLR|=0XFF;;
	I2SCLH=D_VAL;
	I2SCLL=D_VAL;
	I2CONSET=1<<I2EN;
}
void start()
{
	I2CONSET=1<<STA;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<STAC;
}
void stop()
{
	I2CONSET=1<<STO;
	I2CONCLR=1<<SIC;
}
void write(char ch)
{
	I2DAT=ch;
	I2CONCLR=1<<SIC;
	while(((I2CONSET>>SI)&1)==0);
}
void rep_start()
{
	I2CONSET=1<<STA;
	I2CONCLR=1<<SIC;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<STAC;
}
char mack()
{
	I2CONSET=1<<AA;
	I2CONCLR=1<<SIC;
	while(((I2CONSET>>SI)&1)==0);
	I2CONCLR=1<<AAC;
	return I2DAT;
}
char nack()
{
	I2CONCLR=1<<SIC;
	while(((I2CONSET>>SI)&1)==0);
	return I2DAT;
}
