#include "file.h"

#include <stdio.h>
#include <stdlib.h>

// >0 success -1 error
int ReadStudentInfo(const char *filename, Student **pStudents)
{
    FILE *file = NULL;
    file = fopen(filename, "r");

    if (file == NULL)
    {
        // can't open file
        return -1;
    }

    int num_count = 0;
    char file_read_buf[64];

    // malloc
    *pStudents = (Student *)malloc(sizeof(Student) * num_count);

    // first reading, get num_count, check
    for (; num_count < 999999; num_count++)
    {
        if (feof(file))
        {
            // read finish
            break;
        }

        if (5 != fscanf(file, "%s %s %d %d %d",
                        (*pStudents)[0].name, (*pStudents)[0].id,
                        (*pStudents)[0].grade_ex, (*pStudents)[0].grade_hf,
                        (*pStudents)[0].grade_sum))
        {
            // struct error
            printf("Data struct error. At line %d\n", num_count + 1);
            return -1;
        }

        if ((*pStudents)[0].grade_ex < 0 || (*pStudents)[0].grade_ex > 100 ||
            (*pStudents)[0].grade_hf < 0 || (*pStudents)[0].grade_hf > 100 ||
            (*pStudents)[0].grade_sum < 0 || (*pStudents)[0].grade_sum > 100)
        {
            // beyound normal range
            printf("Data out of range. At line %d\n", num_count + 1);
            return -1;
        }
    }

    // realloc
    *pStudents = (Student *)realloc(*pStudents, sizeof(Student) * num_count);

    // second reading, get value
    for (int i = 0; i < num_count; i++)
    {
        fscanf(file, "%s %s %d %d %d",
               (*pStudents)[i].name, (*pStudents)[i].id,
               (*pStudents)[i].grade_ex, (*pStudents)[i].grade_hf,
               (*pStudents)[i].grade_sum);
    }

    return num_count;
}