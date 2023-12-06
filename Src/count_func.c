#include "count_func.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// count everyone's grade and return average
float Count_grade(Student **pStu, int num)
{
    long grade_sum = 0;
    for (int i = 0; i < num; i++)
    {
        (*pStu)[i].grade_sum = (*pStu)[i].grade_ex + (*pStu)[i].grade_hf;
        grade_sum += (*pStu)[i].grade_sum;
    }
    return (float)grade_sum / (float)num;
}

// combine students from two data, retrun Student *Stu_combined
Student *Combine(const Student *Stu1, const Student *Stu2, int n1, int n2)
{
    // pointer to save combined data
    Student *Stu_combined;
    Stu_combined = (Student *)malloc(sizeof(Student) * (n1 + n2));

    // copy data into new pointer
    for (int i = 0; i < n1; i++)
    {
        Stu_combined[i] = Stu1[i];
    }
    for (int i = 0; i < n2; i++)
    {
        Stu_combined[n1 + i] = Stu2[i];
    }

    return Stu_combined;
}

// split students from same class
Student *Split(const Student *Stu, int n, char *class, int n_class)
{

    // pointer to save data of students who are in class
    Student *Stu_split;
    Stu_split = (Student *)malloc(sizeof(Student) * n_class);

    // copy data to new pointer
    int i = 0;
    for (; i < n; i++)
    {
        if (strncmp(Stu[i].id, class, 10) == 0)
        {
            *Stu_split = Stu[i];
            Stu_split++;
        }
    }
    Stu_split -= n_class;

    return Stu_split;
}

// number of students from same class in *Stu
int Count_num(const Student *Stu, int n, char *class)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (strncmp(Stu[i].id, class, 10) == 0)
        {
            count++;
        }
    }

    return count;
}
