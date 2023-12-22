#include "count_func.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Calculates the average grade for a given array of Student pointers.
 *
 * @param pStu A pointer to an array of Student pointers.
 * @param num The number of elements in the array.
 * @return The average grade as a floating-point value.
 */
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

/**
 * Combines two arrays of Student objects into a single array.
 *
 * @param Stu1 Pointer to the first array of Student objects.
 * @param Stu2 Pointer to the second array of Student objects.
 * @param n1   Number of elements in the first array.
 * @param n2   Number of elements in the second array.
 * @return     Pointer to the combined array of Student objects.
 */
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

/**
 * Splits the given array of students into multiple classes based on the provided class name.
 *
 * @param Stu The array of students to be split.
 * @param n The number of students in the array.
 * @param class The name of the class to split the students into.
 * @param n_class The number of students in class.
 * @return A pointer to the newly created array of students for the specified class.
 */
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

/**
 * Counts the number of students in a given class.
 *
 * @param Stu Pointer to an array of Student structures.
 * @param n Number of elements in the Stu array.
 * @param class Name of the class to count students from.
 * @return The number of students in the specified class.
 */
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
