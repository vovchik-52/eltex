#include <stdio.h>
#include <stdlib.h>

int main() {
   int  n,i, j;
   float chek;
    int **matrix;

    printf("Введите размер квадратной матрицы:\n(Рекомендуеться вводить нечетные числа размерности)\n");
    if((!scanf("%f", &chek))||(chek!=(int)chek)||(chek <= 0)){
        printf("Нельзя\n");
        return 0;
    }
    n = (int)chek;
    matrix = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if(i >= n-j-1){
                matrix[i][j] = 0;
            }
            else{
                matrix[i][j] = 1;               
            }
            
        }
    }

    printf("Ваша матрица:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    free(matrix);
    

    return 0;
}