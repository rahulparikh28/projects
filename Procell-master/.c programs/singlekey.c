#include<p32xxxx.h>
#include<plib.h>
int main()
{
  while(1)
{
	unsigned int config;
	DDPCON=0x0000;
	mPORTASetPinsDigitalOut(BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
	mPORTGSetPinsDigitalOut(BIT_14);
    mPORTAClearBits(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
    mPORTGClearBits(BIT_14);
    mPORTFSetPinsDigitalIn(BIT_0);
	config=mPORTFReadBits(BIT_0);
	if(config==0)
	{
	  PORTSetBits(IOPORT_A, BIT_6);
	}
	else
	
	{ 
		PORTSetBits(IOPORT_A, BIT_7);
	}
}
	
}