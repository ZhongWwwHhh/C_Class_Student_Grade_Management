#include "file.h"

#include "main.h"

void print_line(const char *name, const char *id, const int grade_ex, const int grade_hf, const int grade_sum, const uint8_t is_file, FILE **file)
{
    if (!is_file)
    {
        printf("%s\t%13s %3d %3d %3d\n", name, id, grade_ex, grade_hf, grade_sum);
    }
    else
    {
        fprintf(*file, "%s\t%13s %3d %3d %3d\n", name, id, grade_ex, grade_hf, grade_sum);
    }
    return;
}

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
        print_line((*Stu)[i].name, (*Stu)[i].id, (*Stu)[i].grade_ex, (*Stu)[i].grade_hf, (*Stu)[i].grade_sum, 0, NULL);
    }

    // release file
    fclose(file);

    return num_count;
}

int WriteClassInfo(const Student *Stu, const uint32_t Stu_num, const char *class_name, const float average, const char *filename, int8_t need_detail)
{
    FILE *file = NULL;
    file = fopen(filename, "a");

    if (NULL == file)
    {
        // can't open file
        puts(CLOUR_ON "CAN'T OPEN FILE" CLOUR_OFF);
        return -1;
    }

    fprintf(file, "Result of class %s: ", class_name);

    if (need_detail)
    {
        fprintf(file, "\n----------\n");
        for (uint32_t i = 0; i < Stu_num; i++)
        {
            print_line(Stu[i].name, Stu[i].id, Stu[i].grade_hf, Stu[i].grade_ex, Stu[i].grade_sum, 1, &file);
        }
        fputs("----------\n", file);
    }

    fprintf(file, "average grade: %.4f", average);

    fputs("\n\n", file);

    fclose(file);

    return 0;
}