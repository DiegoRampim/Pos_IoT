#include <tm4c123gh6pm.h>
#include <inttypes.h>

int main(void) {
    //LED R -> PF1 /-/ LED G -> PF2 /-/ LED B -> PF3 /-/ SW1   -> PF4

    /* ATIVA플O DAS PORTAS
     * SYSCTL_RCGCGPIO_R
     * 0 -> DESLIGA
     * 1 -> LIGA
     */

    SYSCTL_RCGCGPIO_R |= 1 << 5;  //Ativando PORTF bit 5  / Decimal = 32 / Binario = 0b100000 / Hexa / Deslocamento = 1 << 5
                                  //"|" = OPERA플O LOGICA OU +

    GPIO_PORTF_DIR_R |=  1 << 1 | 1 << 2 | 1 << 3;      //CONFIGURA플O DOS PINOS ENTRADA - SAIDA (DIRE플O)
                                                        //0 -> ENTRADA - 1 -> SAIDA

    GPIO_PORTF_DEN_R |=  1 << 1 | 1 << 2 | 1 << 3;       //DEN = DIGITAL ENABLE - HABILITA PINO
                                                         //0 -> DESABILITA - 1 -> HABILITA

    while(1){

        int i;

        //OPERADOR XOR "^" - MUDA DE NIVEL

        GPIO_PORTF_DATA_R ^= 1 << 1;   //LIGA E DESLIGA O PINO - ACENDE E APAGA LED
                                        // 1 - LIGA  - 0 - DESLIGA

        for(i = 0; i < 2000000; i++){}

    }


	return 0;
}
