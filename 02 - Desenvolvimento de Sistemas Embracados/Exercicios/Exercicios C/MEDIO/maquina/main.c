#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x[5] = {0, 0, 0, 0, 0};
    int y[5] = {0, 0, 0, 0, 0};
    int controle, aux;
    int achou = 0;

    for(controle = 0; controle <= 4; controle++){
        scanf("%d", &x[controle]);
    }

    for(controle = 0; controle <= 4; controle++){
        scanf("%d", &y[controle]);
    }

    for(controle = 0; controle <= 4; controle++){
        aux = x[controle] + y[controle];

        if(aux > 1){
            achou++;
        }
    }

    if(achou != 0){
        printf("N\n");
    }else{
        printf("Y\n");
    }



    return 0;
}
