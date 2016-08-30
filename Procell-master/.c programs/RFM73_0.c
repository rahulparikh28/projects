#include <plib.h>
#include <p32xxxx.h> 
extern void lcddata(unsigned char);
extern void lcdconfig();
extern void lcdcmd(unsigned char);
void rfm_init();
void rfm73_mode_transmit();
void delay();
void rfm73_mode_receive();
void rfm73_register_write(unsigned char,unsigned char);
unsigned char rfm73_register_read(unsigned char);
//char rfm73_spi_rw(unsigned char);
void SPI_INIT();


// RFM73 SPI read and write commands
#define RFM73_CMD_READ_REG     0x00
#define RFM73_CMD_WRITE_REG    0x20
#define RFM73_CMD_FLUSH_TX     0xE1
#define RFM73_CMD_FLUSH_RX     0xE2
//#define RFM73_CMD_AIRDATARATE		  2 MBPS
//#define RFM73_CMD_CRC_length
#define RFM73_CMD_ACTIVATE    0x50
#define RFM73_REG_STATUS      0x07
#define RFM73_REG_CONFIG      0x00
#define W_TX_PAYLOAD_NOACK    0xB0
#define REUSE_TX_PL           0xE3
 
#define MOSI  PORTGbits.RG8
#define MISO  PORTGbits.RG7
#define IRQ   PORTEbits.RE8
#define CE    PORTDbits.RD1
#define CSN   PORTGbits.RG9
#define SCK   PORTGbits.RG6


//interrupt status
#define STATUS          0x07  // 'Status' register address
#define STATUS_RX_DR    0x40
#define STATUS_TX_DS    0x20
#define STATUS_MAX_RT   0x10
 

//FIFO_STATUS

#define FIFO_STATUS           0x17  // 'FIFO Status Register' register address
#define FIFO_STATUS_TX_REUSE  0x40
#define FIFO_STATUS_TX_FULL   0x20
#define FIFO_STATUS_TX_EMPTY  0x10

#define FIFO_STATUS_RX_FULL   0x02
#define FIFO_STATUS_RX_EMPTY  0x01

//#define RFM73_MAX_PACKET_LEN  32
//typedef unsigned char rfm73_buffer [ RFM73_MAX_PACKET_LEN ];

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1

// Bank0 register initialization values
#define BANK0_ENTRIES 23
const unsigned char Bank0_Reg[ BANK0_ENTRIES ][ 2 ]={
	{ (0x20|0x00),  0x0B },  //Alle Int's am IRQ Pin active low ausgeben, CRC an, CRC Encoding 1 byte, Power Up, Transmitter
    { (0x20|0x01),  0x3F },  //Auto Acknowledge auf alle pipes aktivieren
    { (0x20|0x02),  0x3F },  //alle Datenpipes aktivieren
    { (0x20|0x03),  0x03 },  //RX/TX 5 byte lange Adresse für Empfänger/Sender
    { (0x20|0x04),  0x27 },  //Auto Retransmition delay 500us, Auto Retransmision aus
    { (0x20|0x05),  0x3F },  //kanal = 18
    { (0x20|0x06),  0x37 },  //Air Data Rate 2Mbps, Transmit Power 5dBm, LNA gain -20dB
    { (0x20|0x07),  0x00 },   // Statusregister
    { (0x20|0x08),  0x00 },  //Read only Transmit Observe Register, zählt Packet loss und retransmits
    { (0x20|0x09),  0x00 },  //Read only Carrier Detect (?)
    { (0x20|0x0C),  0xC3 },  //LSB Addr pipe 2
    { (0x20|0x0D),  0xC4 },  //LSB Addr pipe 3
    { (0x20|0x0E),  0xC5 },  //LSB Addr pipe 4
    { (0x20|0x0F),  0xC6 },  //LSB Addr pipe 5
    { (0x20|0x11),  0x32 },  // 32 bytes RX Payload in pipe0 ------>?
    { (0x20|0x12),  0x32 },  // 32 bytes RX Payload in pipe1 ------>?
    { (0x20|0x13),  0x32 },  // 32 bytes RX Payload in pipe2 ------>?
    { (0x20|0x14),  0x32 },  // 32 bytes RX Payload in pipe3 ------>?
    { (0x20|0x15),  0x32 },  // 32 bytes RX Payload in pipe4 ------>?
    { (0x20|0x16),  0x32 },  // 32 bytes RX Payload in pipe5 ------>?
    { (0x20|0x17),  0x11 },  // FIFO Flag Register, ansich Read Only
    { (0x20|0x1C),  0x3F },  //  Dynamic Payload length für alle pipes aktiviert
    { (0x20|0x1D),  0x07 }   //Enables Dynamic Payload Length,Enables Payload with ACK
};

int main()
{

 mJTAGPortEnable(0);
 mPORTGSetPinsDigitalOut(BIT_6 | BIT_8 | BIT_9);
 mPORTESetPinsDigitalIn(BIT_8);
 mPORTGSetPinsDigitalIn(BIT_7);
 mPORTDSetPinsDigitalOut(BIT_1);
 mPORTASetPinsDigitalOut(0xFF);
 mPORTAClearBits(0xFF);
 mPORTCClearBits(BIT_4);

  lcdconfig();
  SPI_INIT();
  rfm_init();
  

   unsigned char value;
   // flush receive queue 
  // rfm73_register_write( (RFM73_CMD_FLUSH_RX|0x20), 0x00 );
    CSN=0; 
    delay(1000000000);
    SPI2BUF=RFM73_CMD_FLUSH_RX;
	CSN=1;
    // clear interrupt status
  // value = rfm73_register_read( RFM73_REG_STATUS );
  // rfm73_register_write( RFM73_REG_STATUS,value );

   
   rfm73_mode_receive();
   CE=1;
   SPI2BUF='A';
   delay(1000000000);
   rfm73_mode_transmit();
   SPI2BUF=0;
   while(1)
   {
    CE=0;
    CSN=0; 
    delay(1000000000);
    SPI2BUF=W_TX_PAYLOAD_NOACK;
    delay(1000000000);
    CE=1;
    SPI2BUF='A';
    delay(1000000000);
	CSN=1; 
    delay(1000000000);
   }   
}

//initialize the wireless module rfm73
void rfm_init(void)
{
 CE=0;
 CSN=1;
 SCK=0;
 MOSI=0;
 delay(1000000);
// rfm73_register_write(RFM73_CMD_ACTIVATE,0x53);
    CSN=0; 
    delay(1000000000);
    SPI2BUF=RFM73_CMD_ACTIVATE;
    delay(1000000000);
    SPI2BUF=0x73;
    delay(1000000000);
	CSN=1;

 unsigned char i;
 for( i = 0; i < BANK0_ENTRIES; i++ )
 {
    // rfm73_register_write( Bank0_Reg[i][0], Bank0_Reg[ i ][1] );
    CSN=0; 
    delay(1000000000);
    SPI2BUF=Bank0_Reg[i][0];
    delay(1000000000);
    SPI2BUF=Bank0_Reg[ i ][1];
    delay(1000000000);
	CSN=1;


 }

}

//put rfm73 into the transmit mode
void rfm73_mode_transmit( void )
{
unsigned char value;
	
	if (SPI2STAT==0x00000001)
	{ 
      PORTA=0xFF;	
      // flush receive queue 
  // rfm73_register_write((RFM73_CMD_FLUSH_TX|0x20), 0 );
    CSN=0; 
    delay(1000000000);
    SPI2BUF=RFM73_CMD_FLUSH_TX;
	CSN=1;
      // clear interrupt status
   //value = rfm73_register_read( RFM73_REG_STATUS );
   //rfm73_register_write( RFM73_REG_STATUS ,value );
   
	
      //  delay();
	   	CE=0;
   	//	value = rfm73_register_read( RFM73_REG_CONFIG );                   //RFM73_REG_CONFIG will be set 		
   		value = 0xFE; // set tx bit
   	//	value |= 0x02; // set PWR_UP bit
    //    rfm73_register_write((RFM73_REG_CONFIG|0x20), value );
     CSN=0; 
    delay(1000000000);
    SPI2BUF=(RFM73_REG_CONFIG|0x20);
    delay(1000000000);
    SPI2BUF=value;
    delay(1000000000);
	CSN=1;
    CE=1;
	}
}

//delay
void delay(unsigned int time)
{
unsigned int i;
for(i=0;i<time/140;i++);
}

//put rfm73 into the receive mode
void rfm73_mode_receive( void )
{
  CE=0;
  CSN=1;
  SCK=0;
  MOSI=0;

    unsigned char value;
 
   // flush transmit queue 
  // rfm73_register_write((RFM73_CMD_FLUSH_RX|0x20), 0x00 );
    CSN=0; 
    delay(1000000000);
    SPI2BUF=RFM73_CMD_FLUSH_RX;
	CSN=1;

    // clear interrupt status
 //  value = rfm73_register_read( RFM73_REG_STATUS );
 //  rfm73_register_write( RFM73_REG_STATUS ,value );
   
	// switch to receive mode
	//SPI2CONSET=0x00008800;
	//SPI2BUF='A';
	
//	CE=0;//CE=0
   

  // value = rfm73_register_read( RFM73_REG_CONFIG );		
  // value &= 0xFE; // clear RX bit
  // value |= 0x01; // set rx bit
  // rfm73_register_write( (RFM73_REG_CONFIG | 0x20),0x0B );
    //CE=1;
   // SPI2BUF=W_TX_PAYLOAD_NOACK;  //no ACK
   // SPI2BUF=REUSE_TX_PL;  //reuse last transmitted packet
  
}
/*
void rfm73_register_write(unsigned char reg,unsigned char value)
{
	CSN=0; 
    delay(1000000000);
    SPI2BUF=reg;
    delay(1000000000);
    SPI2BUF=value;
    delay(1000000000);
	CSN=1;  
}


unsigned char rfm73_register_read(unsigned char reg)
{
   unsigned char value;
	CSN=0;  
    //value=rfm73_spi_rw(reg);
    delay(1000000000);
    SPI2BUF=reg;
    delay(1000000000);
    value = SPI2BUF;
    CSN=1;
	return(value);
}



 
char rfm73_spi_rw(unsigned char value)
{

 unsigned char i,j; 
PORTA=0xF0;
MOSI==1;
delay(10000000000);
while(MOSI==1);
PORTA=0x0F;
 for(i=0;i<8;i++);
	{
		//delay(1000000);
		if((value & 0x80)==0x80)
		{
			MOSI=1;
          
          //delay(1000000000);
		}
		else
		{
			MOSI=0;		
		}
		//delay(10000000); 
		value = (value << 1);        // shift next bit into MSB..
		SCK=1;       	            // Set SCK high..
		j |= MISO;              // capture current MISO bit
        j = (j >> 1 );
		SCK=0;                     // ..then set SCK low again
	}
   //lcddata(j | 0x30);
	return(j);      
}*/



//now initialize the SPI of the PIC32MX

void SPI_INIT(void)
{

	IEC1CLR=0x000000E0;			// disable all interrupts
	SPI2CON =0; 				// Stops and resets the SPI2.
	SPI2BUF=0; 				// clears the receive buffer
	IFS1CLR=0x000000E0; 		// clear any existing event
	IPC7CLR=0x1f000000; 		// clear the priority
	IPC7SET=0x0d000000; 		// Set IPL=3, Subpriority 1
	IEC1SET=0x000000E0; 		// Enable Rx, Tx and Error interrupts
	SPI2STATCLR=0x40;
    SPI2BRG=9;
    SPI2STATbits.SPIROV=0;      // clear the Overflow
    SPI2CON=0x8220;			// SPI ON, 8 bits transfer, Master mode

}

