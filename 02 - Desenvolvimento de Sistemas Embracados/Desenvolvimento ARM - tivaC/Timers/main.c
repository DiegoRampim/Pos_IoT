#include <tm4c123gh6pm.h>
#include <inttypes.h>

int jogo[10] = {1, 2, 3, 1, 2, 3, 1, 2, 3};
int resposta[10];
int pos = 0;
int confere = 0;
int controleDelay = 1;

void trataST(){
    NVIC_ST_CTRL_R = 0 | NVIC_ST_CTRL_INTEN;
    controleDelay = 0;
}

void delay(int tempo){

    controleDelay = 1;

    //4000000  = 1000
    //  x      = tempo
    // tempo * 4000 = 1000 * x

    int var = ((tempo * 4000000)/1000);

    NVIC_ST_RELOAD_R = 4000000;
    NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE | NVIC_ST_CTRL_INTEN;

    // __asm("WFI");

    while(controleDelay){};
}

void acende(int cor){

    if(cor == 1){
        GPIO_PORTF_DATA_R = 1 << 1;
    }else{
       if(cor == 2){
           GPIO_PORTF_DATA_R = 1 << 2;
       }else{
           GPIO_PORTF_DATA_R = 1 << 3;
       }
    }
}


void apaga(int cor){

    if(cor == 1){
        GPIO_PORTF_DATA_R = 0 << 1;
    }else{
       if(cor == 2){
           GPIO_PORTF_DATA_R = 0 << 2;
       }else{
           GPIO_PORTF_DATA_R = 0 << 3;
       }
    }
}

void trataJogador(){

    int y;
    int pino = GPIO_PORTD_RIS_R;

    // Limpar interrupção  ICR

    GPIO_PORTD_ICR_R = pino;

    if(jogo[confere] == (pino+1)){
            //continua
           confere++;
        }else{
            //perdeu - fim do jogo - acende vermelho

            acende(1);
            delay(4000);
            apaga(1);

            pos = 0;
            //zerar interrupções

        }


    if(confere >= pos){
     //nova rodada
        pos++;

        if(pos > 10){
            //Ganhou - Fim do jogo - acende azul
            acende(2);
            delay(4000);
            apaga(2);

            pos = 0;
        }

    }

    GPIO_PORTD_ICR_R = pino;
}


int main(void) {
	
    /*
     * PortD    0          1       2
     * PortF    1          2       3
     *          VERMELHO   AZUL    VERDE
     */

    SYSCTL_RCGCGPIO_R = 1 << 5 | 1 << 3;


    GPIO_PORTF_DIR_R = 1 << 1 | 1 << 2 | 1 << 3;
    GPIO_PORTF_DEN_R = 1 << 1 | 1 << 2 | 1 << 3;
    GPIO_PORTD_PUR_R = 0b111;
    GPIO_PORTD_DEN_R = 0b111; // 1 | 1 << 1 | 1 << 2



    //habilita int no portD
    NVIC_EN0_R = 1 << 3;

    //habilita int de ambas as bordas no pino do botão
    //GPIO_PORTF_IBE_R = 1 << 4;

    //habilita bordas no pino do botão | 0 com borda | 1 sinal continuo
    GPIO_PORTF_IS_R = 0b000;

    //habilita subida ou descida no pino do botão | 0 descida | 1 subida
    GPIO_PORTD_IEV_R = 0b000;

    GPIO_PORTD_IM_R = 0b111;


  //  NVIC_ST_RELOAD_R = 4000000;   //QUANTIDADE DE TICS(CICLO DE CLOCK) PARA O TEMPO ESTURAR TIMER  ( VALOR / 4 = 16.000.000 )

  //  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE | NVIC_ST_CTRL_INTEN;  // HABILITA SYSTIC E INTERRUPÇÃO

  //  GPIO_PORTF_DATA_R ^= 1 << 1;



    while(1){

        int x, corAtual;

        for(x = 0; x <= pos; x++){

            corAtual = jogo[x];

            acende(corAtual);

            delay(1000);


            apaga(corAtual);
        }

        __asm("WFI");

    }

	return 0;
}
