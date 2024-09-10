#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define XYSIZE 4

const char *positions[4] = {
    "ближняя справа", 
    "ближняя слева",
    "дальняя слева",
    "дальняя справа"};

int safe_str_to_int(const char *str, int *result) {
    char *endptr;
    long long int value;
    errno = 0;
    value = strtoll(str, &endptr, 10);
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN || endptr == str || *endptr != '\0') {
        return -1;
    }
    *result = (int)value;
    return 0;
}

int get_input(char *str, int size, int *result) {
    if (fgets(str, size, stdin) != NULL) {
        str[strcspn(str, "\n")] = 0;
        if (safe_str_to_int(str, result) == 0) {
            return 0;
        } else {
            printf("Ошибка: введенные данные некорректны.\n");
            return 1;
        }
    } else {
        printf("Ошибка при считывании данных.\n");
        return 2;
    }
}

int solve(int x, int y, int n) {
    int Xpos = ((n + XYSIZE - 1) / XYSIZE + y - 1) / y;
    int Ypos = (n + XYSIZE - 1) / XYSIZE - y * (Xpos - 1);
    int Npos = n % XYSIZE;
    if (Xpos > x) {
        printf("Квартиры с таким номером нет в доме, %d > %d\n", Xpos, x);
        return -1;
    }
    printf("Номер подъезда: %d\n", Xpos);
    printf("Номер этажа: %d\n", Ypos);
    printf("Положение на лестничной площадке: %s\n", positions[Npos]);

    return 0;
}

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    char input[256];
    int y, x, n;

    printf("Введите количество этажей: ");
    get_input(input, sizeof(input), &y);
    printf("Введите количество подъездов: ");
    get_input(input, sizeof(input), &x);
    printf("Введите номер квартиры: ");
    get_input(input, sizeof(input), &n);

    return solve(x, y, n);
}
