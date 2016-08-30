#include<plib.h>
void mode();
void batteryv();
void temps();
void mode2();
void menudisplay();
void settemp();
extern void lcdcmd(unsigned char);
extern void lcddata(unsigned char);
extern void lcdini();
extern void msdelay(unsigned int);
extern char keypad();
void delay(unsigned int);
unsigned char str1[]="1.Mode Select";
unsigned char str2[]="2.Bat Voltage";
unsigned char str3[]="3.Temp Change";
unsigned char str4[]="Menu";
unsigned char str5[]="1.Auto Mode";
unsigned char str6[]="2.Manual Mode";
unsigned char str7[]="Set Temp";


int i;

int main()
{
i=0;
DDPCON=0x0000;
mPORTDSetPinsDigitalIn(BIT_7|BIT_13|BIT_6);                           //Set Portd pins DigitalIn
mPORTESetPinsDigitalIn(BIT_9);
mPORTASetPinsDigitalOut(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6);
mPORTAClearBits(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6);
mPORTASetPinsDigitalIn(BIT_7);
lcdcmd(0x01);                                        //Set Porta Pin DigitalIn
while(PORTEbits.RE9==1);                                              //Wait till key press
menudisplay();
lcdini();

	switch(i)                                                         //Switch case to select function
	{
		case 0:
        mode();
		break;
		case 1:
		batteryv();
		break;
		case 2:
		temps();
	
	}

}	
void mode()                                                           //Function for mode selection
{
int j;
  j=0;
 menudisplay();
 lcdcmd(0xC0);
while(str1[j]!='\0')
  {
    lcddata(str1[j]);
    j++;
  }
delay(10000000);
while(PORTDbits.RD13==1&&PORTDbits.RD7==1);                           //Wait till any key press
if(PORTDbits.RD7==0)
{
i++;
lcdcmd(0x01);
}
else if(PORTDbits.RD13==0)
{
mode2();
}
//return;
}
void batteryv()                                                      //Function to display battery voltage
{
int j;
  j=0;
 menudisplay();
 lcdcmd(0xC0);
 while(str2[j]!='\0')
  {
    lcddata(str2[j]);
    j++;
  }
delay(10000000);
while(PORTDbits.RD13==1&&PORTDbits.RD7==1&&PORTAbits.RA7==1);        //Wait till any key press
if(PORTDbits.RD7==0)
{
i++;
lcdcmd(0x01);
}
else if(PORTDbits.RD13==0)
{
mPORTASetBits(BIT_2 | BIT_3);
}
else if(PORTAbits.RA7==0)
{
i--;
lcdcmd(0x01);
}
//return;
}


void temps()                                                        //Function to display temp change                                                       
{
int j;
  j=0;
 menudisplay();
 lcdcmd(0xC0);
 while(str3[j]!='\0')
  {
    lcddata(str3[j]);
    j++;
  }
delay(10000000);
while(PORTDbits.RD13==1&&PORTDbits.RD7==1&&PORTAbits.RA7==1);      //Wait till any key press
if(PORTDbits.RD7==0)
{
i++;
lcdcmd(0x01);
}
else if(PORTDbits.RD13==0)
{
settemp();
i==2;
delay(100000000);
}
else if(PORTAbits.RA7==0)
{
i--;
lcdcmd(0x01);
}
//return;
}
void delay(unsigned int itime)                                     //Delay function
{
 unsigned int y;
 for(y=0;y<itime/140;y++);
}
void menudisplay()
{
int j;
j=0;
lcdini();
while(str4[j]!='\0')
{
 lcddata(str4[j]);
	j++;
}
}
void mode2()
{
int j;
j=0;

lcdcmd(0x01);
lcdcmd(0x80);
while(str5[j]!='\0')
{
  lcddata(str5[j]);
  j++;
}
j=0;
lcdcmd(0xC0);
while(str6[j]!='\0')
{
 lcddata(str6[j]);
 j++;
}
while(PORTDbits.RD7==1);

//return;

}


void settemp()
{
int j;
char x;
j=0;
lcdcmd(0x01);
lcdcmd(0x80);
while(str7[j]!='\0')
{
lcddata(str7[j]);
j++;
}
lcdcmd(0xc0);
x = keypad();
x+= 0x30;
lcddata(x);
delay(1000000000);
x = keypad();
x+= 0x30;
lcddata(x);
while(PORTEbits.RE9==1);
//return;
}