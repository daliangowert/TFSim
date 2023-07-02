#include <stdio.h>


void inicializaMatriz(int n,int m, int mat[n][m]){
    int num = 0;
    for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j < m; j++,num++){
            mat[i][j] = num;
        }
    }
}


int somaMaior(int n,int m, int mat[n][m],int num){
    int saida = 0;
    for(int i = 0 ; i < n; i++){
        for (int j = 0 ; j < m; j++){
            if (mat[i][j] >= num){
                saida += mat[i][j];
            }
        }
    }
    return saida;
}

int main(void){
    int n = 6;
    int m = 6;
    int mat[n][m];
    inicializaMatriz(n,m,mat);
    printf("%d\n",somaMaior(n,m,mat,15));

    return 0;
}