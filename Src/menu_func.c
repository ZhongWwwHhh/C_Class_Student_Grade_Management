#include "menu_func.h"

#include "main.h"
#include "file.h"
#include "count_func.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

int menu_read_file(Student **Stu, uint32_t *Stu_num)
{
PRINT_MENU_READFILE:
    // get file path
    char path[256] = {0};
    puts(CLOUR_ON "Please input file path(entire path): " CLOUR_OFF);
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

int menu_count_class(const Student *Stu, const uint32_t Stu_num)
{
    // get class name
    char class_name[256] = {0};
    puts(CLOUR_ON "Please input class number(eg:2023010901): " CLOUR_OFF);
    scanf_s("%s", class_name, 255);

    for (int i = 0; i != 0; i++)
    {
        if ('0' > class_name[i] || '9' < class_name[i])
        {
            // input error
            puts(CLOUR_ON "INCORRECT CLASS NAME" CLOUR_OFF);
            return -1;
        };
    }

    // num of students in class
    int class_num = Count_num(Stu, Stu_num, class_name);
    if (class_num <= 0)
    {
        // input unexist class name
        puts(CLOUR_ON "CLASS NAME UNEXIST IN DATA" CLOUR_OFF);
        return -2;
    }

    // split data
    Student *Stu_temp = Split(Stu, Stu_num, class_name, class_num);

    // countdata
    float average = Count_grade(&Stu_temp, class_num);

    // print result
    printf("Result of class %s:\n----------\n", class_name);
    for (int i = 0; i < class_num; i++)
    {
        print_line(Stu_temp->name, Stu_temp->id, Stu_temp->grade_hf, Stu_temp->grade_ex, Stu_temp->grade_sum, 0, NULL);
    }
    printf("----------\n");

    // write result
    char filename[256] = {0};
    strcat(filename, class_name);
    strcat(filename, ".txt");
    WriteClassInfo(Stu_temp, (uint32_t)class_num, class_name, average, filename);

    // free Stu_temp
    free(Stu_temp);
    Stu_temp = NULL;
    return 0;
}