#include <plib.h>

void mode();
void batteryv();
void temps();
void mode2();
void menudisplay();
void settemp();

void setbatvoltage();

extern void lcdcmd(unsigned char);
extern void lcddata(unsigned char);
extern void lcdini();
extern void msdelay(unsigned int);
extern char keypad();

void delay(unsigned int);
void automode();
void manualmode();

unsigned char str1[]="1.Mode Select";
unsigned char str2[]="2.Bat Voltage";
unsigned char str3[]="3.Temp Change";
unsigned char str4[]="Menu";
unsigned char str5[]="1.Auto Mode";
unsigned char str6[]="2.Manual Mode";
unsigned char str7[]="Set Temp :";




int i;

int main()
{
i=0;
lcdini();

DDPCON=0x0000;
mPORTDSetPinsDigitalIn(BIT_7|BIT_13|BIT_6);                           //Set Portd pins DigitalIn
mPORTASetPinsDigitalOut(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6);
mPORTAClearBits(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6);
mPORTASetPinsDigitalIn(BIT_7);
char x;

while(1)
{
    switch(i)                                                                              //Switch case to select function
	{
		case 0:
        mode();
		break;
		case 1:
        batteryv();
		break;
		case 2:
		temps();
        break;
	}
    
    if(i==3)
    {
     lcdcmd(0x01);
     break;
    }
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
	while(PORTDbits.RD13==1&&PORTDbits.RD7==1&&PORTDbits.RD6==1);        //Wait till any key press
	if(PORTDbits.RD7==0)
	{
		i++;
		lcdcmd(0x01);
	}
	else if(PORTDbits.RD13==0)
	{
		PORTA=0xff;
		delay(1000000);
		PORTA=0x00;	
		while(PORTDbits.RD6==1);
		if(PORTDbits.RD6==0)
		{
			lcdcmd(0x01);
		}
	}
	else if(PORTDbits.RD6==0)
	{
		i--;
		lcdcmd(0x01);
	}

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
	while(PORTDbits.RD13==1&&PORTDbits.RD7==1&&PORTDbits.RD6==1);      //Wait till any key press
	if(PORTDbits.RD7==0)
	{
		i++;
		lcdcmd(0x01);
	}
	else if(PORTDbits.RD13==0)
	{
		settemp();
		delay(100000000);
	}
	else if(PORTDbits.RD6==0)
	{
		i--;
		lcdcmd(0x01);
	}

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
	automode();
}

void automode()
{
	menudisplay();
	int j=0;
	lcdcmd(0xC0);
	while(str5[j]!='\0')
	{
  		lcddata(str5[j]);
  		j++;
	}
	while(PORTDbits.RD13==1&&PORTDbits.RD7==1);  
	if(PORTDbits.RD13==0)
	{
  		PORTA=0xff;
		delay(1000000);
	}
	else if(PORTDbits.RD7==0)
	{
 		manualmode();
	}
/*	while(PORTDbits.RD6==1);
	if(PORTDbits.RD6==0)
	{
 		i++;
 		lcdcmd(0x01);
	}*/
}

void manualmode()
{
	menudisplay();
	int j=0;
	lcdcmd(0xC0);
	while(str6[j]!='\0')
	{
 		lcddata(str6[j]);
 		j++;
	}
	while(PORTDbits.RD6==1&&PORTDbits.RD13==1); 
	if(PORTDbits.RD13==0)
	{
 		PORTA=0xff;
		delay(1000000);
		PORTA=0x00;

	} 
	else if(PORTDbits.RD6==0)
	{
 		
		lcdcmd(0x01);
	}
	delay(1000000000);

}


void settemp()
{

	int j,b,x,v;
	j=0;
	lcdcmd(0x01);
	lcdcmd(0x80);
	while(str7[j]!='\0')
	{
		lcddata(str7[j]);
		j++;
	}

	x = keypad();
	lcdcmd(0xC0);
	lcddata(x+48);
	delay(1000000000);
	v = keypad();
	lcdcmd(0xC1);
	lcddata(v+48);
	PORTA=0xff;
}

