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
extern Course coursesForSem5[MAX_COURSES];
extern Course coursesForSem6[MAX_COURSES];
extern Course coursesForSem7[MAX_COURSES];
extern Course coursesForSem8[MAX_COURSES];
extern Course registeredCourses[MAX_REGISTERED_COURSES];
int isAlreadyRegistered(const char code[]);
int registerCourse(Course semesterCourses[], int count, const char code[], const char std_fileName[]);
extern int registerCourseCount;
extern const char dayNames[5][4];

int loadCourses(const char *filename, Course courses[]);
void displayCourses(Course courses[]);
int stdFileExists(const char fileName[]);
void createStudentFile(const char std_fileName[], char name[], char id[]);
void readRegisteredCourses(const char fileName[]);
void displaymenu();
void displayTimetable(const char fileName[], int sem);
int findCourse(Course courses[], int count, const char code[]);

#endif
