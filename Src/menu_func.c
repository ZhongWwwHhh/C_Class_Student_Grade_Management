#include "menu_func.h"

#include "main.h"
#include "file.h"
#include "count_func.h"

#include <stdio.h>
#include <stdlib.h>
#include <io.h>

int menu_read_file(Student **Stu, uint32_t *Stu_num)
{
PRINT_MENU_READFILE:
    // get file path
    char path[256] = {0};
    puts(CLOUR_ON "Please input file or folder path(entire path): " CLOUR_OFF);
    scanf_s("%s", path, 255);

    // get data from a new file
    Student *Stu_temp;
    int res = ReadStudentInfo(path, &Stu_temp);

    if (0 > res)
    {
        // error
        puts(CLOUR_ON "CAN NOT OPEN FILE" CLOUR_OFF);
        goto PRINT_MENU_READFILE;
        return -1;
    }
    else if (0 < res)
    {
        // success
        // add new data

        Student *Stu_new = Combine(*Stu, Stu_temp, *Stu_num, res);
        free(Stu_temp);
        Stu_temp = NULL;
        if (NULL != *Stu)
        {
            free(*Stu);
            *Stu = NULL;
        }
        *Stu = Stu_new;
        // add stu num
        *Stu_num += res;

        printf("Read %s success, %d line", path, res);
        1 == res ? puts("") : puts("s");

        return 0;
    }
}