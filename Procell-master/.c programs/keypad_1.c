#include<p32xxxx.h>
#include<plib.h>
void msdelay();
void lcdcmnd(unsigned char);
void lcddata(unsigned char);
void lcdconfig();

int main()
{
	unsigned int col1,col2,col3,col4;
	mPORTFSetPinsDigitalOut(BIT_0|BIT_1); 
	mPORTGSetPinsDigitalOut(BIT_1|BIT_0);
	mPORTGSetPinsDigitalIn(BIT_14|BIT_12|BIT_13|BIT_15);
	DDPCON=0x0000;
    mPORTASetPinsDigitalOut(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
 while(1)
 {
	mPORTFSetBits(BIT_0);
	mPORTFClearBits(BIT_1);
	mPORTGClearBits(BIT_0|BIT_1);

	col1=mPORTGReadBits(BIT_14);
	col2=mPORTGReadBits(BIT_12);
	col3=mPORTGReadBits(BIT_13);
	col4=mPORTGReadBits(BIT_15);


	lcdconfig();

	if(col1==1)
    	{
		    lcdcmnd(0x81);
			msdelay(10);
			lcddata('1');
	    }
	else if(col2==1)
		{
			lcdcmnd(0x82);
			msdelay(10);
			lcddata('2');
		}	
	else if(col3==1)
		{
			lcdcmnd(0x83);
			msdelay(10);
			lcddata('3');	    
		}
	else if(col4==1)
	    {
	       	lcdcmnd(0x84);
			msdelay(10);
			lcddata('4');
	    }
 }
}

void lcdconfig()

{
	mPORTESetPinsDigitalOut(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
	mPORTDSetPinsDigitalOut(BIT_4|BIT_5);
	msdelay(10);
	lcdcmnd(0x38);
	msdelay(10);
	lcdcmnd(0x0E);
	msdelay(10);
	lcdcmnd(0x01); //clear screen
    msdelay(10);
    lcdcmnd(0x06); //display ON
    msdelay(10);
    lcdcmnd(0x86); // bring cursor to position 6 of line 1
    msdelay(10);
    return;
}
void lcdcmnd(unsigned char value)
{
	PORTE=value;
	msdelay(10);
	mPORTDClearBits(BIT_5);
	mPORTDSetBits(BIT_4);
	msdelay(10);
	mPORTDClearBits(BIT_4);
	return;
}
void lcddata(unsigned char value)
{
	PORTE=value;
	msdelay(10);
	mPORTDSetBits(BIT_5);
	mPORTDSetBits(BIT_4);
	msdelay(10);
	mPORTDClearBits(BIT_4);
	msdelay(10);
	return;
}
void msdelay(unsigned int itime)
{
 unsigned int i,j;
 for(i=1;i<itime;i++);
	for(j=1;j<1000;j++);
}
