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

void createStudentFile(const char std_fileName[], char name[], char id[], int sem)
{
    FILE *file = fopen(std_fileName, "w");

    if (file == NULL)
    {
        printf("\nError creating File");
        return;
    }

    fprintf(file, "%s|%s|%d", name, id, sem);
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

    // (clash check will go here later)

    registeredCourses[registerCourseCount] = semesterCourses[index];
    registerCourseCount++;
    semesterCourses[index].available_seats--;

    saveRegisteredCourse(std_fileName, code);

    printf("Course registered successfully!\n");
    return 1;
}
