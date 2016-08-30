#include <plib.h>
#include <p32xxxx.h>
/*#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
#define SYS_FREQ         (80000000L)
*/
void msdelay();
void lcdcmnd(unsigned char);
void lcddata1();
void lcdconfig();
int main(void)
{
	unsigned int t0,t1;
	DDPCON=0x0000;
	mPORTASetPinsDigitalOut(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
	mPORTAClearBits(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
	RtccInit();        // init the RTCC
	RTCCONSET=0x0081;
 	OSCCONSET=0x04000;
	OSCCONSET=0x0400;
	OSCCONSET=0x0001;
    while(RtccGetClkStat()!=RTCC_CLK_ON); // wait for the SOSC to be actually running and RTCC to have its clock source
             
        // could wait here at most 32ms
	
    RtccSetTimeDate(0x09703023, 0x13030704);  

   mPORTASetBits(BIT_1);


lcdconfig();
}   
void lcdconfig()
{
	PORTSetPinsDigitalOut(IOPORT_D,BIT_4 | BIT_5);
	mPORTESetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4 | BIT_5 | BIT_6 | BIT_7);
	lcdcmnd(0x38); //init lcd 2 line 5x7 matrix
    msdelay(10);
    lcdcmnd(0x0E); //display on cursor blink
    msdelay(10);
    lcdcmnd(0x01); // clear display
    msdelay(10);
    lcdcmnd(0x06); // shift cursor right
    msdelay(10);
    lcdcmnd(0x84); // cursor at line 1 pos. 4
    msdelay(10);
	lcddata1();
	msdelay(100);
}

void msdelay(unsigned int itime)
{
	unsigned int i,j;
	for(i=1;i<itime;i++)
	  for(j=1;j<1275;j++);
    return;
}	

void lcdcmnd(unsigned char value)
{
	PORTE=value;
	msdelay(100);
 	mPORTDClearBits(BIT_5);   // RS=0 write
	mPORTDSetBits(BIT_4);
	msdelay(100);
	mPORTDClearBits(BIT_4);
	return;
}
void lcddata1()
{
unsigned int a,c,p,b,d;
unsigned int num[20];

a=RTCTIME;

int k=0;
while(a>0)
{
  num[k]=a%16;
  a=a/16;
   k++;
}
k--;
for (p=k;0<=p;p--)
{
  c=num[p]+48;
if(p==1||p==3||p==5)
{
	b=':';
	PORTE=b;
	msdelay(100);
  	mPORTDSetBits(BIT_5);//RS=1 write
  	mPORTDSetBits(BIT_4);
  	msdelay(10);
  	mPORTDClearBits(BIT_4);
	msdelay(100);

}
  PORTE = c;
  msdelay(100);
  mPORTDSetBits(BIT_5);//RS=1 write
  mPORTDSetBits(BIT_4);
  msdelay(100);
  mPORTDClearBits(BIT_4);
  msdelay(100);
  if(p==0)
  break;
}
	
}


