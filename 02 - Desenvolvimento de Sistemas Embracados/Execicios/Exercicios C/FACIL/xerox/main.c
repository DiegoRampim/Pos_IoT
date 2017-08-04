#include <stdio.h>
#include <stdlib.h>

int main()
{

    long int copias;

    long int aux;

    float valorA = 0;
    float valorB = 0;
    float valorC = 0;

    float menorValor;

    char menor;

    int controle = 1;

    while(controle != 0){

        scanf("%d", &copias);

        if(copias == 0){
            controle = 0;
        }else{


    if(copias >= 1 && copias <= 1000000){

        valorA = (copias*0.09);

        valorB = (copias*0.10);


        if(copias > 50){
            valorC = (50*0.15);



            if(copias >= 101){
                valorC = valorC + (50 * 0.10);
                valorC = valorC + ((copias-100) * 0.06 );
            }else{

                valorC = valorC + ((copias-50) * 0.10);

            }

        }else{
            valorC = (copias * 0.15);
        }


        printf("%f - %f - %f\n", valorA, valorB, valorC);




        if(copias > 150){
            if(valorB <= valorC){
              printf("B\n");
            }else{
                printf("C\n");
            }
        }else{
            if(valorA <= valorB){
                    if(valorA <= valorC){
                        printf("A\n");
                    }else{
                        printf("C\n");
                    }

            }else{
                if(valorB <= valorC){
                    printf("B\n");
                }else{
                    printf("C\n");
                }
            }
        }

    }

        }

        valorA = 0;
        valorB = 0;
        valorC = 0;

    }


    return 0;
}
