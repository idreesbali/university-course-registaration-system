#include <stdio.h>
#include "common.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void Readtext(char text[], int size)
{
    if (fgets(text, size, stdin) != NULL)
    {
        text[strcspn(text, "\n")] = '\0';
    }
}

int upperCase(char text[])
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
    printf("\n#####################################################");
    printf("\n\tCOURSE REGISTRATION AND TIMETABLE MENU");
    printf("\n#####################################################");

    printf("\n 1. Display Semester Available Courses");
    printf("\n 2. Register a new Course");
    printf("\n 3. View TimeTable");
    printf("\n 4. Exit");
}

int main()
{
    char code[10];
    printf("NAME: ");
    char name[50];
    Readtext(name, sizeof(name));
    upperCase(name);
    char id[20];
    do
    {
        printf("STUDENT ID: ");
        Readtext(id, sizeof(id));
        upperCase(id);
    } while (isValid(id) == 0);

    int sem;

    do
    {
        printf("Semester(1-8): ");
        scanf(" %d", &sem);

        if (sem <= 0 || sem > 8)
        {
            printf("\nInvalid Semester Input[!], Enter Again Correct Semester Number: ");
        }
    } while (sem <= 0 || sem > 8);

    char std_fileName[60];
    sprintf(std_fileName, "%s_%s.txt", name, id);

    int returnFile = stdFileExists(std_fileName);
    if (returnFile == 0)
    {
        printf("Welcome %s! A new file has been created for you!\n", name);
        createStudentFile(std_fileName, name, id, sem);
    }
    else
    {
        printf("Welcome back %s!\n", name);
        readRegisteredCourses(std_fileName);
    }
    Course semesterCourses[MAX_COURSES];
    char courseFile[30];
    sprintf(courseFile, "semester%dcourses.txt", sem);
    int semesterCount = loadCourses(courseFile, semesterCourses);
    while (1)
    {

        int choice;
        do
        {
            displaymenu();
            printf("\nEnter Choice : ");
            scanf("%d", &choice);
            if (choice <= 0 || choice > 4)
            {
                printf("\nInvalid Input[!]. Please Enter Again Correct Choice : ");
            }
        } while (choice <= 0 || choice > 4);

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
                    printf("\nEnter Course code(0 to exit): ");
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
            printf("\nExiting The program");
            return 0;
            break;
        default:
            printf("\nInvalid Choice[!]");
            break;
        }
    }
    // display menu
    // input user(1.display courses/2. register course /3. view timwetable/ 4. exit)
    // switch case for display courses
    // display menu again
    // register courses store it in array
    // timeta

    return 0;
}