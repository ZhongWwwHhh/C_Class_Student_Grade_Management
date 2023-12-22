#include "file.h"

#include "main.h"

/**
 * Prints a line of student information.
 *
 * @param name The name of the student.
 * @param id The ID of the student.
 * @param grade_ex The grade of the student in the experiment.
 * @param grade_hf The grade of the student in the half exam.
 * @param grade_sum The total grade of the student.
 * @param is_file Flag indicating whether to print to a file.
 * @param file Pointer to the file to print to (if is_file is true).
 */
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

/**
 * @brief Reads student information from a file.
 *
 * This function reads student information from the specified file and stores it in the `Stu` parameter.
 *
 * @param filename The name of the file to read from.
 * @param Stu A pointer to a pointer to the `Student` structure where the student information will be stored.
 * @return Returns > 0 if the operation is successful, otherwise returns a less-zero value.
 */
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
        int res = fscanf_s(file, "%s %s %d %d %d", (*Stu)->name, sizeof((*Stu)->name), (*Stu)->id, sizeof((*Stu)->id), &(*Stu)->grade_hf, &(*Stu)->grade_ex, &(*Stu)->grade_sum);

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
        fscanf_s(file, "%s %s %d %d %d",
                 (*Stu)[i].name, sizeof((*Stu)[i].name),
                 (*Stu)[i].id, sizeof((*Stu)[i].id),
                 &(*Stu)[i].grade_ex, &(*Stu)[i].grade_hf,
                 &(*Stu)[i].grade_sum);
        print_line((*Stu)[i].name, (*Stu)[i].id, (*Stu)[i].grade_ex, (*Stu)[i].grade_hf, (*Stu)[i].grade_sum, 0, NULL);
    }

    // release file
    fclose(file);

    return num_count;
}

/**
 * Writes the class information to a file.
 *
 * This function takes in the student information, class name, average grade,
 * filename, and a flag indicating whether detailed information is needed.
 * It writes the class information to the specified file.
 *
 * @param Stu Pointer to an array of Student structures containing student information.
 * @param Stu_num Number of students in the class.
 * @param class_name Name of the class.
 * @param average Average grade of the class.
 * @param filename Name of the file to write the class information to.
 * @param need_detail Flag indicating whether detailed information is needed (1 for yes, 0 for no).
 * @return Returns 0 on success, -1 on failure.
 */
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

    fprintf(file, "Result of class %.10s: ", class_name);

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