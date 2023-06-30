#include <stdio.h>




int pot(int base,int expoente){
    int saida = 1;
    for (int i = 0; i < expoente; i++)
        saida *= base;
    return saida;
}


int main(void){
    int base = 2;
    int resultado = 1;
    int results[10] = {0};
    for(int i = 0; i < 10; i++){
        results[i] = pot(base,i);
    }
    for(int i = 0; i < 10; i++)
        printf("%d ",results[i]);
    printf("\n");
    return 0;
}