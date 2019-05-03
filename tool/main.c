#include <stdio.h>
#include <afxres.h>
#include "../params.h"

void action(void) {
// Створення файл можливе тільки якщо файлу немає
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return;
    }
// Отримання значень параметрів від користувача
    float a, b, c, d;
    printf("a=");
    scanf("%f", &a);
    printf("b=");
    scanf("%f", &b);
    printf("c=");
    scanf("%f", &c);
    printf("d=");
    scanf("%f", &d);
// Зберігання параметрів розрахунку у файл
    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Can not open file for write.\n");
        return;
    }
    int success = fwrite(&a, sizeof(a), 1, file) == 1 &&
                  fwrite(&b, sizeof(b), 1, file) == 1 &&
                  fwrite(&c, sizeof(c), 1, file) == 1 &&
                  fwrite(&d, sizeof(d), 1, file) == 1;
    fclose(file);
    if (!success) {
        printf("Can not write a, b, c, d to file.\n");
        remove(filename);
    }
}


int main() {
// Створення семафору
    HANDLE sem = CreateSemaphore(NULL, 0, 3, semaphore_name);
    if (sem == NULL)
    {
        printf("Can not create semaphore.\n");
        return -1;
    }
    // Підготовка до початку роботи
    if (ReleaseSemaphore(sem, 1, NULL) == 0)
    {
        printf("Can not post semaphore.\n");
        CloseHandle(sem);
        return -1;
    }
    remove(filename);
    // Нескінченний цикл
    for(ever)
    {
        // Отримати дозвіл на запис у файл
        if (WaitForSingleObject(sem, INFINITE) != WAIT_OBJECT_0)
        {
            printf("Can not wait semaphore.\n");
            break;
        }
        // Виконати дію над файлом
        action();
        // Дозволити іншим процесам працювати з файлом
        if (ReleaseSemaphore(sem, 1, NULL) == 0)
        {
            printf("Can not post semaphore.\n");
            break;
        }
    }
    // Закриття семафору
    CloseHandle(sem);
    return 0;
}