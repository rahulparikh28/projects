#include<p32xxxx.h>
#include<plib.h>
extern void msdelay(unsigned int);
extern void delay();
char keypad(void);

char keypad(void)
{


DDPCON=0x0000; //disabling jtag pins
mPORTGSetPinsDigitalIn(BIT_14 | BIT_12 | BIT_13 | BIT_15);
mPORTGSetPinsDigitalOut(BIT_0 | BIT_1);  
mPORTFSetPinsDigitalOut(BIT_0 | BIT_1); 
mPORTASetPinsDigitalOut(0x00FF); //for displaying the leds
mPORTAClearBits(0x00FF);

while(1)
{

mPORTFClearBits(BIT_1);
mPORTGClearBits(BIT_0);
mPORTGClearBits(BIT_1);
mPORTFSetBits(BIT_0);
msdelay(100);
if(PORTGbits.RG12==1)
{
// lcdcmd(j);
 //msdelay(100);
 //lcddata('0'
return 0;
break;   
}
else if(PORTGbits.RG13==1)
{
return 1; 
break; 
}
else if(PORTGbits.RG15==1)
{
return 2;
 break;  
}

mPORTFClearBits(BIT_0);
mPORTGClearBits(BIT_1);
mPORTGClearBits(BIT_0);
mPORTFSetBits(BIT_1);
msdelay(100);
if(PORTGbits.RG12==1)
{
 return 3; 
 break;
}
else if(PORTGbits.RG13==1)
{
 return 4; 
  break;  
}
else if(PORTGbits.RG15==1)
{
 return 5;  
break; 
}

mPORTFClearBits(BIT_1);
mPORTFClearBits(BIT_0);
mPORTGClearBits(BIT_0);
mPORTGSetBits(BIT_1);
msdelay(100);
if(PORTGbits.RG12==1)
{
 return 6; 
 break;
}
else if(PORTGbits.RG13==1)
{
 return 7;   
break;  
}
else if(PORTGbits.RG15==1)
{
 return 8; 
 break; 
}


mPORTFClearBits(BIT_1);
mPORTFClearBits(BIT_0);
mPORTGClearBits(BIT_1);
mPORTGSetBits(BIT_0);
msdelay(100);
if(PORTGbits.RG12==1)
{
 return 9;  
break;
}

}

}





