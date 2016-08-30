#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))  // IRQ 0 to 31 Set Enable Register
#define NVIC_PRI0_R             (*((volatile unsigned long *)0xE000E400))  // IRQ 28 to 31 Priority Register
#define NVIC_PRI1_R             (*((volatile unsigned long *)0xE000E404))
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
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

volatile unsigned long risingedges=0;
volatile unsigned long fallingedges=0;

void EdgeCounterInit(void){
SYSCTL_RCGC2_R |= 0x00000011; // (a) activate clock for port F
  fallingEdges = 0;             // (b) initialize counter
  risingedges = 0;
  GPIO_PORTE_DIR_R &= 0xFB;    // (c) make PF4 in (built-in button)
  GPIO_PORTE_AFSEL_R &= 0xFB;  //     disable alt funct on PF4
  GPIO_PORTE_DEN_R |= 0x04;     //     enable digital I/O on PF4   
  GPIO_PORTE_PCTL_R &= 0x00000000; // configure PF4 as GPIO
  GPIO_PORTE_AMSEL_R = 0;       //     disable analog functionality on PF
  GPIO_PORTE_PUR_R |= 0x04;     //     enable weak pull-up on PF4
  GPIO_PORTE_IS_R &= 0xFB;      // (d) PF4 is edge-sensitive
  GPIO_PORTE_IBE_R &= 0xFB;     //     PF4 is not both edges
  GPIO_PORTE_IEV_R &= 0xFB;     //     PF4 falling edge event
  GPIO_PORTE_ICR_R = 0x04;      // (e) clear flag4
  GPIO_PORTE_IM_R |= 0x04;      // (f) arm interrupt on PF4
	GPIO_PORTA_DIR_R &= 0xFD;    // (c) make PF4 in (built-in button)
  GPIO_PORTA_AFSEL_R &= 0xFD;  //     disable alt funct on PF4
  GPIO_PORTA_DEN_R |= 0x02;     //     enable digital I/O on PF4   
  GPIO_PORTA_PCTL_R &= 0x00000000; // configure PF4 as GPIO
  GPIO_PORTA_AMSEL_R = 0;       //     disable analog functionality on PF
  GPIO_PORTA_PUR_R |= 0x02;     //     enable weak pull-up on PF4
  GPIO_PORTA_IS_R &= 0xFD;      // (d) PF4 is edge-sensitive
  GPIO_PORTA_IBE_R &= 0xFD;     //     PF4 is not both edges
  GPIO_PORTA_IEV_R &= 0x02;     //     PF4 falling edge event
  GPIO_PORTA_ICR_R = 0x02;      // (e) clear flag4
  GPIO_PORTA_IM_R |= 0x02;      // (f) arm interrupt on PF4
  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00)|0x00000020; // (g) priority 1
	NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFFFF00)|0x00000000;
  NVIC_EN0_R = 0x00000011;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}
void GPIOPortE_Handler(void){
  GPIO_PORTE_ICR_R = 0x04;      // acknowledge flag4
  FallingEdges = FallingEdges + 2;
}
void GPIOPortA_Handler(void){
  GPIO_PORTA_ICR_R = 0x02;      // acknowledge flag4
  risingEdges = risingEdges + 1;
}
int main(void){
  EdgeCounter_Init();           // initialize GPIO Port F interrupt
  while(1){
    WaitForInterrupt();
  }
