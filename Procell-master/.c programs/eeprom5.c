//5-3-2012...eeprom checking
#include"exp16.h"
//********************SPI SECTION*******************

#define BIT_MOSI   TRISGbits.TRISG8		    //MOSI
#define BIT_MISO   TRISGbits.TRISG7			//MISO
#define BIT_SCK    TRISGbits.TRISG6           //SCk
#define chipselect TRISDbits.TRISD12		    //~CS
#define wrtprtct   TRISDbits.TRISD8			//~WP

//spi instruction set.....//
#define read      3   //Read data from memory array beginning at selected address
#define write	  2   //Write data to memory array beginning at selected address	
#define wrdi	  4   //Reset the write enable latch (disable write operations)	
#define wren	  6   //Set the write enable latch (enable write operations) 	
#define rdsr      5   //read status register
#define wrsr      1   //write status register

//void delay(unsigned int);
void chip_select(void);
void SPIWIPPolling(void);
void led1(void);
void led2(void);
void WREn(void);
void WRDi(void);
void check_status(void);
unsigned int read_ext_eeprom(unsigned char address);
void write_ext_eeprom(unsigned char address, unsigned int data); 				

unsigned int EP_write_value,read_sequence;
unsigned int EP_input_data=0;
unsigned char EP_read_value;
unsigned char buff[50];
unsigned char Status;
int i;

int main()
	{	
		SYSTEMConfigWaitStatesAndPB(80000000L);
		CheKseg0CacheOn();			// enable the cache for the best performance
		mBMXDisableDRMWaitState(); // no wait states for RAM
		lcd_config();
		SPI2BRG=9;            // use Fpb/10 clock frequency will give 10MHz....80/(2*(9+1))=10Mhz
		SPIWIPPolling();
//STATUS FLAG value initially		
		check_status();
		chip_select();			       //select the slave
unsigned char *address=0000;	
unsigned int data=10;	
		for(i=0;i<10;i++)
			{	
			//this loop write data....10 to address 0x0000 to 19 to address 0x0009   
			write_ext_eeprom(address,data);
			read_ext_eeprom(address);
			*address++;
			data++;
			}
}
void chip_select(void)
{

								
	
	OpenSPI2(SPI_MODE16_ON|SPI_CKE_OFF|CLK_POL_ACTIVE_LOW|SPI_SMP_OFF|SLAVE_ENABLE_ON|MASTER_ENABLE_ON|SEC_PRESCAL_1_1|PRI_PRESCAL_1_1, SPI_ENABLE); //to turn on the SPI modules
	SpiChnOpen(2, SPICON_MSTEN|SPICON_FRMEN|SPICON_SMP|SPICON_ON, 20);     	//fpdiv=4, will set BR=Fpb/4=10MHz	
	
	mPORTDSetPinsDigitalOut(BIT_12);        //chip select for eeprom
	mPORTGSetPinsDigitalOut(BIT_8);             //master out slave in 
	mPORTGSetPinsDigitalIn(BIT_7);    	       //master in slav out
	mPORTGSetPinsDigitalOut(BIT_6);    	       //clk out
	mPORTDSetPinsDigitalOut(BIT_8);             //write protect
	mPORTDSetBits(BIT_8);
	//wrtprtct=1;  //~WP=HIGH so writes to the non volatile
				 //bits in the status register operates normally
	
	unsigned int dump=SPI2BUF;					//clears the receive buffer
	lcd_ini();
	lcd_data("dump:");
	lcdcmd(0x85);	
	ConvertData(dump);		                    //take initial data from SPI2BUF and clear SPI2BUF
	Delay(140000000);   //1us delay
	}

void SPIWIPPolling(void)
 {
   	
		 do{
		 	chipselect = 0;                    //Select Device
		 	BIT_SCK=1;  					   //sck on
			WriteSPI2 ( 0x05 );                //Read Status Reg OpCode
		 	Status = ReadSPI2();               //Read Status Reg
			BIT_SCK=0;  					   //sck off
			chipselect = 1;                    //Deselect Device
		 	}while (Status & 0x01);            //Check for WIP bit Set
}
void write_ext_eeprom(unsigned char address, unsigned int data)
{
 	while(SPI2STAT && 0x00000008 == 0x00000000);	    //check transmit buffer is empty or not
	SPI2CONSET=0x10008700;				//enable the spi peripheral
						  				//ckp=1,idle=high,active =low,smp=0,cke=0(data input sample phase bit) 28-MSSEN bit enable
 	while(SPI2STAT && 0x00000800 == 0x00000000);	    //check 11th bit either SPI is BUSY or NOT,make sure it is 0 
	
	SPI2CON = 0;		  // stop and reset the SPI2
	SPI2CONSET=0x00008000;// turn on SPI
	//IFS1CLR=0x03800000;   // clear any existing event
	//IFS1SET=0x000000E0;   // tx,rx and RV interrupt
	//IPC5CLR=0x1f000000;   // clear the priorityf
	//IPC5SET=0x0d000000;   // Set IPL=3, Subpriority 1
	//IPC7SET=0x1F000000;
	//IEC1SET=0x00000E0;   // Enable Rx, Tx and Error interrupts
	
	unsigned long IEC1_SAVE=IEC1;       // save IEC1 data
	IEC1CLR=0xFFFFFFFF;  				// disable all interrupts
	//display IEC1 data on LCD
						
		
/*	SPI2BUF=0x65; 		// transmit an A character
	EP_read_value=SPI2BUF;
	lcd_ini();
	lcd_data("send val:");
	ConvertData(EP_read_value);
*/
	

/*
						SpiChnPutC(2,wren);                                 //write enable 
						SpiChnPutC(2,write);                                //write enable 
						SpiChnPutC(2,address >> 8);						    //the first 16-bit address
						SpiChnPutC(2,address);						        //the first 16-bit address
					
						putcSPI2(wren);				//put this instruction on SPI bus				
						putcSPI2(write);
						putcSPI2(address>>8);
						putcSPI2(address); 
*/ 
	
	WREn();             				//write ENABLE latch
	check_status();     				//all bits are ON
//write sequence start here
	mPORTDClearBits(BIT_12); 			//chip select 	
	mPORTGSetBits(BIT_6);	    		//sck on 
	WriteSPI2(write);  			 		//send write sequence
	WriteSPI2(address);
	WriteSPI2(data);  					//8 bit data	
	Delay(5000000);     				//wait for 5ms till transfer to complete   
//here receiver BUFF is FULL,tx BUFF,SPI busy here 	
	lcd_ini();
	ConvertData(SPI2STAT);
	Delay(140000000);
	while(SPI2STAT && 0x00000001 == 0x00000001);  		//wait for transfer to complete-rcv buff full 
	mPORTGClearBits(BIT_6); 		    //sck off 
	mPORTDSetBits(BIT_12); 				//chip deselect 	
	WRDi();               				//writ disable
	//IEC1=IEC1_SAVE;       			//reset the interrupts interrupts
	SPI2STATCLR=0x40;     				//clear the Overflow

	lcd_ini();
	lcd_data("sent:");
	lcdcmd(0xC0);
	ConvertData(data);
	lcdcmd(0x86);
	lcd_data("addr:");
	lcdcmd(0xC6);
	ConvertData(address);
	Delay(140000000);  
//		if(!TxBufFullSPI2())                                //check tx buffer untill it's full 
//		{
//		lcd_ini();
//		lcd_data("Tx BF is FULL:");
//		Delay(140000000);
//		}
		
// 			//testing
//TRISA=0;
//PORTA=0;
//Delay(10000);
//PORTA=0xFF;
//Delay(10000);
//PORTA=0;
	
	//WriteSPI2(data >> 8);           // send msb
    //WriteSPI2(data & 0xff);         // send lsb 
    //chipselect=0;										//select chip
	//SpiChnPutC(2,write);                                //write enable 
	//putcSPI2(0x2);
	//chipselect=1;

	//while(SPI2STAT && 0x00000800 == 0x00000000);	    //check 11th bit either SPI is BUSY or NOT,make sure it is 0 

	
		
	
//Stops and resets the SPI2.
//LATAINV=0x00FF;
//write cycle	
//-----check the status register
//	SpiChnPutC(2,wrsr);                                 //write status register
//	SpiChnPutC(2,0x8E);                                 //WPEN and WIP enable,BP0=BP1=1 set all address 0000-7FFFh write protect    	
//	SpiChnPutC(2,rdsr);                                 //read status register 
	 
//-----after every write cycle reset the WEL
	
//	while(SPI2STAT & 0x00000004 == 0x00000000);   		//chech if tx buffer is empty or not	
}
unsigned int read_ext_eeprom(unsigned char address) 
{
    //SPIWIPPolling();
	
	OpenSPI2(SPI_MODE16_ON|SPI_CKE_OFF|CLK_POL_ACTIVE_LOW|SPI_SMP_OFF|SLAVE_ENABLE_ON|MASTER_ENABLE_ON|SEC_PRESCAL_1_1|PRI_PRESCAL_1_1, SPI_ENABLE); //to turn on the SPI modules
	SpiChnOpen(2, SPICON_FRMEN|SPICON_FRMSYNC|SPICON_SMP|SPICON_ON, 20);	//fpdiv=4, will set BR=Fpb/4=10MHz
		
	while(SPI2STAT && 0x00000800 == 0x00000000); 		//check 11th bit either SPI is BUSY or NOT 
	
	
	SPI2CON = 0;										//stop and reset the SPI2
	SPI2CONSET=0x10008700;  							//enable the spi peripheral-8840
	//read operation starts here	
	mPORTDClearBits(BIT_12); //chip select 
	mPORTGSetBits(BIT_6); //sck on	
	WriteSPI2(read);	                               	//read operation starts
    WriteSPI2(address);	          //give 16 bit address with 1st bit dn't care 
	while(SPI2STAT==0x00000849);  //wait until the TX buffer is empty,recbuf is full,data received,and spi is currently busy!!!            
	unsigned int received1 = PORTReadBits(IOPORT_G, BIT_7);  //data shifted on SO pin---reading data on MISO pin
	mPORTGClearBits(BIT_6); //sck off
//unsigned int *rdptr=address;
//unsigned char received2=getsSPI2(sizeof(buff),rdptr,10);
	mPORTDSetBits(BIT_12); //chip deselect 	
	SPI2STATCLR = 0x40;                                 //clear overflow flag
	SPI2CONCLR=0x00008000;				                //OFF SPI

	lcd_ini();
	lcd_data("received1:");
	lcdcmd(0xC0);
	ConvertData(received1);
	Delay(140000000);       

	//WriteSPI2(address>>8);          		// address MSB first
    //WriteSPI2(address & 0xfe);      		// address LSB (word aligned)
	//int msb = WriteSPI2(0);             		// send dummy, read data msb
    //int lsb = WriteSPI2(0);             		// send dummy, read data lsb
	//unsigned char got=((msb<<8) + lsb);
	//return (got);        // join objects + return integer
	//while(1);
	
//	unsigned int data3=SPI2BUF;
//	lcd_ini();
//	lcd_data("rcv SBUF:");
//	lcdcmd(0xC0);
//	ConvertData(data3);
//	Delay(140000000);
//
////read testing 
//	ReadSPI2();
//	unsigned int data2=ReadSPI2();      //waits for received data to be available
//
//	lcd_ini();
//	lcd_data("data2:");
//	lcdcmd(0xC0);
//	ConvertData(data2);
//	Delay(140000000);  

 

	
	

	//while(1);
	//EP_read_value  = SPI2BUF;   						//since overflow is cleared, buffer is read so that new data can come in

	
	//EP_read_value  = buff;   							//since overflow is cleared, buffer is read so that new data can come in
//	if(buff==0x05)
//		{
//			led1();
//		}
//	else
//		{
//			led2();
//		}
//	//buff=SPI2BUF;                                       //receive the data
	//SpiChnPutC(2,address>>8);				 			//the first 8-bit address
	//SpiChnPutC(2,address);				 				//the first 8-bit address


//	lcd_ini();
//	lcd_data("received:");
//	lcdcmd(0x89);
//	Delay(1000); //1 us
//	ConvertData(EP_read_value);
//	SPI2CONCLR=0x00008000;								//OFF SPI
//	return;										
//
														//ckp=1,idle=high,active =low,smp=0(data input sample phase bit)
	//SpiChnPutC(2,0x00);								//write the starting address
	//SpiChnPutC(2,rdsr);
	//*data=receive;									//store data at random address
	//data++;											//increment the address
	//length--;											//?????
	//EP_read_value=PORTReadBits(IOPORT_G, BIT_8);      //read the data from the spi receiver register		
	
	//while(SPI2STAT != 0x00000008){}        		 	    //check 1st bit showes the txbuf is empty or not
	
}
void led1(void)
{
	TRISA=0;
	PORTA=0;
	mPORTASetBits(BIT_0);   //led2
	Delay(1000000000);
}

void led2(void)
{
	TRISA=0;
	PORTA=0;
	mPORTASetBits(BIT_1);   //led3
	Delay(10000000);
}
void WREn(void)
{
//write flow....WREN sequence
	mPORTDClearBits(BIT_12); //chip select 	
	mPORTGSetBits(BIT_6);      //sck on  		
	WriteSPI2(wren);//write enable sequence  
	mPORTGClearBits(BIT_6);  //sck off 
	mPORTDSetBits(BIT_12); //chip deselect 	
	return;
}
void WRDi(void)
{
//write flow....WREN sequence
	mPORTDClearBits(BIT_12); //chip select 	
	mPORTGSetBits(BIT_6);      //sck on  		
	WriteSPI2(wren);//write enable sequence  
	mPORTGClearBits(BIT_6);      //sck off  		
	mPORTDSetBits(BIT_12); //chip deselect 	
	return;
}
void check_status(void)
{
			mPORTDClearBits(BIT_12); 	//chip select 	
			mPORTGSetBits(BIT_6);      //sck on  		
			WriteSPI2 ( 0x05 );                //Read Status Reg OpCode
		 	Status = ReadSPI2();               //Read Status Reg
			mPORTGClearBits(BIT_6);      //sck on  		
			mPORTDSetBits(BIT_12); 	//chip deselect 	
			lcd_ini();
			lcd_data("STATUS FLAG:");
			lcdcmd(0xc0);
			ConvertData(Status);
			Delay(140000000);
}
	









