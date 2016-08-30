// EdgeInterrupt.c
// Runs on LM4F120 or TM4C123
// Request an interrupt on the falling edge of PF4 (when the user
// button is pressed) and increment a counter in the interrupt.  Note
// that button bouncing is not addressed.
// Daniel Valvano
// September 14, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013
   Volume 1, Program 9.4
   
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013
   Volume 2, Program 5.6, Section 5.5

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

// created by Rahul Parikh and Chittibabu Chatla 

#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))  // IRQ 0 to 31 Set Enable Register
#define NVIC_PRI0_R             (*((volatile unsigned long *)0xE000E400))  // IRQ 0 to 3 Priority Register
#define NVIC_PRI1_R             (*((volatile unsigned long *)0xE000E404))
#define GPIO_PORTE_DATA_R        (*((volatile unsigned long *)0x400243FC))  // IRQ 4 to 7 Priority Register
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTE_IS_R         (*((volatile unsigned long *)0x40024404))
#define GPIO_PORTA_IS_R         (*((volatile unsigned long *)0x40004404))
#define GPIO_PORTE_IBE_R        (*((volatile unsigned long *)0x40004408))
#define GPIO_PORTA_IBE_R        (*((volatile unsigned long *)0x40024408))
#define GPIO_PORTE_IEV_R        (*((volatile unsigned long *)0x4002440C))
#define GPIO_PORTA_IEV_R        (*((volatile unsigned long *)0x4000440C))
#define GPIO_PORTE_IM_R         (*((volatile unsigned long *)0x40024410))
#define GPIO_PORTA_IM_R         (*((volatile unsigned long *)0x40004410))
#define GPIO_PORTE_RIS_R        (*((volatile unsigned long *)0x40024414))
#define GPIO_PORTA_RIS_R        (*((volatile unsigned long *)0x40004414))
#define GPIO_PORTE_ICR_R        (*((volatile unsigned long *)0x4002441C))
#define GPIO_PORTA_ICR_R        (*((volatile unsigned long *)0x4000441C))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTE_PDR_R        (*((volatile unsigned long *)0x40024514))
#define GPIO_PORTA_PDR_R        (*((volatile unsigned long *)0x40004514))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
// global variable visible in Watch window of debugger
// increments at least once per button press
volatile unsigned long CPA2=0;       // global variable declared for counter port A
volatile unsigned long CPE3=0;       // global variable declared for counter port E
void EdgeCounter_Init(void){                          
  SYSCTL_RCGC2_R |= 0x00000011;      // (1) activate clock for port E and port A
  CPE3 = 0;                          // (2) initialize counter for port E
	CPA2 = 0;                          // (3) initialize counter for port A
  GPIO_PORTE_DIR_R |= 0x0F;          // (4) make PE3 input 
  GPIO_PORTE_AFSEL_R &= 0x00;        // (5) disable alternet function on PE3
  GPIO_PORTE_DEN_R |= 0x0F;          // (6) enable digital I/O on PE3   
  GPIO_PORTE_PCTL_R &= 0x00000000;   // (7) configure PE3 as GPIO
  GPIO_PORTE_AMSEL_R = 0;            // (8) disable analog functionality on PE
  //GPIO_PORTE_PDR_R |= 0x08;          // (9) enable  pulldown on PE3
  //GPIO_PORTE_IS_R &= 0xF7;           // (10) PE3 is edge-sensitive
  //GPIO_PORTE_IBE_R &= 0xF7;          // (11) PE3 is not both edges
  //GPIO_PORTE_IEV_R &= 0xF7;          // (12) PF4 falling edge event
  //GPIO_PORTE_ICR_R |= 0x08;          // (13) clear flag3
  //GPIO_PORTE_IM_R |= 0x08;           // (14) mark interrupt on PE3
	
	
	GPIO_PORTA_DIR_R &= 0xFB;          // (15) make PA2 input
  GPIO_PORTA_AFSEL_R &= 0xFB;        // (16) disable alternet function on PA2   
  GPIO_PORTA_DEN_R |= 0x04;          // (17) enable digital I/O on PA2   
  GPIO_PORTA_PCTL_R &= 0x00000000;   // (18) configure PA2 as GPIO
  GPIO_PORTA_AMSEL_R = 0;            // (19) disable analog functionality on PA
  GPIO_PORTA_PDR_R |= 0x04;          // (20) enable pulldown on PA2
  GPIO_PORTA_IS_R &= 0xFB;           // (21) PA2 is edge-sensitive
  GPIO_PORTA_IBE_R &= 0xFB;          // (22) PA2 is not both edges
  GPIO_PORTA_IEV_R |= 0x04;          // (23) PA2 falling edge event
  GPIO_PORTA_ICR_R = 0x04;           // (24) clear flag2
  GPIO_PORTA_IM_R |= 0x04;           // (25) mark interrupt on PA2
  //NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00)|0x00000020; // (26) priority 1 for port E
	NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFFFF00)|0x00000000; // (27) priority 2 for port A
  NVIC_EN0_R = 0x0000001;           // (28) enable interrupt on port E and A
  EnableInterrupts();                // (29) Clears the I bit
}
/*void GPIOPortE_Handler(void){        // (30) Interrupt sub routine for port E
  GPIO_PORTE_ICR_R = 0x08;           // (31) acknowledge flag3
  CPE3=CPE3 + 2;                     // (32) counter for port E
}*/
void GPIOPortA_Handler(void){        // (34) Interrupt sub routine for port A
  GPIO_PORTA_ICR_R = 0x04;
	CPA2 = CPA2 + 1;
GPIO_PORTE_DATA_R=CPA2;	// (35) acknowledge flag2
                     // (36) counter for port A
}
int main(void){
  EdgeCounter_Init();                // (37) initialize GPIO Port E and Port A interrupt
  //GPIO_PORTE_DATA_R=0x07;
	while(1){
  WaitForInterrupt();                // (38) wait for interrupt to come
  }
}