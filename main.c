#include <stdio.h>
#include "common.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

void Readtext(char text[], int size)
{
    if (fgets(text, size, stdin) != NULL)
    {
        text[strcspn(text, "\n")] = '\0';
    }
}

void upperCase(char text[])
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        text[i] = toupper(text[i]);
    }
}

int isValid(char text[])
{

    if (strlen(text) != 8)
    {
        printf("\nMust be 8 characters long\n");
        return 0;
    }

    if (text[0] != '2' || (text[1] < '3' || text[1] > '6'))
    {
        printf("\nWrong batch year entered\n");
        return 0;
    }

    if (text[2] != 'K' || text[3] != '-')
    {
        printf("\nWrong format entered, must be in format like (2XK-XXXX)\n");
        return 0;
    }

    for (int i = 4; i < 8; i++)
    {
        if (!isdigit(text[i]))
        {
            printf("\nLast 4 digits must be numbers");
            return 0;
        }
    }
    return 1;
}

void displaymenu()
{
    printf("\n\n======================================================");
    printf("\n                  STUDENT DASHBOARD");
    printf("\n======================================================");

    printf("\n  [1] Display Available Courses");
    printf("\n  [2] Register a New Course");
    printf("\n  [3] View Personal Timetable");
    printf("\n  [4] Drop a Course");
    printf("\n  [5] Exit Portal");

    printf("\n======================================================");
}

int main()
{
    char code[10];
    printf("\n======================================================");
    printf("\n       UNIVERSITY COURSE REGISTRATION SYSTEM");
    printf("\n======================================================");
    printf("\n                  STUDENT PORTAL");
    printf("\n======================================================");

    printf("\n\n---------------- STUDENT INFORMATION ----------------");
    printf("\nNAME: ");
    char name[50];
    Readtext(name, sizeof(name));
    upperCase(name);
    char id[20];
    do
    {
        printf("\nSTUDENT ID: ");
        Readtext(id, sizeof(id));
        upperCase(id);
    } while (isValid(id) == 0);

    char std_fileName[60];
    sprintf(std_fileName, "%s_%s.txt", name, id);

    int sem = 0;
    int returnFile = stdFileExists(std_fileName);

    if (returnFile == 0)
    {
        printf("\n[+] NEW STUDENT PROFILE CREATED SUCCESSFULLY!");
        printf("\n[+] Welcome, %s!", name);

        do
        {
            printf("\nEnter Your Semester (1-8): ");
            scanf(" %d", &sem);

            if (sem <= 0 || sem > 8)
            {
                printf("\nInvalid Semester Input[!]");
            }
        } while (sem <= 0 || sem > 8);

        createStudentFile(std_fileName, name, id, sem);
    }
    else
    {
        printf("\n[+] WELCOME BACK, %s!", name);
        printf("\n[+] Existing Student Record Found.");
        printf("\n------------------------------------------------------");
        printf("\n             YOUR REGISTERED COURSES");
        printf("\n------------------------------------------------------\n\n");
        readRegisteredCourses(std_fileName);

        FILE *fp = fopen(std_fileName, "r");
        if (fp == NULL)
        {
            printf("\nError opening your file.\n");
            return 1;
        }
        fscanf(fp, "%*[^|]|%*[^|]|%d", &sem);
        fclose(fp);
    }

    Course semesterCourses[MAX_COURSES];
    char courseFile[30];
    sprintf(courseFile, "semester%dcourses.txt", sem);
    int semesterCount = loadCourses(courseFile, semesterCourses);

    // Fill in full details (days, times) for courses loaded from the file
    for (int i = 0; i < registerCourseCount; i++)
    {
        int index = findCourse(semesterCourses, semesterCount, registeredCourses[i].course_code);

        if (index != -1)
        {
            registeredCourses[i] = semesterCourses[index];
        }
    }

    while (1)
    {

        int choice;
        do
        {
            displaymenu();
            printf("\nEnter Choice : ");
            scanf("%d", &choice);
            if (choice <= 0 || choice > 5)
            {
                printf("\nInvalid Input[!]. Please Enter Again Correct Choice : ");
            }
        } while (choice <= 0 || choice > 5);

        switch (choice)
        {
        case 1:
            displayCourses(semesterCourses);
            break;
        case 2:
            if (registerCourseCount == MAX_REGISTERED_COURSES)
            {
                printf("You have already registered for 5 courses.\n");
            }
            else
            {

                while (registerCourseCount < MAX_REGISTERED_COURSES)
                {
                    displayCourses(semesterCourses);
                    printf("\nEnter Course Code (0 to exit): ");
                    scanf(" %9s", code);
                    if (strcmp(code, "0") == 0)
                    {
                        break;
                    }
                    upperCase(code);
                    registerCourse(semesterCourses, semesterCount, code, std_fileName);
                }
            }
            break;

        case 3:
            displayTimetable(std_fileName, sem);
            break;

        case 4:
            if (registerCourseCount == 0)
            {
                printf("\nYou have no registered courses to drop.\n");
            }
            else
            {
                printf("\nYour registered courses:\n");
                for (int i = 0; i < registerCourseCount; i++)
                {
                    printf("  %s - %s\n", registeredCourses[i].course_code, registeredCourses[i].course_title);
                }

                printf("\nEnter Course Code to drop: ");
                scanf(" %9s", code);
                upperCase(code);
                dropCourse(semesterCourses, semesterCount, code, std_fileName);
            }
            break;
        case 5:
            printf("\n\n======================================================");
            printf("\n             THANK YOU FOR USING OUR PORTAL");
            printf("\n======================================================");
            printf("\n                  SESSION ENDED");
            printf("\n======================================================\n");
            return 0;
            break;
        default:
            printf("\nInvalid Choice[!]");
            break;
        }
    }

    return 0;
}