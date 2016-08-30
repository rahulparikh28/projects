// PeriodicSysTickInts.c
// Runs on LM4F120 or TM4C123
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano
// September 14, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013
   Volume 1, Program 9.6
   
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013
   Volume 2, Program 5.12, section 5.7

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// Rahul Parikh and Chittibabu Chatla


#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))  // Sys. Handlers 12 to 15 Priority
#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
unsigned long count = 0;      // global variable for reference
// **************SysTick_Init*********************
// Initialize SysTick periodic interrupts
// Input: interrupt period
//        Units of period are 62.5ns (assuming 16 MHz clock)
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR
// Output: none
void SysTick_Init(unsigned long period){
  NVIC_ST_CTRL_R = 0;                                         // (1) disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;                                // (2) reload value
  NVIC_ST_CURRENT_R = 0;                                      // (3) any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000;  // (4) priority 1
  NVIC_ST_CTRL_R = 0x07;                                      // (5) enable SysTick with core clock and interrupts
  EnableInterrupts();
}
// Interrupt service routine
// Executed every 1ms period
void SysTick_Handler(void){
	count++;
	if(count%2==0){
	GPIO_PORTE_DATA_R ^= 0x02;                                  // (6) toggle PE1
  count = 0;
	}
	else{
		GPIO_PORTE_DATA_R^=0X01;                                  // (7) toggle PE0
	}
}
int main(void){
  SYSCTL_RCGC2_R |= 0x00000010;                               // (8) activate clock for port E
  count = 1;                                                  // (9) initialize the counter and giving delay to settle the clock
  GPIO_PORTE_DIR_R |= 0x03;                                   // (10) make PE1-0 output 
  GPIO_PORTE_AFSEL_R &= ~0x03;                                // (11) disable alternet functions on PE1-0
  GPIO_PORTE_DEN_R |= 0x03;                                   // (12) enable digital I/O on PE1-0
  GPIO_PORTE_PCTL_R=(GPIO_PORTE_PCTL_R&0xFFFFFF00)+0x00000000;// (13) configure PE1-0 as GPIO
  GPIO_PORTE_AMSEL_R = 0;                                     // (14) disable analog functionality on PE
	GPIO_PORTE_DATA_R=0X02;                                     // (15) initial condition to start output 
  SysTick_Init(16000);                                        // (16) initialize SysTick timer
  EnableInterrupts();                                         // (17) enable specified interrupts
	

  while(1){                                                   // (18)interrupts every 1ms, 500 Hz flash
    WaitForInterrupt();
  }
}