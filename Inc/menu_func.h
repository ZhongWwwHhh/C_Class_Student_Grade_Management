#ifndef MENU_FUNC_H
#define MENU_FUNC_H

#include "type_define.h"

#include <stdint.h>

int menu_read_file(Student **Stu, uint32_t *Stu_num);

int menu_count_class(const Student *Stu, const uint32_t Stu_num);

int menu_count_all(const Student *Stu, const uint32_t Stu_num);

#endif