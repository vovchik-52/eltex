#include <stdio.h>
#include <stdlib.h>

int main() {
   int  n,i, j, shet;
   float chek;
    int **matrix;

    printf("Введите размер квадратной матрицы: ");
    if((!scanf("%f", &chek))||(chek!=(int)chek)||(chek <= 0)){
        printf("ээээу! вводи нормально жи есть да?!\n");
        return 0;
    }
    n = (int)chek;
    matrix = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }
    shet=1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) 
            {
            matrix[i][j] = shet;
            shet++;
            
        }
    }

    printf("Ваша матрица:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d\t ", matrix[i][j]);
        }
        printf("\n");
    }

    free(matrix);
    

    return 0;
}