#include <stdio.h>
#include "common.h"
Course courses[MAX_COURSES];
Course coursesForSem2[MAX_COURSES];
Course coursesForSem3[MAX_COURSES];
Course coursesForSem4[MAX_COURSES];

int courseCountSem1 = 0;
int courseCountSem2 = 0;
int courseCountSem3 = 0;
int courseCountSem4 = 0;

int courseCount = 0;
int loadCourses(const char *fileName, Course courses[])
{
    FILE *file;

    file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Error: Could not open %s\n", fileName);
        return 0;
    }

    int courseCount = 0;

    while (courseCount < MAX_COURSES &&
           fscanf(file,
                  "%9[^|]|%59[^|]|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d\n",
                  courses[courseCount].course_code,
                  courses[courseCount].course_title,
                  &courses[courseCount].credit_hours,
                  &courses[courseCount].available_seats,
                  &courses[courseCount].days[0],
                  &courses[courseCount].days[1],
                  &courses[courseCount].days[2],
                  &courses[courseCount].days[3],
                  &courses[courseCount].days[4],
                  &courses[courseCount].start_hour,
                  &courses[courseCount].start_minute,
                  &courses[courseCount].end_hour,
                  &courses[courseCount].end_minute) == 13)
    {
        courseCount++;
    }

    fclose(file);

    return courseCount;
}

void displayCourses(Course courses[])
{
    for (int i = 0; i < courseCount; i++)
    {
        printf("\n");
        printf("\nCourse %d:", i + 1);
        printf("\nCourse Code: %s\n", courses[i].course_code);
        printf("Course Title: %s\n", courses[i].course_title);
        printf("Credit Hours: %d\n", courses[i].credit_hours);
        printf("Available Seats: %d\n", courses[i].available_seats);
        printf("\nDays             : ");
        printf("%s", courses[i].days[0] ? "Mon " : "");
        printf("%s", courses[i].days[1] ? "Tue " : "");
        printf("%s", courses[i].days[2] ? "Wed " : "");
        printf("%s", courses[i].days[3] ? "Thu " : "");
        printf("%s", courses[i].days[4] ? "Fri " : "");
        printf("Start Time: %d:%d\nEnd Time: %d:%d", courses[i].start_hour, courses[i].start_minute, courses[i].end_hour, courses[i].end_minute);
    }
}