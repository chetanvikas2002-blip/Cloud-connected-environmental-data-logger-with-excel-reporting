#include<LPC21xx.h>
#include"keypad_defines.h"
char LUT[][4]={0,1,2,3,
	           4,5,6,7,
						 8,9,10,11,
	           12,13,14,15};

void init_keypad(void)
{
		IODIR1|=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
	    //P1.16-P1.19 are for output functionality
		IOCLR1=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
		//Initializing rows to 0

}
char col_stat(void)
{
	if((((IOPIN1>>20)&0x0f)==0x0f))
		return 1;
	else 
		return 0;
}
char key_val(void)
{
		char row_val=0,col_val=0;
		IOCLR1=(1<<R0);
		IOSET1=((1<<R1)|(1<<R2)|(1<<R3));
		if((((IOPIN1>>20)&0x0f)!=0x0f))
		{
			row_val=0;
			goto colcheck;
		}
		IOCLR1=(1<<R1);
		IOSET1=((1<<R0)|(1<<R2)|(1<<R3));
		if((((IOPIN1>>20)&0x0f)!=0x0f))
		{
			row_val=1;
			goto colcheck;
		}
		IOCLR1=(1<<R2);
		IOSET1=((1<<R0)|(1<<R1)|(1<<R3));
		if((((IOPIN1>>20)&0x0f)!=0x0f))
		{
			row_val=2;
			goto colcheck;
		}
		IOCLR1=(1<<R3);
		IOSET1=((1<<R0)|(1<<R1)|(1<<R2));
		if((((IOPIN1>>20)&0x0f)!=0x0f))
			row_val=3;
		
		colcheck:		
		if(((IOPIN1>>C0)&1)==0)
			col_val=0;
		else if(((IOPIN1>>C1)&1)==0)
			col_val=1;
		else if(((IOPIN1>>C2)&1)==0)
			col_val=2;
		else
			col_val=3;

		IOCLR1=((1<<R0)|(1<<R1)|(1<<R2)|(1<<R3));
	//Initializing rows to 0

		return(LUT[row_val][col_val]);
	
}
