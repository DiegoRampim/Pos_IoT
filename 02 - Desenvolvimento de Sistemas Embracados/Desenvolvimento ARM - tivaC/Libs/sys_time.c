#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "sys_time.h"

//define SysTick
#define NVIC_ST_CTRL_R          (*((volatile uint32_t *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile uint32_t *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile uint32_t *)0xE000E018))
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Counter load value

//define PLL
#define SYSDIV2 4
#define SYSCTL_RIS_PLLLRIS      0x00000040
#define SYSCTL_RCC_XTAL_M       0x000007C0
#define SYSCTL_RCC_XTAL_6MHZ    0x000002C0
#define SYSCTL_RCC_XTAL_8MHZ    0x00000380
#define SYSCTL_RCC_XTAL_16MHZ   0x00000540
#define SYSCTL_RCC2_USERCC2     0x80000000
#define SYSCTL_RCC2_DIV400      0x40000000
#define SYSCTL_RCC2_SYSDIV2_M   0x1F800000
#define SYSCTL_RCC2_SYSDIV2LSB  0x00400000
#define SYSCTL_RCC2_PWRDN2      0x00002000
#define SYSCTL_RCC2_BYPASS2     0x00000800
#define SYSCTL_RCC2_OSCSRC2_M   0x00000070
#define SYSCTL_RCC2_OSCSRC2_MO  0x00000000

#ifndef F_CPU
# define F_CPU 16
#endif

void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
                                        // enable SysTick with core clock
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
}

void SysTick_Wait_us(uint32_t delay){
	delay = delay * F_CPU;
	volatile uint32_t elapsedTime;
  uint32_t startTime = NVIC_ST_CURRENT_R;

  do{
    elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(elapsedTime <= delay);
}

void SysTick_Wait_ms(uint32_t delay){
  volatile uint32_t elapsedTime;
  uint32_t startTime = NVIC_ST_CURRENT_R;
  delay = delay * 1000 * F_CPU;
  do{
    elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(elapsedTime <= delay);
}



void PLL_Init(void){
  SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
  SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;
  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_16MHZ;
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;
  SYSCTL_RCC2_R += SYSCTL_RCC2_OSCSRC2_MO;
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
  SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) + (SYSDIV2<<22);
  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
  SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}
