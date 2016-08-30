// Sound.c, 
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2013 
// Last Modified: 10/9/2013 
// Lab number: 6
// Hardware connections
#include "tm4c123gh6pm.h"
#include "dac.h"
// put code definitions for the software (actual C code)
// this file explains how the module works

unsigned long b[128]={8,8,8,9,9,9,10,10,10,11,11,                        // vlues for sine waves 
	11,12,12,12,13,13,13,13,14,14,14,14,14,14,15,15,
	15,15,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,
	14,14,13,13,13,13,12,12,12,11,11,11,10,10,10,9,9,9,
	8,8,8,7,7,6,6,6,5,5,5,4,4,4,3,3,3,2,2,2,2,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,3,
  3,3,4,4,4,5,5,5,6,6,6,7,7};
unsigned long i=0;                                           // global varible for index(to access the array elements)
// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Input: Initial interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
// Output: none
void Sound_Init(unsigned long period){                        // User define function for systick initialization
	NVIC_ST_CTRL_R = 0;                                         // (1) disable systick for initialization       
  NVIC_ST_RELOAD_R = period-1;                                // (2) give reload value
  NVIC_ST_CURRENT_R = 0;                                      // (3) anything write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000;  // (4) give systick priority 1
  }
// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//         input of zero disables sound output
// Output: none
void Sound_Play(unsigned long period){                     // User define function for relpading the value as switch is pressd
	NVIC_ST_RELOAD_R = period-1;                             // (5) reload new value for systick
	NVIC_ST_CTRL_R = 0x07;                                   // (6) enable interrupt for systick
}
// Interrupt service routine
// Executed periodically, the actual period
// determined by the current Reload.
void SysTick_Handler(void){                                // Interrupt sevice routine for systick
	GPIO_PORTE_DATA_R^=0x10;                                 // (7) toggle pin 5 of port E to creat heartbeat signal
	DAC_Out(b[i]);                                           // (8) give output to DAC pins
	if(i==127){                                              // (9) check weather i value is overloading or not  
		i=0;                                                   // (10) i back to 0
}
	i++;                                                     // (11) Increament the index
}