#ifndef COMMON_H
#define COMMON_H

#define MAX_COURSES 10
#define MAX_REGISTERED_COURSES 5

typedef struct
{
    char course_code[10];
    char course_title[60];
    int credit_hours;
    int available_seats;
    int days[5];
    int start_hour;
    int start_minute;
    int end_hour;
    int end_minute;
} Course;

extern Course coursesForSem1[MAX_COURSES];
extern Course coursesForSem2[MAX_COURSES];
extern Course coursesForSem3[MAX_COURSES];
extern Course coursesForSem4[MAX_COURSES];
int loadCourses(const char *filename, Course courses[]);
void displayCourses(Course courses[]);
#endif
