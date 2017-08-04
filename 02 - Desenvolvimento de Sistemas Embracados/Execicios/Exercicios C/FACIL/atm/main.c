#include <stdio.h>
#include <stdlib.h>

int main()
{
    float valorSolicitado = 0;
    float valorCaixa = 0;
    int sair = 1;
    int auxInt = 0;
    int notas100 = 0;
    int notas50  = 0;
    int notas20  = 0;
    int notas10  = 0;

    int final[4] = {0, 0, 0, 0};

    scanf("%d %d %d %d", &notas100, &notas50, &notas20, &notas10);
    fflush(stdin);

    do{
        scanf("%f", &valorSolicitado);
        fflush(stdin);



        if(valorSolicitado == 0){
            sair = 0;
        }else{

            valorCaixa = ((notas100*100)+(notas50*50)+(notas20*20)+(notas10*10));

             if((valorSolicitado/1) != valorSolicitado && valorSolicitado <= valorCaixa){
                valorSolicitado = 0;
             }

             auxInt = (valorSolicitado/100);

                if(auxInt <= notas100){

                    notas100 = notas100 - auxInt;

                    valorSolicitado = (valorSolicitado - (auxInt*100));
                    final[0] = auxInt;

                }else{
                    valorSolicitado = (valorSolicitado - (notas100*100));
                    final[0] = notas100;
                    notas100 = 0;
                }

                auxInt = (valorSolicitado/50);

                if(auxInt <= notas50 ){

                    notas50 = notas50 - auxInt;

                    valorSolicitado = (valorSolicitado - (auxInt*50));
                    final[1] = auxInt;

                }else{
                    valorSolicitado = (valorSolicitado - (notas50*50));
                    final[1] = notas50;
                    notas50 = 0;
                }

                auxInt = (valorSolicitado/20);

                if(auxInt <= notas20 ){

                    notas20 = notas20 - auxInt;

                    valorSolicitado = (valorSolicitado - (auxInt*20));
                    final[2] = auxInt;

                }else{
                    valorSolicitado = (valorSolicitado - (notas20*20));
                    final[2] = notas20;
                    notas20 = 0;
                }

                auxInt = (valorSolicitado/10);

                if(auxInt <= notas10 ){

                    notas10 = notas10 - auxInt;
                    valorSolicitado = (valorSolicitado - (auxInt*10));
                    final[3] = auxInt;

                }else{
                    valorSolicitado = (valorSolicitado - (notas10*10));
                    final[3] = notas10;
                    notas10 = 0;
                }

                if(valorSolicitado != 0){

                    notas100 = notas100 + final[0];
                    notas50  = notas50  + final[1];
                    notas20  = notas20  + final[2];
                    notas10  = notas10  + final[3];

                    printf("*\n");
                }else{
                    printf("%d %d %d %d \n", final[0], final[1], final[2], final[3]);
                }

        }




    }while(sair != 0);

    return 0;
}
