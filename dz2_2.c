#include <stdio.h>
#include <stdlib.h>

int main() {
   int  n,i, j;
   float chek;
    printf("Введите размер массива: ");
    if((!scanf("%f", &chek))||(chek!=(int)chek)||(chek <= 0)){
        printf("Нельзя\n");
    } 
    n = (int)chek;
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i]=i+1;
    }
        for (int i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    int *reverb = (int *)malloc(n * sizeof(int));
       for (int i = 0; i < n; i++)
    {
        reverb[i]=arr[n-i-1];
    }
       for (int i = 0; i < n; i++)
    {
        printf("%d ",reverb[i]);
    }
    free(arr);
    free(reverb);

    return 0;
}