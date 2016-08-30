#include<plib.h>
#include<p32xxxx.h>
void delay(unsigned int);
void lcdconfig();
void lcdcmnd(unsigned char);
void lcddata(unsigned char);
int main()
{
mJTAGPortEnable(0);
//mPORTDSetPinsDigitalOut(BIT_9);
//mPORTDClearBits(BIT_9);
mPORTASetPinsDigitalIn(BIT_14|BIT_15);

mPORTASetPinsDigitalOut(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
mPORTAClearBits(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);

INTCONSET=0x01000;
INTEnableSystemMultiVectoredInt();
IEC0 =0x0000;
//IEC0CLR = 0x00008000; // disable INT3
//IEC0CLR = 0x00080000; // disable INT4
INTCONSET = 0x00000018; // set the bit for rising edge trigger
//INTCONSET = 0x00000010; // set the bit for rising edge trigger
IFS0 = 0; // clear the interrupt flag
//IFS0CLR = 0x00080000; // clear the interrupt flag
//INTEnableInterrupts();
IEC0SET = 0x00088000; // enable INT3 & INT4
//IEC0SET = 0x00080000; // enable INT4
IPC3 = 0x1F000000;
//IPC3SET = 0x3000000;
IPC4 = 0X17000000;
//IPC4SET = 0x3000000;
lcdconfig();

//

}
void delay(unsigned int itime)
{
	unsigned int i,j;
	for(i=1;i<itime;i++)
	  for(j=1;j<1275;j++);
    return;
}	


             
void __ISR(_EXTERNAL_3_VECTOR,ipl7) generator_OFF(void)
{
IFS0=0;
//while(IFS0 & 0x8000 ==1)
lcddata('3');
//IEC0CLR=0X8000;
//mPORTDSetBits(BIT_9);
PORTA=0xFF;
//delay(1000000);
PORTA=0x00;

}
void __ISR(_EXTERNAL_4_VECTOR,ipl5) generator_ON(void)
{
IFS0=0;
lcddata('4');
//IEC0CLR=0X80000;
//mPORTDClearBits(BIT_9);
PORTA=0x0F;
//delay(1000000);
//PORTA=0x00;
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



