#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char c, d;
    char texto[255];
    int carac, x, n, tamanho;



    do{
        scanf("%d", &n);

        fflush(stdin);

        gets(texto);

       // printf("Recebido: %s", texto);

        if(texto[0] != 48){

            tamanho = strlen(texto);

            for(x= 0; x < tamanho; x++){

                carac = texto[x];

                if(carac >= 32 && carac <= 64){
                   printf("%c", texto[x]);

                }else{
                    if(carac < 91){
                    c = carac+n;
                    if(c > 90){
                        c = c - 26;
                    }
                    printf("%c", c);
                    }else{
                        c = (carac + n - 32);

                        if(c > 90){
                            c = c - 26;
                        }

                        printf("%c", c);
                    }
                }
            } // for
        }

        printf("\n");

    }while(texto[0] != 48);

    getch();

    return 0;
}
