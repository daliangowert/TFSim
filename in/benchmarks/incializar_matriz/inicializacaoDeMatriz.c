#include <stdio.h>
#include <stdlib.h>




/***
 * so para ter uma ideia de como o codigo ficara em assembly
*/


int main(void){
    int n;
    int m;
    int mat[n][m];
    int i;
    int j;
    int k = 0;
    for (i = 0; i < n; i++){
        for(j = 0 ; j < m; j++){
            mat[i][j] = k;
        }
    }

}