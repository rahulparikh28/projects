// Lab6.c
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2013 
// Last Modified: 10/9/2013 
// Lab number: 5
// Brief description of the program
//   A digital piano with 4 keys and a 4-bit DAC
// Hardware connections


#include "tm4c123gh6pm.h"
#include "PLL.h"
#include "Sound.h"
#include "Piano.h"
#include "dac.h"
// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
unsigned long data1=0;                              //(1) Global Variable to read the input
int main(void){ 
	PLL_Init();                                       //(2) Initialize PLL for 80MHz Clock
  DAC_Init();                                       //(3) Initialize Output pins for DAC
	Sound_Init(1420);                                 //(4) Initialize Systick with some reload value
	Piano_Init();                                     //(5) Initialize Input pins 
	EnableInterrupts();                               //(6) Enable all interrupts
while(1){ 
	 data1=Piano_In();                                //(7) read the input
	if(data1==0x04){                                  //(8) check if switch for note A is preesed 
     Sound_Play(1420);                              //(9) give systick relaod value for for note A 
	NVIC_ST_CTRL_R = 0x05;}                           //(10) disable systick interrupts           		
  else if(data1==0x08){                             //(11) check if switch for note B is preesed
    Sound_Play(1265);                               //(12) give systick relaod value for for note B
	NVIC_ST_CTRL_R = 0x05;}                           //(13) disable systick interrupts           		
  else if(data1==0x10){                             //(14) check if switch for note C is preesed
     Sound_Play(2385);                              //(15) give systick relaod value for for note C
	NVIC_ST_CTRL_R = 0x05;}                           //(16) disable systick interrupts
}                  
}                                            