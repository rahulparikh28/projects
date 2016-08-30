#include<p32xxxx.h>
#include<plib.h>
#define A PORTGbits.RG14
#define B PORTGbits.RG12
#define C PORTGbits.RG13
#define D PORTGbits.RG15
void delay();
void lcdconfig();
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void msdelay(unsigned int);

void delay()
{
unsigned int i;
i=1024*1024;
while(i--);
}

int main()
{
unsigned int value;
DDPCON=0x0000;
mPORTASetPinsDigitalOut(0xFF);
mPORTAClearBits(0xFF);
mPORTGSetPinsDigitalIn(BIT_14 | BIT_12 | BIT_13 | BIT_15);
mPORTGSetPinsDigitalOut(BIT_0 | BIT_1);
mPORTFSetPinsDigitalOut(BIT_0 | BIT_1);
lcdconfig();
lcdcmd(0x86);
delay();
//lcddata('m');
while(1)
{

      mPORTGSetBits(BIT_1);
      mPORTFClearBits(BIT_0);
      mPORTFClearBits(BIT_1);
      mPORTGClearBits(BIT_0);

      if(PORTGbits.RG14==1)
   {
      lcdcmd(0xC0);
      msdelay(100);
      lcddata('8');
   }
      if(PORTGbits.RG12==1)
  {
      lcdcmd(0xC1);
      msdelay(100);
      lcddata('9');
  }
   else if(PORTGbits.RG13==1)
  {
      lcdcmd(0xC2);
      msdelay(100);
      lcddata('A');
  }
   else if(PORTGbits.RG15==1)
  {
      lcdcmd(0xC3);
      msdelay(100);
      lcddata('B');
  }


      mPORTGSetBits(BIT_0);
      mPORTGClearBits(BIT_1);
      mPORTFClearBits(BIT_1);
      mPORTFClearBits(BIT_0);

      if(PORTGbits.RG14==1)
   {
      lcdcmd(0xC4);
      msdelay(100);
      lcddata('C');
   }
      if(PORTGbits.RG12==1)
  {
      lcdcmd(0xC5);
      msdelay(100);
      lcddata('D');
  }
   else if(PORTGbits.RG13==1)
  {
      lcdcmd(0xC6);
      msdelay(100);
      lcddata('E');
  }
   else if(PORTGbits.RG15==1)
  {
      lcdcmd(0xC7);
      msdelay(100);
      lcddata('F');
  }

      mPORTFSetBits(BIT_0);
      mPORTGClearBits(BIT_0);
      mPORTFClearBits(BIT_1);
      mPORTGClearBits(BIT_1);

      if(PORTGbits.RG14==1)
   {
      lcdcmd(0x80);
      msdelay(100);
      lcddata('0');
   }
      if(PORTGbits.RG12==1)
  {
      lcdcmd(0x81);
      msdelay(100);
      lcddata('1');
  }
   else if(PORTGbits.RG13==1)
  {
      lcdcmd(0x82);
      msdelay(100);
      lcddata('2');
  }
   else if(PORTGbits.RG15==1)
  {
      lcdcmd(0x83);
      msdelay(100);
      lcddata('3');
  }


      mPORTFSetBits(BIT_1);
      mPORTGClearBits(BIT_0);
      mPORTFClearBits(BIT_0);
      mPORTGClearBits(BIT_1);

    
      if(PORTGbits.RG12==1)
  {
      lcdcmd(0x85);
      msdelay(100);
      lcddata('5');
  }
   else if(PORTGbits.RG13==1)
  {
      lcdcmd(0x86);
      msdelay(100);
      lcddata('6');
  }
   else if(PORTGbits.RG15==1)
  {
      lcdcmd(0x87);
      msdelay(100);
      lcddata('7');
}
 else if(PORTGbits.RG14==1)
   {
      lcdcmd(0x84);
      msdelay(100);
      lcddata('4');
   }
}
}

void lcdconfig()
{
 mPORTESetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4 | BIT_5 | BIT_6 | BIT_7);
    PORTSetPinsDigitalOut(IOPORT_D,BIT_5 | BIT_4);
    lcdcmd(0x38); // for using 8-bit 2 row mode of LCD
    msdelay(10);
    lcdcmd(0x0E);  // turn display ON for cursor blinking
    msdelay(10);
    lcdcmd(0x01); //clear screen
    msdelay(10);
    lcdcmd(0x06); //display ON
    msdelay(10);
    lcdcmd(0x86); // bring cursor to position 6 of line 1
    msdelay(10);
    return;
}

 void lcdcmd(unsigned char value)
{
    PORTE = value;    
     msdelay(100);                                                      
     PORTClearBits(IOPORT_D, BIT_5);
    PORTSetBits(IOPORT_D, BIT_4);
    msdelay(100);
    PORTClearBits(IOPORT_D, BIT_4);
    return;
 }

void lcddata(unsigned char value)
{
    PORTE = value;                                                               // write whole port E
    PORTSetBits(IOPORT_D, BIT_5);
    PORTSetBits(IOPORT_D, BIT_4);
    msdelay(100);
    PORTClearBits(IOPORT_D,BIT_4);
    delay(1000000);
    //return;
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
