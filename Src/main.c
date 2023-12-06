#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "main.h"

#include "type_define.h"
#include "file.h"
#include "count_func.h"
#include "menu_func.h"

int main()
{
    Student *Student_Data;
    uint32_t Stu_num = 0;

    // title
    puts(CLOUR_ON "Student Performance Management System" CLOUR_OFF);
    puts("");

// menu
PRINT_MENU:
#define MENU_CHOICE_NUM 4
    const char *menu[MENU_CHOICE_NUM] = {"1: Read(add) file", "2: Count a class", "3: Count all", "0: quit"};
    for (int i = 0; i < MENU_CHOICE_NUM; i++)
    {
        puts(menu[i]);
    }

    // get func choose
    printf("Choose a num: ");
    int8_t choose = -1;
    if (1 != scanf_s("%d", &choose))
    {
        puts(ERROR_INPUT);
        goto PRINT_MENU;
    }

    switch (choose)
    {
    case 1:
        // read file
        int res = menu_read_file(&Student_Data, &Stu_num);
        // count data
        printf("average: %f, all data has been counted\n", Count_grade(&Student_Data, Stu_num));
        goto PRINT_MENU;
        break;

    case 2:
        // count a class
        menu_count_class(Student_Data, Stu_num);
        goto PRINT_MENU;
        break;

    case 3:
        // count all
        break;

    case 0:
        // quit
        goto QUIT;
        break;

    default:
        // error
        goto PRINT_MENU;
        break;
    }

// release memory and quit
QUIT:
    // free all malloc
    free(Student_Data);

    // say goodbye
    puts("Bye");

    return 0;
}