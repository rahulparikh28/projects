#include<p32xxxx.h>
#include<plib.h>
void delay();

int main()
{
    while(1)
  {
	delay();
	TRISA=0x0000;
	PORTA=0x000f;
	delay();
	TRISA=0x0000;
	PORTA=0x00f0;
  }
}

 
void delay()
 {
	 unsigned int i;
	 i=1000*1000;
     while(i--);
  }
	  