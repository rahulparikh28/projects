


#include<plib.h>
#include<p32xxxx.h>



#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1

#define SYS_FREQ         (80000000L)
void msdelay(unsigned int);
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdini();
unsigned char value ;



void lcdini()
{
 
    mPORTESetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4 | BIT_5 | BIT_6 | BIT_7);
    PORTSetPinsDigitalOut(IOPORT_D,BIT_5 | BIT_4);
    lcdcmd(0x38);
    msdelay(10);
    lcdcmd(0x0E);
    msdelay(10);
    lcdcmd(0x01);
    msdelay(10);
    lcdcmd(0x06);
    msdelay(10);
    lcdcmd(0x80);
    return;
}


 void lcdcmd(unsigned char value)
{
    PORTE = value;                                                                // write whole port E
    //PORTWrite(IOPORT_E) = value;
	//PORTWrite(IOPORT_E,BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7) = value;
    PORTClearBits(IOPORT_D, BIT_5);
    PORTSetBits(IOPORT_D, BIT_4);
    msdelay(100);
    PORTClearBits(IOPORT_D, BIT_4);
    return;
 }


 void lcddata(unsigned char value)
{
    PORTE = value;                                                               // write whole port E
    //mPORTEWrite = value;
    //PORTWrite(IOPORT_E,BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7) = value1;
    PORTSetBits(IOPORT_D, BIT_5);
    PORTSetBits(IOPORT_D, BIT_4);
    msdelay(100);
    PORTClearBits(IOPORT_D,BIT_4);
    return;
 }



void msdelay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		{
			for(j=0;j<1250;j++)
				{

				}
		}
}

