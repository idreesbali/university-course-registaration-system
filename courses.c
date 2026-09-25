#include <stdio.h>
#include "common.h"

Course coursesForSem1[MAX_COURSES];
int courseCount = 0;
int loadSemester1Courses() {
    FILE *file;
    file = fopen("semester1courses.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open semester1courses.txt\n");
        return 0;
    }
    while (courseCount < MAX_COURSES &&
           fscanf(file,
                  "%9[^|]|%59[^|]|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d\n",
                  coursesForSem1[courseCount].course_code,
                  coursesForSem1[courseCount].course_title,
                  &coursesForSem1[courseCount].credit_hours,
                  &coursesForSem1[courseCount].available_seats,
                  &coursesForSem1[courseCount].days[0],
                  &coursesForSem1[courseCount].days[1],
                  &coursesForSem1[courseCount].days[2],
                  &coursesForSem1[courseCount].days[3],
                  &coursesForSem1[courseCount].days[4],
                  &coursesForSem1[courseCount].days[5],
                  &coursesForSem1[courseCount].days[6],
                  &coursesForSem1[courseCount].start_hour,
                  &coursesForSem1[courseCount].start_minute,
                  &coursesForSem1[courseCount].end_hour,
                  &coursesForSem1[courseCount].end_minute) == 15)
    {
        courseCount++;
    }
    fclose(file);
    return courseCount;
}

void displayCourses() {
    for(int i = 0; i < courseCount; i++) {
        printf("\n");
        printf("\nCourse %d:", i+1);
        printf("\nCourse Code: %s\n", coursesForSem1[i].course_code);
        printf("Course Title: %s\n", coursesForSem1[i].course_title);
        printf("Credit Hours: %d\n", coursesForSem1[i].credit_hours);
        printf("Available Seats: %d\n", coursesForSem1[i].available_seats);
        printf("Start Time: %d:%d\nEnd Time: %d:%d",coursesForSem1[i].start_hour,coursesForSem1[i].start_minute,coursesForSem1[i].end_hour,coursesForSem1[i].end_minute);
    }
}