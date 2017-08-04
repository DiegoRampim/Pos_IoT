
#include <tm4c123gh6pm.h>
#include <inttypes.h>

int x = 0;

void TrataInt(){

    if(x){
        x = 0;
    }else{
        x = 1;
    }

    //GPIO_PORTF_ICR_R - INFORMA QUE A INTERRUP플O FOI TRATADA, SETA BIT REFERENTE A INTERRUP플O
    GPIO_PORTF_ICR_R = 1 << 4;

}

int main(void) {

    //LED R -> PF1 /-/ LED G -> PF2 /-/ LED B -> PF3 /-/ SW1   -> PF4

    /* ATIVA플O DAS PORTAS
     * SYSCTL_RCGCGPIO_R
     * 0 -> DESLIGA
     * 1 -> LIGA
     */

    //SYSCTL_RCGCGPIO_R - Ativando PORTF bit 5  / Decimal = 32 / Binario = 0b100000 / Hexa / Deslocamento = 1 << 5
    //"|" = OPERA플O LOGICA OU +
    SYSCTL_RCGCGPIO_R |= 1 << 5;

    //NVIC_EN0_R - CONTROLA INTERUP합ES / BIT 30 - INTERRUP합ES PORTF
    NVIC_EN0_R = 1 << 30;

    //GPIO_PORTF_IBE_R - SELECIONA O TIPO DE INTERRUP플O - INTERRUP합ES EM AMBAS AS BORDAS DO PINO 4 DA PORTA F
    GPIO_PORTF_IBE_R = 1 << 4;

    //GPIO_PORTF_IM_R - ATIVA INTERRUP플O NO PINO 4 PORTA F
    GPIO_PORTF_IM_R = 1 << 4;


    //GPIO_PORTF_DIR_R - CONFIGURA플O DOS PINOS ENTRADA - SAIDA (DIRE플O)
    //0 -> ENTRADA - 1 -> SAIDA
    GPIO_PORTF_DIR_R |=  1 << 1 | 1 << 2 | 1 << 3;

    //GPIO_PORTF_PUR_R - REGISTRADOR DE PULL UP  1 - HABILITA
    GPIO_PORTF_PUR_R |= 1 << 4;

    //GPIO_PORTF_DEN_R - DEN = DIGITAL ENABLE - HABILITA PINO
    //0 -> DESABILITA - 1 -> HABILITA
    GPIO_PORTF_DEN_R |=  1 << 1 | 1 << 2 | 1 << 3 | 1 << 4;

    while(1){

        int i, t;


        //GPIO_PORTF_DATA_R - LIGA E DESLIGA O PINO - ACENDE E APAGA LED
        // 1 - LIGA  - 0 - DESLIGA - OPERADOR XOR "^" - MUDA DE NIVEL
        //GPIO_PORTF_DATA_R ^= 1 << 1;


        if(x){

            for(i = 1; i <= 3; i++){
                GPIO_PORTF_DATA_R ^= 1 << i;
                for(t = 0; t < 2000000; t++){}
                GPIO_PORTF_DATA_R ^= 1 << i;
                for(t = 0; t < 2000000; t++){}
            }
        }else{

            for(i = 3; i >= 1; i--){
                GPIO_PORTF_DATA_R ^= 1 << i;
                for(t = 0; t < 2000000; t++){}
                GPIO_PORTF_DATA_R ^= 1 << i;
                for(t = 0; t < 2000000; t++){}
            }


        }

    }


    return 0;
}
