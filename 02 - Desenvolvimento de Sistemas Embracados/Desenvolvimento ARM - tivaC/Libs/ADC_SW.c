#include <stdint.h>
#include "ADC_SW.h"
#include "tm4c123gh6pm.h"
#include "sys_time.h"

void ADC0_InitSWTriggerSeq3(uint32_t channelNum, uint8_t MUXpos){
    volatile uint32_t delay;
  switch(channelNum){             // 1) activate clock
    case 0:
    case 1:
    case 2:
    case 3:
    case 8:
    case 9:                       //    these are on GPIO_PORTE
      SYSCTL_RCGCGPIO_R |= 0x10;
      while((SYSCTL_PRGPIO_R&0x10) != 0x10){};
      break;
    case 4:
    case 5:
    case 6:
    case 7:                       //    these are on GPIO_PORTD
      SYSCTL_RCGCGPIO_R |= 0x08;
      while((SYSCTL_PRGPIO_R&0x08) != 0x08){};
      break;
    case 10:
    case 11:                      //    these are on GPIO_PORTB
      SYSCTL_RCGCGPIO_R |= 0x02;
      while((SYSCTL_PRGPIO_R&0x02) != 0x02){};
      break;
    default: return;              //    0 to 11 are valid channels on the LM4F120/TM4C123
  }
  delay = SYSCTL_RCGCGPIO_R;      // extra time for clock to stabilize
  delay = SYSCTL_RCGCGPIO_R;
  switch(channelNum){
    case 0:                       //      Ain0 is on PE3
      GPIO_PORTE_DIR_R &= ~0x08;  // 3.0) make PE3 input
      GPIO_PORTE_AFSEL_R |= 0x08; // 4.0) enable alternate function on PE3
      GPIO_PORTE_DEN_R &= ~0x08;  // 5.0) disable digital I/O on PE3
      GPIO_PORTE_AMSEL_R |= 0x08; // 6.0) enable analog functionality on PE3
      break;
    case 1:                       //      Ain1 is on PE2
      GPIO_PORTE_DIR_R &= ~0x04;  // 3.1) make PE2 input
      GPIO_PORTE_AFSEL_R |= 0x04; // 4.1) enable alternate function on PE2
      GPIO_PORTE_DEN_R &= ~0x04;  // 5.1) disable digital I/O on PE2
      GPIO_PORTE_AMSEL_R |= 0x04; // 6.1) enable analog functionality on PE2
      break;
    case 2:                       //      Ain2 is on PE1
      GPIO_PORTE_DIR_R &= ~0x02;  // 3.2) make PE1 input
      GPIO_PORTE_AFSEL_R |= 0x02; // 4.2) enable alternate function on PE1
      GPIO_PORTE_DEN_R &= ~0x02;  // 5.2) disable digital I/O on PE1
      GPIO_PORTE_AMSEL_R |= 0x02; // 6.2) enable analog functionality on PE1
      break;
    case 3:                       //      Ain3 is on PE0
      GPIO_PORTE_DIR_R &= ~0x01;  // 3.3) make PE0 input
      GPIO_PORTE_AFSEL_R |= 0x01; // 4.3) enable alternate function on PE0
      GPIO_PORTE_DEN_R &= ~0x01;  // 5.3) disable digital I/O on PE0
      GPIO_PORTE_AMSEL_R |= 0x01; // 6.3) enable analog functionality on PE0
      break;
    case 4:                       //      Ain4 is on PD3
      GPIO_PORTD_DIR_R &= ~0x08;  // 3.4) make PD3 input
      GPIO_PORTD_AFSEL_R |= 0x08; // 4.4) enable alternate function on PD3
      GPIO_PORTD_DEN_R &= ~0x08;  // 5.4) disable digital I/O on PD3
      GPIO_PORTD_AMSEL_R |= 0x08; // 6.4) enable analog functionality on PD3
      break;
    case 5:                       //      Ain5 is on PD2
      GPIO_PORTD_DIR_R &= ~0x04;  // 3.5) make PD2 input
      GPIO_PORTD_AFSEL_R |= 0x04; // 4.5) enable alternate function on PD2
      GPIO_PORTD_DEN_R &= ~0x04;  // 5.5) disable digital I/O on PD2
      GPIO_PORTD_AMSEL_R |= 0x04; // 6.5) enable analog functionality on PD2
      break;
    case 6:                       //      Ain6 is on PD1
      GPIO_PORTD_DIR_R &= ~0x02;  // 3.6) make PD1 input
      GPIO_PORTD_AFSEL_R |= 0x02; // 4.6) enable alternate function on PD1
      GPIO_PORTD_DEN_R &= ~0x02;  // 5.6) disable digital I/O on PD1
      GPIO_PORTD_AMSEL_R |= 0x02; // 6.6) enable analog functionality on PD1
      break;
    case 7:                       //      Ain7 is on PD0
      GPIO_PORTD_DIR_R &= ~0x01;  // 3.7) make PD0 input
      GPIO_PORTD_AFSEL_R |= 0x01; // 4.7) enable alternate function on PD0
      GPIO_PORTD_DEN_R &= ~0x01;  // 5.7) disable digital I/O on PD0
      GPIO_PORTD_AMSEL_R |= 0x01; // 6.7) enable analog functionality on PD0
      break;
    case 8:                       //      Ain8 is on PE5
      GPIO_PORTE_DIR_R &= ~0x20;  // 3.8) make PE5 input
      GPIO_PORTE_AFSEL_R |= 0x20; // 4.8) enable alternate function on PE5
      GPIO_PORTE_DEN_R &= ~0x20;  // 5.8) disable digital I/O on PE5
      GPIO_PORTE_AMSEL_R |= 0x20; // 6.8) enable analog functionality on PE5
      break;
    case 9:                       //      Ain9 is on PE4
      GPIO_PORTE_DIR_R &= ~0x10;  // 3.9) make PE4 input
      GPIO_PORTE_AFSEL_R |= 0x10; // 4.9) enable alternate function on PE4
      GPIO_PORTE_DEN_R &= ~0x10;  // 5.9) disable digital I/O on PE4
      GPIO_PORTE_AMSEL_R |= 0x10; // 6.9) enable analog functionality on PE4
      break;
    case 10:                      //       Ain10 is on PB4
      GPIO_PORTB_DIR_R &= ~0x10;  // 3.10) make PB4 input
      GPIO_PORTB_AFSEL_R |= 0x10; // 4.10) enable alternate function on PB4
      GPIO_PORTB_DEN_R &= ~0x10;  // 5.10) disable digital I/O on PB4
      GPIO_PORTB_AMSEL_R |= 0x10; // 6.10) enable analog functionality on PB4
      break;
    case 11:                      //       Ain11 is on PB5
      GPIO_PORTB_DIR_R &= ~0x20;  // 3.11) make PB5 input
      GPIO_PORTB_AFSEL_R |= 0x20; // 4.11) enable alternate function on PB5
      GPIO_PORTB_DEN_R &= ~0x20;  // 5.11) disable digital I/O on PB5
      GPIO_PORTB_AMSEL_R |= 0x20; // 6.11) enable analog functionality on PB5
      break;
  }
  SYSCTL_RCGCADC_R |= 0x0001;   // 7) activate ADC0
//  while((SYSCTL_PRADC_R&0x0001) != 0x0001){};   // good code, but not yet implemented in simulator
  delay = SYSCTL_RCGCADC_R;         // extra time for clock to stabilize
  delay = SYSCTL_RCGCADC_R;         // extra time for clock to stabilize
  delay = SYSCTL_RCGCADC_R;         // extra time for clock to stabilize
  delay = SYSCTL_RCGCADC_R;
  ADC0_PC_R &= ~0xF;              // 9) clear max sample rate field
  ADC0_PC_R |= 0x1;               //    configure for 125K samples/sec
  ADC0_SSPRI_R = 0x3210;          // 10) Sequencer 3 is lowest priority
  ADC0_ACTSS_R &= ~0x0004;        // 11) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;         // 12) seq3 is software trigger
  //ADC0_SSMUX3_R &= ~0x000F;       // 13) clear SS3 field
  //ADC0_SSMUX2_R += channelNum;    //     set channel
  //ADC0_SSMUX2_R = 0x0089;


  if(MUXpos == 0)
  {
	  ADC0_SSMUX2_R |= channelNum;
  }
  if(MUXpos == 1)
  {
	  ADC0_SSMUX2_R  |=    channelNum << 4 ;
  }
  if(MUXpos == 2)
  {
	  ADC0_SSMUX2_R  |=  channelNum << 8 ;
  }
  if(MUXpos == 3)
  {
	  ADC0_SSMUX2_R  |=  channelNum << 12 ;
  }

  //ADC0_SSCTL3_R = 0x0006;         // 14) no TS0 D0, yes IE0 END0
  ADC0_SSCTL2_R = 0x6000;         // 14) no TS0 D0, yes IE3 END3
  ADC0_IM_R &= ~0x0004;           // 15) disable SS3 interrupts
  ADC0_ACTSS_R |= 0x0004;         // 16) enable sample sequencer 3
}


void ADC0_InSeq3(uint32_t data[4])
{
  ADC0_PSSI_R = 0x0004;            // 1) initiate SS3
  while((ADC0_RIS_R&0x04)==0){};   // 2) wait for conversion done

  SysTick_Wait_us(10);
  data[3] = ADC0_SSFIFO2_R&0xFFF;  // 3A) read 1 result
  data[2] = ADC0_SSFIFO2_R&0xFFF;  // 3B) read 2 result
  data[1] = ADC0_SSFIFO2_R&0xFFF;  // 3C) read 3 result
  data[0] = ADC0_SSFIFO2_R&0xFFF;  // 3D) read 4 result
  ADC0_ISC_R = 0x0004;             // 4) acknowledge completion
}

uint8_t ADC0_New_InSeq3()
{
    uint8_t read;
    ADC0_PSSI_R = 0x0004;            // 1) initiate SS3
    while((ADC0_RIS_R&0x04)==0){};   // 2) wait for conversion done

    SysTick_Wait_us(10);
    read = (ADC0_SSFIFO2_R & 0xFFF) >> 3;  // 3A) read 1 result
    ADC0_ISC_R = 0x0004;             // 4) acknowledge completion
    return read;
}
