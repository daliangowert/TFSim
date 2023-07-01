#include <stdio.h>




int main(void){

    int n = 6;
    int mat[n][n];
    int i, j, num = 0;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
            mat[i][j] = 0;
        }
    }

    /**
     * no caso a matriz eh inicializada antes da execucao do programa
     * 
    */


   for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j <= i; j++){
            mat[i][j] = num;
            num++;
        }
   }




    return 0;


}