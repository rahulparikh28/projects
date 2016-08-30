// dac.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2013 
// Last Modified: 10/9/2013 
// Lab number: 6
// Hardware connections

#include "tm4c123gh6pm.h"
// put code definitions for the software (actual C code)
// this file explains how the module works

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){unsigned long count;                      // User define function to initialize the DAC pins
	SYSCTL_RCGC2_R |= 0x00000010;                               // (1) activate clock for port E
  count = 1;                                                  // (2) giving delay to settle the clock
  GPIO_PORTE_DIR_R |= 0x1F;                                   // (3) make PE4-0 input 
  GPIO_PORTE_AFSEL_R &= 0x00;                                 // (4) disable alternet function on PE4-0
  GPIO_PORTE_DEN_R |= 0x1F;                                   // (5) enable digital I/O on PE4-0   
  GPIO_PORTE_PCTL_R &= 0x00000000;                            // (6) configure PE4-0 as GPIO
  GPIO_PORTE_AMSEL_R = 0;                                     // (7) disable analog functionality on PE
  }
// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){                             // User define function to give output
	GPIO_PORTE_DATA_R=data&0X0F;                                // (8) give output to DAC 
}