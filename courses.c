#include <stdio.h>
#include<string.h>
#include "common.h"
Course coursesForSem1[MAX_COURSES];
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
    courseCount = 0;

    file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("Error: Could not open %s\n", fileName);
        return 0;
    }

    while (courseCount < MAX_COURSES &&
           fscanf(file,
                  "%9[^|]|%59[^|]|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d\n",
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
    printf("\n");
    printf("+------+----------+----------------------------------+--------+-------+----------------+-------------+\n");
    printf("| No.  | Code     | Course Title                     | Credit | Seats | Days           | Time        |\n");
    printf("+------+----------+----------------------------------+--------+-------+----------------+-------------+\n");

    for (int i = 0; i < courseCount; i++)
    {
        char days[20] = "";

        if (courses[i].days[0]) strcat(days, "Mon ");
        if (courses[i].days[1]) strcat(days, "Tue ");
        if (courses[i].days[2]) strcat(days, "Wed ");
        if (courses[i].days[3]) strcat(days, "Thu ");
        if (courses[i].days[4]) strcat(days, "Fri ");

        printf("| %-4d | %-8s | %-32.32s | %-6d | %-5d | %-14s | %02d:%02d-%02d:%02d |\n",
               i + 1,
               courses[i].course_code,
               courses[i].course_title,
               courses[i].credit_hours,
               courses[i].available_seats,
               days,
               courses[i].start_hour,
               courses[i].start_minute,
               courses[i].end_hour,
               courses[i].end_minute);

        printf("+------+----------+----------------------------------+--------+-------+----------------+-------------+\n");
    }
}
