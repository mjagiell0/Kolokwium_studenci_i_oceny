#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_students_grades(struct student_t **students);

int read_students_grades(const char *filename, struct student_t ***students) {
    if (!filename || !students)
        return -1;

    FILE *f = fopen(filename, "r");
    if (!f)
        return -2;

    struct student_t **arr = NULL;

    while (!feof(f)) {
        char name[21], last_name[41], course[43];
        int grade;

        if (fscanf(f, "%20[^|]|%40[^|]|%42[^|]|%d\n", name, last_name, course, &grade) != 4) {
            free_students_grades(arr);
            fclose(f);

            return -3;
        }

    }

    return 0;
}

void display_students_grades(struct student_t **students);

const struct student_t *search_student(const char *name, const char *last_name, const struct student_t **students) {
    if (!students)
        return NULL;

    for (int i = 0; *(students + i); ++i)
        if (!strcmp(name, (*(students + i))->name) && !strcmp(last_name, (*(students + i))->last_name))
            return *(students + i);

    return NULL;
}