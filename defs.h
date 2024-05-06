#ifndef KOLOKWIUM_4_05_22_NA_3_DEFS_H
#define KOLOKWIUM_4_05_22_NA_3_DEFS_H
#include <stdio.h>

struct course_grades_t {
    char course[43];
    size_t number_of_grades;
    int* grades;
};

struct student_t {
    char name[21];
    char last_name[41];
    size_t number_of_courses;
    struct course_grades_t* courses;
};

void free_students_grades(struct student_t **students);
int read_students_grades(const char *filename, struct student_t ***students);
void display_students_grades(struct student_t **students);
const struct student_t *search_student(const char *name, const char *last_name, const struct student_t **students);
const struct course_grades_t *search_course(const char *course, const struct course_grades_t *courses, unsigned long long N);
#endif
