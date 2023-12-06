#include "file.h"

#include "main.h"

#include <stdio.h>
#include <stdlib.h>

// read a file, return > 0 success means count of line / return < 0 means fail with reason output
int ReadStudentInfo(const char *filename, Student **Stu)
{
    FILE *file = NULL;
    file = fopen(filename, "r");

    if (file == NULL)
    {
        // can't open file
        puts(CLOUR_ON "CAN'T OPEN" CLOUR_OFF);
        return -1;
    }

    int num_count = 0;
    char file_read_buf[64];

    // malloc
    *Stu = (Student *)malloc(sizeof(Student));

    // first reading, get num_count, check
    for (; num_count < 10240; num_count++)
    {
        int res = fscanf(file, "%s %s %d %d %d", (*Stu)->name, (*Stu)->id, &(*Stu)->grade_hf, &(*Stu)->grade_ex, &(*Stu)->grade_sum);

        // imnormal line
        if (5 != res)
        {
            if (EOF == res)
            {
                // read finish
                break;
            }
            else
            {
                // struct error
                printf(CLOUR_ON "Data struct error. At line %d\n" CLOUR_OFF, num_count + 1);
                return -2;
            }
        }

        // beyound normal range
        if ((*Stu)[0].grade_ex < 0 || (*Stu)[0].grade_ex > 100 ||
            (*Stu)[0].grade_hf < 0 || (*Stu)[0].grade_hf > 100 ||
            (*Stu)[0].grade_sum < 0 || (*Stu)[0].grade_sum > 100)
        {
            printf(CLOUR_ON "Data out of range. At line %d\n" CLOUR_OFF, num_count + 1);
            return -3;
        }

        // too many data
        if (num_count > 8192)
        {
            puts(CLOUR_ON "FILE TOO LARGE" CLOUR_OFF);
            return -4;
        }
    }

    // remalloc
    free(*Stu);
    *Stu = (Student *)malloc(sizeof(Student) * num_count);

    // back to file header
    rewind(file);

    // second reading, get value
    for (int i = 0; i < num_count; i++)
    {
        fscanf(file, "%s %s %d %d %d",
               (*Stu)[i].name, (*Stu)[i].id,
               &(*Stu)[i].grade_ex, &(*Stu)[i].grade_hf,
               &(*Stu)[i].grade_sum);
        printf("%s %s %d %d %d\n", (*Stu)[i].name, (*Stu)[i].id, (*Stu)[i].grade_ex, (*Stu)[i].grade_hf, (*Stu)[i].grade_sum);
    }

    // release file
    fclose(file);

    return num_count;
}