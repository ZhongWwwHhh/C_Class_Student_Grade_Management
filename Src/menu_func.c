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
        print_line(Stu_temp[i].name, Stu_temp[i].id, Stu_temp[i].grade_hf, Stu_temp[i].grade_ex, Stu_temp[i].grade_sum, 0, NULL);
    }
    printf("----------\n");

    // write result
    char filename[256] = {0};
    strcat(filename, class_name);
    strcat(filename, ".txt");
    if (0 > WriteClassInfo(Stu_temp, (uint32_t)class_num, class_name, average, filename, 1))
    {
        return -3;
    }

    // free Stu_temp
    free(Stu_temp);
    Stu_temp = NULL;
    return 0;
}

int menu_count_all(const Student *Stu, const uint32_t Stu_num)
{
    // get all class names
    char class_names[256][16] = {0};
    int8_t is_same = 0;
    uint8_t class_num_count = 0;
    for (uint32_t i = 0; i < Stu_num; i++)
    {
        for (uint16_t j = 0; j < 256; j++)
        {
            if (strncmp(Stu[i].id, class_names[j], 10) == 0)
            {
                is_same = 1;
            }
        }
        if (!is_same)
        {
            for (uint8_t k = 0; k < 16; k++)
            {
                class_names[class_num_count][k] = Stu[i].id[k];
            }
            class_num_count++;
            if (class_num_count == 255)
            {
                // print error
                puts(CLOUR_ON "TOO MANY CLASS" CLOUR_OFF);
                return -1;
            }
        }
    }

    // record average for each class
    float averages[256] = {0};

    for (uint8_t i = 0; i < class_num_count; i++)
    {
        // spilt one of class name
        // num of students in class
        char *class_name = class_names[i];
        int class_num = Count_num(Stu, Stu_num, class_name);

        // split data
        Student *Stu_temp = Split(Stu, Stu_num, class_name, class_num);

        // countdata
        averages[i] = Count_grade(&Stu_temp, class_num);

        // release
        free(Stu_temp);
        Stu_temp = NULL;
    }

    // print result
    printf("Result of %d class:\n----------\n", (int)class_num_count);
    puts("class_name\t\taverage");
    for (uint8_t i = 0; i < class_num_count; i++)
    {
        printf("%s\t\t%f\n", class_names[i], averages[i]);
    }
    puts("----------");

    // write result
    for (uint8_t i = 0; i < class_num_count; i++)
    {
        if (0 > WriteClassInfo(NULL, 0, class_names[i], averages[i], "all.txt", 0))
        {
            // write file error
            return -3;
        }
    }

    return 0;
}