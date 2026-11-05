#include <stdio.h>
#include <string.h>
#include "common.h"

void displayTimetable(const char fileName[], int sem)
{
    FILE *file;

    char line[100];
    char registeredCodes[MAX_REGISTERED_COURSES][10];

    Course semesterCourses[MAX_COURSES];
    Course selectedCourses[MAX_REGISTERED_COURSES];

    int registeredCount = 0;
    int selectedCount = 0;
    int courseCount;

    int start, end;
    char cell[10];

    // Open student file
    file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("\nError opening student file.\n");
        return;
    }

    // Skip student details (first line)
    fgets(line, sizeof(line), file);

    // Read registered course codes
    while (fgets(line, sizeof(line), file) != NULL &&
           registeredCount < MAX_REGISTERED_COURSES)
    {
        line[strcspn(line, "\r\n")] = '\0';

        if (strlen(line) > 0)
        {
            strcpy(registeredCodes[registeredCount], line);
            registeredCount++;
        }
    }

    fclose(file);

    if (registeredCount == 0)
    {
        printf("\nNo courses registered yet, so there is no timetable.\n");
        return;
    }

    // Generate semester course filename
    char courseFileName[40];
    sprintf(courseFileName, "semester%dcourses.txt", sem);

    // Load semester courses
    courseCount = loadCourses(courseFileName, semesterCourses);

    if (courseCount == 0)
    {
        printf("\nNo semester courses found.\n");
        return;
    }

    // Match registered course codes with semester courses
    for (int i = 0; i < registeredCount; i++)
    {
        for (int j = 0; j < courseCount; j++)
        {
            if (strcmp(registeredCodes[i], semesterCourses[j].course_code) == 0)
            {
                selectedCourses[selectedCount] = semesterCourses[j];
                selectedCount++;
                break;
            }
        }
    }

    if (selectedCount == 0)
    {
        printf("\nNo matching courses found.\n");
        return;
    }

    // Display timetable
    printf("\n===================== TIMETABLE =====================\n");

    printf("%-12s", "Time");

    for (int d = 0; d < 5; d++)
    {
        printf("%-9s", dayNames[d]);
    }

    printf("\n");

    // Generate 1-hour time slots from 08:00 to 17:00
    for (int slot = 8 * 60; slot < 17 * 60; slot += 60)
    {
        printf("%02d:00-%02d:00 ",
               slot / 60, (slot + 60) / 60);

        for (int d = 0; d < 5; d++)
        {
            strcpy(cell, "--");

            for (int i = 0; i < selectedCount; i++)
            {
                start = selectedCourses[i].start_hour * 60
                      + selectedCourses[i].start_minute;

                end = selectedCourses[i].end_hour * 60
                    + selectedCourses[i].end_minute;

                if (selectedCourses[i].days[d] == 1 &&
                    slot < end && slot + 60 > start)
                {
                    strcpy(cell, selectedCourses[i].course_code);
                }
            }

            printf("%-9s", cell);
        }

        printf("\n");
    }
}