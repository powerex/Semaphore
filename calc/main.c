#include <stdio.h>
#include <afxres.h>
#include<time.h>
#include <float.h>
#include "../params.h"

void action(void) {
// Відкриття файлу
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
// Завантаження значень параметрів розрахунку з файлу
        float a, b, c, d;
        int success = fread(&a, sizeof(a), 1, file) == 1 &&
                      fread(&b, sizeof(b), 1, file) == 1 &&
                      fread(&c, sizeof(c), 1, file) == 1 &&
                      fread(&d, sizeof(d), 1, file) == 1;
        fclose(file);
        remove(filename);
// Виконання розрахунку
        if (success)
            printf("(a+b)/(c+d)=(%f+%f)/(%f+%f)=%f\n", a, b, c, d, (a + b) / (c + d));
        else
            printf("Can not read a, b, c, d from file.\n");
        fflush(stdout);
    }
}

int main() {
    double min_time = DBL_MAX;
// Створення семафору
    HANDLE sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, semaphore_name);
    if (sem == NULL) {
        printf("Can not create semaphore.\n");
        return -1;
    }
// Нескінченний цикл
    for(ever) {
        double time_spent = 0.0;
// Отримати дозвіл на запис у файл
        if (WaitForSingleObject(sem, INFINITE) != WAIT_OBJECT_0) {
            printf("Can not wait semaphore.\n");
            break;
        }
// Виконати дію над файлом
        clock_t begin = clock();
        action();
        clock_t end = clock();
// Дозволити іншим процесам працювати з файлом
        if (ReleaseSemaphore(sem, 1, NULL) == 0) {
            printf("Can not post semaphore.\n");
            break;
        }
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        if (time_spent < min_time)
            min_time = time_spent;
        printf("Current time elpased is %f seconds\nMinimum time elapsed is %f seconds\n", time_spent, min_time);
    }
// Закриття семафору
    CloseHandle(sem);
    return 0;

}