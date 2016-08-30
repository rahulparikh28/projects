#include<p32xxxx.h>
#include<plib.h>
void msdelay();
void lcdcmnd(unsigned char);
void lcddata(unsigned char);

int main()
{
	mPORTASetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4 | BIT_5 | BIT_6 | BIT_7);
	PORTSetPinsDigitalOut(IOPORT_D,BIT_4 | BIT_5);
	mPORTESetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4 | BIT_5 | BIT_6 | BIT_7);
	PORTA=0xFF;
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

	
//	lcddata();
	 msdelay(250);
    lcdcmnd(0x01);
	msdelay(10);
	lcddata('K');
	msdelay(10);
	lcddata('E');
	msdelay(10);
	lcddata('Y');
	msdelay(10);
	lcddata('U');	
	msdelay(10);
	lcddata('R');
	msdelay(10);
	//lcddata('');
	
	
    	
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
//	mPORTBClearBits(BIT_15); // 
	mPORTDClearBits(BIT_5);   // RS=0 write
	mPORTDSetBits(BIT_4);
	msdelay(100);
	mPORTDClearBits(BIT_4);
	return;
}
void lcddata(unsigned char value)
{
	PORTE=value;
	msdelay(250);
	//mPORTBSetBits(BIT_15); 
	mPORTDSetBits(BIT_5);//RS=1 write
	mPORTDSetBits(BIT_4);
	msdelay(100);
	mPORTDClearBits(BIT_4);
	return;
}
/*void lcddata()
{
unsigned int a,c,p,b,d;
unsigned int num[10];
a=0x11371000;
int k=0;
while(a>0)
{
  num[k]=a%16;
  a=a/16;
   k++;
}
k--;
for (p=k;p>=0;p--)
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
{	while(1);
}
}
return;	
}*/





















