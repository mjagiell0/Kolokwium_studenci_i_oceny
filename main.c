#include <stdio.h>
#include "defs.h"

int main(void) {
    struct student_t **students = NULL;
    read_students_grades("test.txt", &students);
    return 0;
}
