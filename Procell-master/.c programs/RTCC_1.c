#include<p32xxxx.h>
#include<plib.h>


void delay();
void msdelay();
void lcdcmnd(unsigned char);
void lcddata();
void lcdconfig();

int main(void)
{
	unsigned int t0,t1,scan;
	unsigned long time,date;
   

    DDPCON=0x0000;
	mPORTASetPinsDigitalOut(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
    mPORTAClearBits(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);

	OSCCONSET=0x00400002; // secondary oscillator 32.768khz
	WDTCONCLR=0x8000;  // watchdog timer=0
	RTCCONCLR=0x8000;
	RTCCONSET=0x0008; // RTCWREN=1 
	while(RTCCON&0x40);	  // wait for RTCC clk=0

RtccSetTimeDate(0x14030000, 0x00022805);
								// 12hr 24min 30sec 00halfsec
	
	RTCCONSET=0x8081;
	RTCCONCLR=0x0008;

	delay(1000);
	while(!(RTCCON&0x40==0x0040));	//wait for clock to be turned on ,
	do
{
	t0=RtccGetTime();
	t1=RtccGetTime();
}while(t0!=t1);
	lcdconfig();
  
mPORTASetBits(BIT_0);
	delay(50000);
	lcdconfig();
/*	while(!((RTCCON&0x02)==0x02));	//wait for sync bit to high
	mPORTASetBits(BIT_6);
	if((RTCCON&0x02)==0x00);    // wait sync to be low
		{
		t0=RTCTIME;
		delay(5000);
		  if((RTCCON&0x02)==0x00); 
		   {
			t1=RTCTIME;
		   }
		}
*/
}
void delay(unsigned int itime)
{
int i,j;
for(i=1;i<itime;i++)
  for(j=1;j<1000;j++);
}

void lcdconfig()
{
	PORTSetPinsDigitalOut(IOPORT_D,BIT_4 | BIT_5);
	mPORTESetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4 | BIT_5 | BIT_6 | BIT_7);
	lcdcmnd(0x38); //init lcd 2 line 5x7 matrix
    msdelay(250);
    lcdcmnd(0x0E); //display on cursor blink
    msdelay(250);
    lcdcmnd(0x01); // clear display
    msdelay(250);
    lcdcmnd(0x06); // shift cursor right
    msdelay(250);
    lcdcmnd(0x84); // cursor at line 1 pos. 4
    msdelay(1000);
	lcddata();
	msdelay(250);
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
	msdelay(250);
 	mPORTDClearBits(BIT_5);   // RS=0 write
	mPORTDSetBits(BIT_4);
	msdelay(100);
	mPORTDClearBits(BIT_4);
	return;
}

/*void lcddata(unsigned char value)
{
	PORTE=value;
	msdelay(250);
	//mPORTBSetBits(BIT_15); 
	mPORTDSetBits(BIT_5);//RS=1 write
	mPORTDSetBits(BIT_4);
	msdelay(100);
	mPORTDClearBits(BIT_4);
	return;
}*/

void lcddata()
{
unsigned int a,c,p,b,d;
unsigned int num[9];
a=RtccGetTime();
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
	msdelay(250);
  	mPORTDSetBits(BIT_5);//RS=1 write
  	mPORTDSetBits(BIT_4);
  	msdelay(100);
  	mPORTDClearBits(BIT_4);
	msdelay(100);

}
  PORTE = c;
  msdelay(250);
  mPORTDSetBits(BIT_5);//RS=1 write
  mPORTDSetBits(BIT_4);
  msdelay(100);
  mPORTDClearBits(BIT_4);
  msdelay(250);
if(p==0)
break;
}
mPORTASetBits(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4);	
}