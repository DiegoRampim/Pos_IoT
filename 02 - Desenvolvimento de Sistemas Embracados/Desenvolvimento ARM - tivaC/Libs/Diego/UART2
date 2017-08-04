#include <stdint.h>
#include "UART.h"
#include <tm4c123gh6pm.h>

#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full -
                                            // Verifica a fila de transmição

#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
                                            // Verifica a fila de recepção

#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
                                            // Seta palavra de 8 bits - Habilta bit 5 e 6

#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
                                            // Habilita transmição por fila na UART

#define UART_CTL_UARTEN         0x00000001  // UART Enables
                                            // Habilita UART


//------------UART_Init------------
// Inicialização de  UART
// Calculo de velocidade da porta (CLOCK / (16 * VELOCIDADE))
//    Parte Inteira - IBRD
//    Resto Decimal - FBRD = (Resto * 64 + 0.5)

// Clock 16 MHz / 115200 - IBRD = 8  / FBRD = 44

// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void) {

  SYSCTL_RCGCUART_R |= 0x01;            // activate UART0
                                        // Habilita a UART0

  SYSCTL_RCGCGPIO_R |= 0x01;            // activate port A
                                        // Habilita Port A - UART0 PA0 - PA1

  while ((SYSCTL_PRGPIO_R & 0x01) == 0){}; // Verifica se a Port A está pronta

  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART

  UART0_IBRD_R = 43;
  UART0_FBRD_R = 26;
  	                                                 // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN); // Configurando a UART0 para 8 bits de dados
                                                     // Habilitando FIFO, fila de dados


  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART

  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
                                        // Habilita função especial dos pinos PA1-0
                                        // UART0

  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // Habilita os pinos PA1-0

    	  // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // Desabilitas as funções de porta analogica dos pinos PA1-0

}

//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
char UART_InChar(void) {

  while ((UART0_FR_R & UART_FR_RXFE) != 0);  //Verifica se a fila de dados não esta vazia

	return ((char) (UART0_DR_R & 0xFF));  // Pega os 8 bits e transforma em char
}

//------------UART_InString------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until <enter> is typed
//    or until max length of the string is reached.
// It echoes each character as it is inputted.
// If a backspace is inputted, the string is modified
//    and the backspace is echoed
// terminates the string with a null character
// uses busy-waiting synchronization on RDRF
// Input: pointer to empty buffer, size of buffer
// Output: Null terminated string
// -- Modified by Agustinus Darmawan + Mingjie Qiu --
void UART_InString(char *bufPt, uint16_t max) {
	int length = 0;
	char character;
	character = UART_InChar();
	while (character != CR && character != LF) {//adicionado tratamento de new line
		if (character == BS) {
			if (length) {
				bufPt--;
				length--;
				//UART_OutChar(BS);//estava imprimintdo aqui
			}
		} else if (length < max) {
			*bufPt = character;
			bufPt++;
			length++;
			//UART_OutChar(character);//estava imprimintdo aqui
		}
		character = UART_InChar();
	}
	*bufPt = 0;
}
