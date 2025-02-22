#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
};

int add(struct abonent *ptr, int count);
int dell(struct abonent *ptr, int count);
int find(struct abonent *ptr, int count);
int all(struct abonent *ptr, int count);

int main() {
    struct abonent ab[100];
    struct abonent *ptr = ab;

    int count = 0;
    int deistvie = 0;

    while (1) {
        printf("Введите действие:\n1 - добавление абонента\n2 - удаление абонента\n3 - поиск абонента\n4 - список абонентов\n5 - выйти\n");
        
        if (scanf("%d", &deistvie) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
            deistvie = 0; // сбрасываем  действия
        }

        switch (deistvie) {
            case 1:
                count = add(ptr, count); 
                break;

            case 2:
                count = dell(ptr, count); 
                break;

            case 3:
                find(ptr, count);
                break;

            case 4:
                all(ptr, count);
                break;

            case 5:
                return 0;

            default:
                printf("Некорректное действие. Попробуйте еще раз.\n");
                break;
        }
    }

    return 0;
}

int add(struct abonent *ptr, int count) {
    if (count >= 100) {
        printf("Список переполнен\n");
        return count;
    } else {
        printf("Введите имя Абонента (до 9 символов):\n");
        scanf("%9s", ptr[count].name);
        printf("Введите фамилию Абонента (до 9 символов):\n");
        scanf("%9s", ptr[count].second_name);
        printf("Введите телефон Абонента (до 9 символов):\n");
        scanf("%9s", ptr[count].tel);
        count++;
    }
    return count;
}

int all(struct abonent *ptr, int count) {
    for (int i = 0; i < count; i++) {
        printf("%s %s %s\n", ptr[i].name, ptr[i].second_name, ptr[i].tel);
    }
    return 0;
}

int find(struct abonent *ptr, int count)
{
    char poiskname[10]={0};
    printf("Введите имя для поиска\n");
    scanf("%s", &poiskname);
    for (int i=0; i<=count; i++)
    {
        if (strcmp(poiskname, ptr[i].name) == 0)
        {
            printf("%s %s %s\n", ptr[i].name, ptr[i].second_name, ptr[i].tel);
        }
    }


    return 0;
}

int dell(struct abonent *ptr,int count){
    int num;
    printf("Введите номер Абонента для удаления\n");
    if ((scanf("%d",&num)!=1)||(num>=100))
    {
        printf("Некоректный порядковый номер пользователя, ожидаеться диапазон чисел 0-99\n");
    }
    if (num >count) return printf("Элемента с таким номером еще не существует\n");
    memset(&ptr[num], 0, sizeof(ptr[num]));//занулили структуру!
    return 0;
}