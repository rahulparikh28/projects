#include <plib.h>
#include <p32xxxx.h>

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
#define SYS_FREQ         (80000000L)

void delay(unsigned int itime);
void lcdconfig();
void lcdcmnd(unsigned char);
void lcddata(unsigned char);
void spiinit();


int main()
{

	unsigned int data;
	unsigned char value;
	int a;
	DDPCON=0x0000;
	mPORTASetPinsDigitalOut(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);
	mPORTAClearBits(BIT_0|BIT_1|BIT_2|BIT_3|BIT_4|BIT_5|BIT_6|BIT_7);	
	mPORTDSetPinsDigitalOut(BIT_12);        	//chip select for eeprom
	mPORTDSetBits(BIT_12);  
	mPORTGSetPinsDigitalOut(BIT_8 | BIT_6);     //master out slave in  & SCK
	mPORTGClearBits(BIT_6 | BIT_8);           /* SCK(RG6) and SDO(RG8) low */
	mPORTGSetPinsDigitalIn(BIT_7);    	        //master in slav out
	mPORTGSetBits(BIT_7);
	mPORTDSetPinsDigitalOut(BIT_8);             //write protect
	mPORTDSetBits(BIT_8);        

//config SPI2....!!!!
	SPI2CONbits.SIDL 	= 0; 	// Continue module operation in Idle mode
  	SPI2CONbits.DISSDO	= 0;	// SDOx pin is controlled by the module

	SPI2CON=0; 
	SPI2CON=0x00008360;				//enable the spi peripheral-8160
	SPI2BRG=15;            			// use Fpb/10 clock frequency will give 10MHz....40/(2*(1+1))=10Mhz
	IEC1CLR=0xE0;          			// disable all interrupts
	IFS1CLR=0xE0;        			// clear any existing event
    IPC7CLR=0x1f000000;     		// clear the priority


/*mPORTDClearBits(BIT_12);
SPI2BUF=0x06;	//write enable latch of EEPROM
mPORTDSetBits(BIT_12);

delay(1000000);

mPORTDClearBits(BIT_12);
SPI2BUF=0x02;		//write data to memory
//delay(10000);
SPI2BUF=0x00;
SPI2BUF=0x00;
SPI2BUF=0x00;

//delay(10000);
//while(!SPI2STATbits.SPITBE);
SPI2BUF='A';
delay(10000);
if(SPI2BUF=0)
{
mPORTASetBits(BIT_1);	
}
mPORTDSetBits(BIT_12);
a=SPI2BUF;
mPORTDClearBits(BIT_12);
SPI2BUF=0x04;				//write disable
mPORTDSetBits(BIT_12);
SPI2CONCLR=0x8000;
*/
unsigned long address=0x00C0;
BYTE getdata;
lcdconfig();
a=SPI2BUF;
while(SPI2ASTATbits.SPIBUSY == 1)
continue;
  //  PORTA=0x0F7;
delay(100);
SPI2CON=0x00008060;	
ENABLE_CS();  
SPI_WriteByte(0x03);
SPI_WriteByte(0x00);
SPI_WriteByte(address>>8);
SPI_WriteByte(address & 0xFF);

getdata=SPI_ReadByte();




lcddata(value);
PORTA=0xFF;

//SPI2CON=0x00000000;
//while(SPI2CON&0x8000==1); 


																																																																																																																								
delay(1000000);	
mPORTDSetBits(BIT_12);


}


void delay(unsigned int itime)
{
	unsigned int i,j;
	for(i=1;i<itime;i++);
	{
		for(j=0;j<1250;j++)
			{
			
			}
	}
}	

void lcdconfig()
{
	PORTSetPinsDigitalOut(IOPORT_D,BIT_4 | BIT_5);
	mPORTESetPinsDigitalOut(BIT_0 | BIT_1 | BIT_2 | BIT_3 | BIT_4 | BIT_5 | BIT_6 | BIT_7);
	lcdcmnd(0x38); //init lcd 2 line 5x7 matrix
    delay(1000000);
    lcdcmnd(0x0E); //display on cursor blink
    delay(1000000);
    lcdcmnd(0x01); // clear display
    delay(1000000);
    lcdcmnd(0x06); // shift cursor right
    delay(1000000);
    lcdcmnd(0x84); // cursor at line 1 pos. 4
    delay(1000000);
}
void lcdcmnd(unsigned char value)
{
	PORTE=value;
	delay(1000000);
 	mPORTDClearBits(BIT_5);   // RS=0 write
	mPORTDSetBits(BIT_4);
	delay(1000000);
	mPORTDClearBits(BIT_4);

}
void lcddata(unsigned char receivedata)
{

PORTE=receivedata;
	delay(1000000);
	//mPORTBSetBits(BIT_15); 
	mPORTDSetBits(BIT_5);//RS=1 write
	mPORTDSetBits(BIT_4);
	delay(1000000);
	mPORTDClearBits(BIT_4);

}
BYTE SPI_WriteByte(int byte)
{
	BYTE dummy_rd;
    
	/* Wait: SPI peripheral to become idle and transmit buffer empty*/
    while(!SPI2STATbits.SPITBE);  // SPIxTXB is not empty
    SPI2BUF = byte;
    // Wait for data byte
    while(!SPI2STATbits.SPIRBF);  //

    dummy_rd = SPI2BUF;
   PORTA=0x0000;
   msdelay(10000);
	return dummy_rd; 
}
BYTE SPI_ReadByte(void)
 {
    //char spi_read;
 	BYTE temp;
    temp = SPI_WriteByte(0x00); /* Dummy write to get SCK running */
 	

    if (SPI2STATbits.SPIROV == 1)
    {
       SPI2ASTATCLR = 0x00000040;
    }
    PORTA=0x0F3;
    return temp;
 }

void DISABLE_CS(void)
{
while (SPI2ASTATbits.SPIBUSY == 1)
continue;
 	 //Added delay before disabling /CS per Errata 
delay(100000);          //100ns
mPORTDSetBits(BIT_12);   
delay(50000);
} 

void ENABLE_CS(void)     
{
    mPORTDClearBits(BIT_12);
	msdelay(50000);  //50ns
}          