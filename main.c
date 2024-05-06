#include <stdio.h>
#include "defs.h"

int main(void) {
    struct student_t **students = NULL;
    read_students_grades("test.txt", &students);
    display_students_grades(students);
    free_students_grades(students);
    return 0;
}
