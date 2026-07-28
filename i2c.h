#include<lpc21xx.h>
#include "clock.h"
#define SCL 2
#define SDA 3
#define I2EN 6
#define STA 5
#define STO 4
#define SI 3
#define AA 2
#define I2ENC 
#define STAC 5
#define SIC 3
#define AAC 2
#define S_CLK 100000
#define D_VAL ((PCLK/S_CLK)/2)
void init_i2c(void);
void start(void);
void stop(void);
void write(char ch);
void rep_start(void);
char mack(void);
char nack(void);
