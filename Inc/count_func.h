#ifndef COUNT_FUNC_H
#define COUNT_FUNC_H

#include "type_define.h"

float Count_grade(Student pStu[], int num);
Student *Combine(const Student *Stu1, const Student *Stu2, int n1, int n2);
Student *Split(const Student *Stu, int n, char *class, int n_class);
int Count_num(const Student *Stu, int n, char *class);

#endif