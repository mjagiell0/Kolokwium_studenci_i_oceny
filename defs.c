#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_students_grades(struct student_t **students);
int read_students_grades(const char *filename, struct student_t ***students);
void display_students_grades(struct student_t **students);