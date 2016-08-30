// Piano.c
// This software configures the off-board piano keys
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2013 
// Last Modified: 10/9/2013 
// Section 1-2pm     TA: Saugata Bhattacharyya
// Lab number: 6
// Hardware connections

#include "tm4c123gh6pm.h"
#include "Sound.h"
// put code definitions for the software (actual C code)
// this file explains how the module works

// **************Piano_Init*********************
// Initialize piano key inputs, called once 
// Input: none 
// Output: none
void EnableInterrupts(void); 
void Piano_Init(void){               // User define function to initialize the input pins 
	unsigned long data1;
	SYSCTL_RCGC2_R |= 0x00000001;      //(1) gatting clock for portA
	data1=0;                           //(2) wait for 4byte cycle to settle the clock
	GPIO_PORTA_DIR_R &= 0xE3;          //(3) make PA4-2 input
  GPIO_PORTA_AFSEL_R &= 0xE3;        //(4) disable alternet function on PA4-2   
  GPIO_PORTA_DEN_R |= 0x1C;          //(5) enable digital I/O on PA4-2   
  GPIO_PORTA_PCTL_R &= 0x00000000;   //(6) configure PA4-2 as GPIO
  GPIO_PORTA_AMSEL_R = 0;            //(7) disable analog functionality on Port A
}
// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 0 to 7 depending on keys
// 0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2
unsigned long Piano_In(void){         // User define function to read the input from switches
 unsigned long a=0;
 a=GPIO_PORTA_DATA_R&0x01C;           //(8) Read PA4-2
 return a;                            //(9) return value where it is called
}