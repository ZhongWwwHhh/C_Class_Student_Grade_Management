#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "main.h"

#include "type_define.h"
#include "file.h"
#include "count_func.h"
#include "menu_func.h"

Student **Student_Data;

int main()
{
    // malloc
    Student_Data = (Student **)malloc(sizeof(Student *));

    // title
    puts(CLOUR_ON "Student Performance Management System" CLOUR_OFF);
    puts("");

// menu
PRINT_MENU:
    const char *menu[3] = {"1: Read file", "2: Count a class", "3: Count all"};
    for (int i = 0; i < 3; i++)
    {
        puts(menu[i]);
    }

    // get func choose
    puts(CLOUR_ON "Choose a num: " CLOUR_OFF);
    int8_t choose = -1;
    if (1 != scanf_s("%d", &choose))
    {
        puts(ERROR_INPUT);
        goto PRINT_MENU;
    }

    switch (choose)
    {
    case 1:
        int res = menu_read_file(Student_Data);
        break;

    case 2:
        break;

    case 3:
        break;

    default:
        goto PRINT_MENU;
        break;
    }

    // free all malloc
    free(*Student_Data);
    free(Student_Data);

    return 0;
}