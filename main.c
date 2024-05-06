#include <stdio.h>
#include "defs.h"

int main(void) {
    struct student_t **students = NULL;
    int result = read_students_grades("students_grades.txt", &students);

    if(result == -2){
        printf("Couldn't open file");
        return 4;
    }else if(result == -3){
        printf("File corrupted");
        return 6;
    }else if(result){
        printf("Failed to allocate memory");
        return 8;
    }

    display_students_grades(students);
    free_students_grades(students);
    return 0;
}
