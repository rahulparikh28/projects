#include<plib.h>
#include<p32xxxx.h>
void delay(unsigned int);
void lcdconfig();
void lcdcmnd(unsigned char);
void lcddata(unsigned char);
int main()
{
	mJTAGPortEnable(0);
	mPORTASetPinsDigitalOut(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
	mPORTAClearBits(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
	INTCONSET=0x1000;
	INTEnableSystemMultiVectoredInt();
	IEC0 =0;
	IFS0 = 0;
	INTCONCLR = 0x00000018;
	IEC0SET = 0x00088000;
	IPC3 = 0x1F000000;
	IPC4 = 0X17000000;
	lcdconfig();

while(1)
{
	if(IFS0 & 0x8000==1)
	{
		lcddata('3');
		PORTA=0X0F;
	}
	if(IFS0 & 0x80000==1)
	{
		lcddata('4');
		PORTA=0XFF;
	}
}
}
void delay(unsigned int itime)
{
	unsigned int i,j;
	for(i=1;i<itime;i++)
	  for(j=1;j<1275;j++);
    return;
}	

void lcdconfig()
{
	PORTSetPinsDigitalOut(IOPORT_D,BIT_4 | BIT_5);
	mPORTESetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4 | BIT_5 | BIT_6 | BIT_7);
	lcdcmnd(0x38); //init lcd 2 line 5x7 matrix
    delay(10);
    lcdcmnd(0x0E); //display on cursor blink
    delay(10);
    lcdcmnd(0x01); // clear display
    delay(10);
    lcdcmnd(0x06); // shift cursor right
    delay(10);
    lcdcmnd(0x84); // cursor at line 1 pos. 4
    delay(10);
}
void lcddata(unsigned char value)
{
	PORTE=value;
	delay(250);
	//mPORTBSetBits(BIT_15); 
	mPORTDSetBits(BIT_5);//RS=1 write
	mPORTDSetBits(BIT_4);
	delay(100);
	mPORTDClearBits(BIT_4);
	return;
}
void lcdcmnd(unsigned char value)
{
	PORTE=value;
	delay(100);
 	mPORTDClearBits(BIT_5);   // RS=0 write
	mPORTDSetBits(BIT_4);
	delay(100);
	mPORTDClearBits(BIT_4);
	return;
}	