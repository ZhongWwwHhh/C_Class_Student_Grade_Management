#ifndef FILE_H
#define FILE_H

#include "type_define.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void print_line(const char *name, const char *id, const int grade_ex, const int grade_hf, const int grade_sum, const uint8_t is_file, FILE **file);

int ReadStudentInfo(const char *filename, Student **pStudents);

int WriteClassInfo(const Student *Stu, const uint32_t Stu_num, const char *class_name, const float average, const char *filename);

#endif
