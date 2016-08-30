//memory code working for 1mb memory

//5-3-2012...eeprom checking
#include<plib.h>
//********************SPI SECTION*******************

#define chipselect LATDbits.LATD12		    //~CS

//spi instruction set.....//
#define read      (unsigned)0x03   //Read data from memory array beginning at selected address
#define write	  (unsigned)0x02   //Write data to memory array beginning at selected address	
#define wrdi	  (unsigned)0x04   //Reset the write enable latch (disable write operations)	
#define wren	  (unsigned)0x06   //Set the write enable latch (enable write operations) 	
#define rdsr      (unsigned)0x05   //read status register
#define wrsr      (unsigned)0x01   //write status register

void chip_select(void);
void SPIWIPPolling(void);
void SPIWELPolling(void);
char SPI1_transfer(char);
void WREn(void);
void WRDi(void);
void WRSr(void);
int eraseEEPROM();
void ENABLE_CS(void);
void DISABLE_CS(void);
BYTE SPI_WriteByte(int byte);
BYTE SPI_ReadByte(void);
unsigned char check_status(void);
void send_8_bit(int _8_data);
void send_16_bit(short _16_data);

unsigned char read_ext_eeprom(unsigned long address); 
void write_ext_eeprom(unsigned short address,unsigned short data); 				
unsigned char Status;
unsigned long i;
int n; 
int main()
	{	
		char arry[255]={0};
		mJTAGPortEnable(0);
		lcd_config();
		lcd_ini();
		chip_select();			       //select the slavehhjhjkhk
		
unsigned short address=0x0000;
unsigned char da_ta=0x20;
unsigned char loc=0x80;


		for(i=0x0000,n=0;n<255;i++,n++)	
		{
			lcd_ini();
			arry[n]=read_ext_eeprom(i);
			
			
		}
			
	}
void chip_select(void)
{
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
}


unsigned char read_ext_eeprom(unsigned long address) 
{	
	while (SPI2ASTATbits.SPIBUSY == 1)
       continue;
	SPI2CON=0x00008060;				//enable the spi peripheral-8160
	BYTE lsb,msb;
	//SPIWIPPolling();	
	int data2=0;
	ENABLE_CS();                       //chip select 
	send_8_bit(read);
	send_8_bit(0x00);	                               	//read operation starts
    send_8_bit(address>>8);	                               	//read operation starts
	send_8_bit((address & 0xFF));	                               	//read operation starts
//	send_8_bit(0x00);

//data2=SPI_ReadByte();
	msb = SPI_ReadByte();
//	lsb = SPI_ReadByte();
	DISABLE_CS();
//	data2=((msb<<8) + lsb); 
//	SPI2STATCLR = 0x40;                                 //clear overflow flag
//	SPI2CONCLR=0x00008000;				                //OFF SPI	
	return msb;
}



void DISABLE_CS(void)
 {
    while (SPI2ASTATbits.SPIBUSY == 1)
       continue;
 	/* Added delay before disabling /CS per Errata #6 */
    Delay(100000);          //100ns
 	mPORTDSetBits(BIT_12);   
	Delay(50000);           //50ns  
 }
 void ENABLE_CS(void)     
 {
    mPORTDClearBits(BIT_12);
	Delay(50000);  //50ns
 }

BYTE SPI_WriteByte(int byte)
{
	BYTE dummy_rd;
    
	/* Wait: SPI peripheral to become idle and transmit buffer empty*/
    while(!SPI2STATbits.SPITBE);  // SPIxTXB is not empty
    SPI2BUF = byte;
    while(!SPI2STATbits.SPIRBF);  
	dummy_rd = SPI2BUF;
	return dummy_rd; 
}
 
BYTE SPI_ReadByte(void)
 {
   
 	BYTE temp;
    temp = SPI_WriteByte(0x00); /* Dummy write to get SCK running */
 	

    
    if (SPI2STATbits.SPIROV == 1)
    {
       SPI2ASTATCLR = 0x00000040;
    }
 
    return temp;
 }
int eraseEEPROM()
{
    //SPIWIPPolling();
	ENABLE_CS();	                // Select EEPROM
    send_8_bit(wren);   			// Send WRITE_ENABLE command
    DISABLE_CS();	                // Select EEPROM
    
	Delay(20000);
    ENABLE_CS();	                // Select EEPROM
    send_8_bit( 0xc7);     		// send CHIP_ERASE command
  	DISABLE_CS();	                // Select EEPROM
    return 0;
} // END eraseEEPROM()

void send_8_bit(int _8_data)
{
	//SPI2CON=0x00008060;
	SPI_WriteByte(_8_data);
}

void send_16_bit(short _16_data)
{
	//SPI2CON=0x00008760;
	SPI_WriteByte(_16_data);
}

//	unsigned int read_MSB = SPI2_transfer( 0x00);  //data shifted on SO pin---reading data on MISO pin
//	unsigned int read_LSB = SPI2_transfer( 0x00);  //data shifted on SO pin---reading data on MISO pin
//	DISABLE_CS() //chip deselect 	
//	SPI2STATCLR = 0x40;                                 //clear overflow flag
//	SPI2CONCLR=0x00008000;				                //OFF SPI
//	return ((read_MSB<<8)+read_LSB);
//SPI_WriteByte(address>>8);  	  	// Output MSB of address
//  SPI_WriteByte(address & 0xFF);          	// Output LSB of address/
void SPIWELPolling(void)
 {
int a=0;
   		 do{
		 	ENABLE_CS();                       //Select Device
		 	SPI_WriteByte(rdsr);                //Read Status Reg OpCode
			a=SPI_ReadByte();                //dummy
			DISABLE_CS();
			Delay(100);
		}while ((a & 0x02) != 0);            //Check for WIP bit Set
}











