#include <stdio.h>
#include <string.h>
#include "common.h"

Course registeredCourses[MAX_REGISTERED_COURSES];
int registerCourseCount = 0;

int stdFileExists(const char fileName[])
{
    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        return 0;
    }

    fclose(file);
    return 1;
}

void createStudentFile(const char std_fileName[], char name[], char id[])
{
    FILE *file = fopen(std_fileName, "w");

    if (file == NULL)
    {
        printf("\nError creating File");
        return;
    }

    fprintf(file, "%s|%s|%d", name, id);
    fclose(file);
}

void readRegisteredCourses(const char fileName[])
{
    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        printf("\nError opening file");
        return;
    }
    else
    {
        int total_lines = 0;
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            total_lines++;
        }
        rewind(file);

        fgets(line, sizeof(line), file);

        for (int i = 0; i < total_lines - 1 &&
                        i < MAX_REGISTERED_COURSES;
             i++)
        {

            if (fscanf(file, "%9s", registeredCourses[i].course_code) == 1)
            {
                printf("Course CODE: %s\n",
                       registeredCourses[i].course_code);
                registerCourseCount++;
            }
        }
        fclose(file);
    }
}
int isAlreadyRegistered(const char code[])
{
    return findCourse(registeredCourses, registerCourseCount, code) != -1;
}
// Adds the course code at the end of the student's file
void saveRegisteredCourse(const char std_fileName[], const char code[])
{
    FILE *file = fopen(std_fileName, "a"); // "a" = add at the end, don't erase

    if (file == NULL)
    {
        printf("\nError saving course to file\n");
        return;
    }

    fprintf(file, "\n%s", code);
    fclose(file);
}
// Converts hours and minutes into total minutes (e.g. 9:30 -> 570)
int toMinutes(int hour, int minute)
{
    return hour * 60 + minute;
}

// Returns 1 if the two courses clash, 0 if they don't
int coursesClash(Course a, Course b)
{
    int shareDay = 0;

    for (int i = 0; i < 5; i++)
    {
        if (a.days[i] != 0 && b.days[i] != 0)
        {
            shareDay = 1;
        }
    }

    if (shareDay == 0)
    {
        return 0; // no common day, so no clash
    }

    int startA = toMinutes(a.start_hour, a.start_minute);
    int endA = toMinutes(a.end_hour, a.end_minute);
    int startB = toMinutes(b.start_hour, b.start_minute);
    int endB = toMinutes(b.end_hour, b.end_minute);

    // They overlap if each one starts before the other ends
    if (startA < endB && startB < endA)
    {
        return 1;
    }
    return 0;
}

// Checks a new course against all registered courses.
// Returns the index of the clashing course, or -1 if there is no clash
int findClash(Course newCourse)
{
    for (int i = 0; i < registerCourseCount; i++)
    {
        if (coursesClash(newCourse, registeredCourses[i]) == 1)
        {
            return i;
        }
    }
    return -1;
}

int registerCourse(Course semesterCourses[], int count, const char code[], const char std_fileName[])
{
    int index = findCourse(semesterCourses, count, code);

    if (index == -1)
    {
        printf("Course %s was not found in your semester. Try again.\n", code);
        return 0;
    }

    if (isAlreadyRegistered(code) == 1)
    {
        printf("You have already registered %s.\n", code);
        return 0;
    }

    if (semesterCourses[index].available_seats <= 0)
    {
        printf("Sorry, no seats are available in %s.\n", code);
        return 0;
    }

    int clashIndex = findClash(semesterCourses[index]);

    if (clashIndex != -1)
    {
        printf("Clash! %s overlaps with %s, which you already registered.\n",
               code, registeredCourses[clashIndex].course_code);
        return 0;
    }

    registeredCourses[registerCourseCount] = semesterCourses[index];
    registerCourseCount++;
    semesterCourses[index].available_seats--;

    saveRegisteredCourse(std_fileName, code);

    printf("Course registered successfully!\n");
    return 1;
}
