#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_students_grades(struct student_t **students) {
    if (!students)
        return;

    for (int i = 0; *(students + i); ++i) {
        free((*(students + i))->courses->grades);
        free((*(students + i))->courses);
        free((*(students + i)));
    }

    free(students);
}

int read_students_grades(const char *filename, struct student_t ***students) {
    if (!filename || !students)
        return -1;

    FILE *f = fopen(filename, "r");
    if (!f)
        return -2;

    struct student_t **arr = NULL;
    unsigned int student_count = 0;

    while (!feof(f)) {
        char name[21], last_name[41], course[43];
        int grade;

        if (fscanf(f, "%20[^|]|%40[^|]|%42[^|]|%d\n", name, last_name, course, &grade) != 4) {
            free_students_grades(arr);
            fclose(f);

            return -3;
        }

        struct student_t *student = (struct student_t *) search_student(name, last_name,
                                                                        (const struct student_t **) arr);
        if (!student) {
            student = calloc(1, sizeof(struct student_t));
            if (!student) {
                free_students_grades(arr);
                fclose(f);
                return -4;
            }

            strcpy(student->name, name);
            strcpy(student->last_name, last_name);
            student->number_of_courses = 1;

            student->courses = calloc(1, sizeof(struct course_grades_t));
            if (!student->courses) {
                free_students_grades(arr);
                free(student);
                fclose(f);
                return -4;
            }

            strcpy(student->courses->course, course);
            student->courses->number_of_grades = 1;

            student->courses->grades = calloc(1, sizeof(int));
            if (!student->courses->grades) {
                free_students_grades(arr);
                free(student->courses);
                free(student);
                fclose(f);
                return -4;
            }

            *student->courses->grades = grade;

            struct student_t **tmp = realloc(arr, (student_count + 2) * sizeof(struct student_t *));
            if (!tmp) {
                free_students_grades(arr);
                free(student->courses);
                free(student);
                fclose(f);
                return -4;
            }
            arr = tmp;

            *(arr + student_count) = student;
            student_count++;
            *(arr + student_count) = NULL;
        }

    }

    *students = arr;

    return 0;
}

void display_students_grades(struct student_t **students) {
    if (!students)
        return;

    for (int i = 0; *(students + i); ++i) {
        printf("%s %s\n", (*(students + i))->name, (*(students + i))->last_name);

        struct course_grades_t *courses = (*(students + i))->courses;

        for (int j = 0; j < (*(students + i))->number_of_courses; ++j) {
            printf("-%s:", (courses + j)->course);

            for (int k = 0; k < (courses + j)->number_of_grades; ++k)
                printf(" %d", *((courses + j)->grades + k));

            printf("\n");
        }
    }
}

const struct student_t *search_student(const char *name, const char *last_name, const struct student_t **students) {
    if (!students)
        return NULL;

    for (int i = 0; *(students + i); ++i)
        if (!strcmp(name, (*(students + i))->name) && !strcmp(last_name, (*(students + i))->last_name))
            return *(students + i);

    return NULL;
}

const struct course_grades_t *search_course(const char *course, const struct course_grades_t *courses, int N){
    if(!courses)
        return NULL;

    for (int i = 0; i < N; ++i)
        if(!strcmp(course,(courses + i)->course))
            return (courses + i);

    return NULL;
}