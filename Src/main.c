#include <stdio.h>

#include "file.h"
#include "count_func.h"

#define CLOUR_ON          "\033[41;37m"
#define CLOUR_OFF         "\033[0m"

int main()
{
    printf(CLOUR_ON"Student Performance Management System"CLOUR_OFF);
    
    return 0;
}