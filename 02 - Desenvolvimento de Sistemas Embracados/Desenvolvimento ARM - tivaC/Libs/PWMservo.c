
#include <stdint.h>
#include "PWMservo.h"
#include <tm4c123gh6pm.h>
#define PWM_0_GENA_ACTCMPAD_ONE 0x000000C0  // Set the output signal to 1
#define PWM_0_GENA_ACTLOAD_ZERO 0x00000008  // Set the output signal to 0
#define PWM_0_GENB_ACTCMPBD_ONE 0x00000C00  // Set the output signal to 1
#define PWM_0_GENB_ACTLOAD_ZERO 0x00000008  // Set the output signal to 0

#define SYSCTL_RCC_USEPWMDIV    0x00100000  // Enable PWM Clock Divisor
#define SYSCTL_RCC_PWMDIV_M     0x000E0000  // PWM Unit Clock Divisor
#define SYSCTL_RCC_PWMDIV_2     0x00000000  // /2


// period is 16-bit number of PWM clock cycles in one period (3<=period)
// period for PB6 and PB7 must be the same
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
// PWM clock rate = processor clock rate/SYSCTL_RCC_PWMDIV
//                = BusClock/2 
//                = 80 MHz/2 = 40 MHz (in this example)
// Output on PB6/M0PWM0
void servo1PWM_Init(float freqCPU,float freqPWM,float porcentagem){

  SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
  SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
  while((SYSCTL_PRGPIO_R&0x02) == 0){};
  GPIO_PORTB_AFSEL_R |= 0x40;           // enable alt funct on PB6
  GPIO_PORTB_PCTL_R &= ~0x0F000000;     // configure PB6 as PWM0
  GPIO_PORTB_PCTL_R |= 0x04000000;
  GPIO_PORTB_AMSEL_R &= ~0x40;          // disable analog functionality on PB6
  GPIO_PORTB_DEN_R |= 0x40;             // enable digital I/O on PB6
  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R & (~0x000E0000));   //    configure for /2 divider

  PWM0_0_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM0_0_GENA_R = 0xC8;                 // low on LOAD, high on CMPA down
  // PB6 goes low on LOAD
  // PB6 goes high on CMPA down
  PWM0_0_LOAD_R = (1/freqPWM) * freqCPU;           // 5) cycles needed to count down to 0
  PWM0_0_CMPA_R = (PWM0_0_LOAD_R * porcentagem)/100;             // 6) count value when output rises
  PWM0_0_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM0_ENABLE_R |= 0x00000001;          // enable PB6/M0PWM0
}
// change duty cycle of PB6
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
void servo1PWM_Duty(float porcentagem){
  PWM0_0_CMPA_R = (PWM0_0_LOAD_R * porcentagem)/100;             // 6) count value when output rises
}


// period is 16-bit number of PWM clock cycles in one period (3<=period)
// period for PB6 and PB7 must be the same
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
// PWM clock rate = processor clock rate/SYSCTL_RCC_PWMDIV
//                = BusClock/2 
//                = 80 MHz/2 = 40 MHz (in this example)
// Output on PB7/M0PWM1
void servo2PWM_Init(float freqCPU,float freqPWM,float porcentagem){
  //volatile unsigned long delay;
  SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
  SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
  //delay = SYSCTL_RCGCGPIO_R;            // allow time to finish activating
  GPIO_PORTB_AFSEL_R |= 0x80;           // enable alt funct on PB7
  GPIO_PORTB_PCTL_R &= ~0xF0000000;     // configure PB7 as M0PWM1
  GPIO_PORTB_PCTL_R |= 0x40000000;

  GPIO_PORTB_AMSEL_R &= ~0x80;          // disable analog functionality on PB7
  GPIO_PORTB_DEN_R |= 0x80;             // enable digital I/O on PB7
  /*
  SYSCTL_RCC_R |= SYSCTL_RCC_USEPWMDIV; // 3) use PWM divider
  SYSCTL_RCC_R &= ~SYSCTL_RCC_PWMDIV_M; //    clear PWM divider field
  SYSCTL_RCC_R += SYSCTL_RCC_PWMDIV_2;  //    configure for /2 divider
  */

  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R & (~0x000E0000));   //    configure for /2 divider

  PWM0_0_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM0_0_GENB_R = (PWM_0_GENB_ACTCMPBD_ONE|PWM_0_GENB_ACTLOAD_ZERO);
  // PB7 goes low on LOAD
  // PB7 goes high on CMPB down
  PWM0_0_LOAD_R = (1/freqPWM) * freqCPU;            // 5) cycles needed to count down to 0
  PWM0_0_CMPB_R = (PWM0_0_LOAD_R * porcentagem)/100;              // 6) count value when output rises
  PWM0_0_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM0_ENABLE_R |= 0x00000002;          // enable PB7/M0PWM1
}
// change duty cycle of PB7
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
void servo2PWM_Duty(float porcentagem){
  PWM0_0_CMPB_R = (PWM0_0_LOAD_R * porcentagem)/100;             // 6) count value when output rises
}





// Output on PB4/M0PWM2
void servo3PWM_Init(float freqCPU,float freqPWM,float porcentagem){
  SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
  SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
  while((SYSCTL_PRGPIO_R&0x02) == 0){}; //wait for port enable
  GPIO_PORTB_AFSEL_R |= 0x10;           // enable alt funct on PB4
  GPIO_PORTB_PCTL_R &= ~GPIO_PCTL_PB4_M;     // configure PB6 as PWM2
  GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB4_M0PWM2;
  GPIO_PORTB_AMSEL_R &= ~0x10;          // disable analog functionality on PB4
  GPIO_PORTB_DEN_R |= 0x10;             // enable digital I/O on PB4
  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R & (~0x000E0000));   //    configure for /2 divider

  PWM0_1_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM0_1_GENA_R = 0xC8;                 // low on LOAD, high on CMPA down
  // PB6 goes low on LOAD
  // PB6 goes high on CMPA down
  PWM0_1_LOAD_R = (1/freqPWM) * freqCPU;            // 5) cycles needed to count down to 0
  PWM0_1_CMPA_R = (PWM0_1_LOAD_R * porcentagem)/100; // 6) count value when output rises
  PWM0_1_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM0_ENABLE_R |= 0x00000004;          // enable PB4/M0PWM2
}
// change duty cycle of PB4
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
void servo3PWM_Duty(float porcentagem){
  PWM0_1_CMPA_R = (PWM0_1_LOAD_R * porcentagem)/100;             // 6) count value when output rises
}

//pwm PB5
void servo4PWM_Init(float freqCPU,float freqPWM,float porcentagem){
  SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
  SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
  while((SYSCTL_PRGPIO_R&0x02) == 0){}; //wait for port enable
  GPIO_PORTB_AFSEL_R |= 0x20;           // enable alt funct on PB5
  GPIO_PORTB_PCTL_R &= ~GPIO_PCTL_PB5_M;     // configure PB5 as PWM3
  GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB5_M0PWM3;
  GPIO_PORTB_AMSEL_R &= ~0x20;          // disable analog functionality on PB5
  GPIO_PORTB_DEN_R |= 0x20;             // enable digital I/O on PB5
  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R & (~0x000E0000));   //    configure for /2 divider

  PWM0_1_CTL_R = 0;                     // 4) re-loading down-counting mode
  //PWM0_1_GENB_R = 0xC8;                 // low on LOAD, high on CMPA down
  PWM0_1_GENB_R = (PWM_1_GENB_ACTCMPBD_ONE|PWM_1_GENB_ACTLOAD_ZERO);
  // PB6 goes low on LOAD
  // PB6 goes high on CMPA down
  PWM0_1_LOAD_R = (1/freqPWM) * freqCPU;            // 5) cycles needed to count down to 0
  PWM0_1_CMPB_R = (PWM0_1_LOAD_R * porcentagem)/100;  // 6) count value when output rises
  PWM0_1_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM0_ENABLE_R |= 0x00000008;          // enable PB5/M0PWM3
}
// change duty cycle of PB4
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
void servo4PWM_Duty(float porcentagem)
{
	PWM0_1_CMPB_R = (PWM0_1_LOAD_R * porcentagem)/100;            // 6) count value when output rises
}


//pwm PE4
void servo5PWM_Init(float freqCPU,float freqPWM,float porcentagem){
  SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
  SYSCTL_RCGCGPIO_R |= 0x10;            // 2) activate port E
  while((SYSCTL_PRGPIO_R&0x10) == 0){}; //wait for port enable
  GPIO_PORTE_AFSEL_R |= 0x10;           // enable alt funct on PE4
  GPIO_PORTE_PCTL_R &= ~GPIO_PCTL_PE4_M;	// configure PE4 as PWM4
  GPIO_PORTE_PCTL_R |= GPIO_PCTL_PE4_M0PWM4;
  GPIO_PORTE_AMSEL_R &= ~0x10;          	// disable analog functionality on PE4
  GPIO_PORTE_DEN_R |= 0x10;             	// enable digital I/O on PE4
  SYSCTL_RCC_R = 0x00100000 |           // 3) use PWM divider
      (SYSCTL_RCC_R & (~0x000E0000));   //    configure for /2 divider

  PWM0_2_CTL_R = 0;                     	// 4) re-loading down-counting mode
  //PWM0_1_GENB_R = 0xC8;                 	// low on LOAD, high on CMPA down
  PWM0_2_GENA_R = 0xC8;
  // PB6 goes low on LOAD
  // PB6 goes high on CMPA down
  PWM0_2_LOAD_R = (1/freqPWM) * freqCPU;            			// 5) cycles needed to count down to 0
  PWM0_2_CMPA_R = (PWM0_2_LOAD_R * porcentagem)/100;  // 6) count value when output rises
  PWM0_2_CTL_R |= 0x00000001;           	// 7) start PWM0
  PWM0_ENABLE_R |= 1<<4;          	// enable PE4/M0PWM5
}
// change duty cycle of PE4
// duty is number of PWM clock cycles output is high  (2<=duty<=period-1)
void servo5PWM_Duty(float porcentagem)
{
	PWM0_2_CMPA_R = (PWM0_2_LOAD_R * porcentagem)/100; // 6) count value when output rises
}



