#include<p32xxxx.h>
#include<plib.h>
int main()
{
	DDPCON=0x0000;
	mPORTASetPinsDigitalOut(BIT_7|BIT_6|BIT_5|BIT_4|BIT_3|BIT_2|BIT_1|BIT_0);
	mPORTASetBits(BIT_7|BIT_6|BIT_5|BIT_4|BIT_3|BIT_2|BIT_1|BIT_0);
}
	