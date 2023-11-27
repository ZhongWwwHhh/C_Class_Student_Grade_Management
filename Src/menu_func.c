#include "menu_func.h"

#include "main.h"
#include "file.h"
#include "count_func.h"

#include <stdio.h>
#include <io.h>

int menu_read_file(Student *Stu)
{
PRINT_MENU_READFILE:
    // get file path
    char path[255] = {0};
    puts(CLOUR_ON "Please input file or folder path(entire path): " CLOUR_OFF);
    if (1 != scanf_s("$s", path, 254))
    {
        puts(ERROR_INPUT);
        goto PRINT_MENU_READFILE;
        return -1;
    }

    int res = ReadStudentInfo(path, Stu);

    if (-1 == res)
    {
        puts(CLOUR_ON "CAN NOT OPEN FILE" CLOUR_OFF);
        goto PRINT_MENU_READFILE;
        return -2;
    }
    else if (0 < res)
    {
        printf("Read %s success\n", path);

        int average = Count_grade(Stu, res);
        printf("Average: %d", average);
        return 0;
    }
}