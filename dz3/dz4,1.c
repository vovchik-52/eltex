#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 100
#define MAX_SUBSTRING_LENGTH 50

char* findSubstring(const char* str, const char* substr) {
    char* result = strstr(str, substr);
    return result; // вернет NULL, если подстрока не найдена
}

int main() {
    char str[MAX_STRING_LENGTH];
    char substr[MAX_SUBSTRING_LENGTH];

    // Ввод строки
    printf("Введите строку: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0; // Удаляем символ новой строки

    // Ввод подстроки
    printf("Введите подстроку: ");
    fgets(substr, sizeof(substr), stdin);
    substr[strcspn(substr, "\n")] = 0; // Удаляем символ новой строки

    // Поиск подстроки
    char* result = findSubstring(str, substr);

    // Вывод результата
    if (result) {
        printf("Подстрока найдена: %s\n", result);
    } else {
        printf("Подстрока не найдена.\n");
    }

    return 0;
}
