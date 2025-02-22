#include <stdio.h>
#include <stdlib.h>

int main() {
   int  chislo, bity3;
   float chek1, chek2;

    printf("Введите целое положительное число: ");
    if((!scanf("%f", &chek1))||(chek1!=(int)chek1)||(chek1 <= 0)){
        printf("Неверный ввод\n");
        return 0;
    }
    chislo = (int)chek1;
    printf("Введите значение, на которое хотите поменять третий байт: ");
    if((!scanf("%f", &chek2))||(chek2!=(int)chek2)||(chek2 <= 0)){
        printf("Неверный ввод\n");
        return 0;
    }
    bity3 = (int)chek2;
    char *ptr;
    ptr = (char*)&chislo;
    ptr+=2;
    *ptr = (char)bity3;
    printf("Измененное число: %d\n", chislo);

    return 0;
}