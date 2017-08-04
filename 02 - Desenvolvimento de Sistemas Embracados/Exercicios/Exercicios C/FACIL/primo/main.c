#include <stdio.h>
#include <stdlib.h>

int main()
{

    int num = 0;
    int x;
    int achou = 0;

    do{
        scanf("%d", &num);

        if(num != 0){

           if(num < 8){

            if(num == 2 || num == 3 || num == 5 || num == 7) {
                printf("1\n");
            }else{
                printf("0\n");
            }

           }else{

               for(x = 2; x <=7; x++){
                 if((num%x) == 0){
                    achou++;
                 }
               }

               if(achou != 0){
                    printf("0\n");
                    achou = 0;
               }else{
                    printf("1\n");
               }

            }
        }

    }while(num != 0);


    return 0;
}
