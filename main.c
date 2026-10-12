#include <stdio.h>
#include "common.h"
#include <string.h>
#include <ctype.h>
int FileExist(char text[], char id[])
{
    char filename[100];
    sprintf(filename, "%s_%s.txt", text, id);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    fclose(file);
}
void Readtext(char text[], int size)
{
    if (fgets(text, size, stdin) != NULL)
    {
        text[strcspn(text, "\n")] = '\0';
    }
}
void filename(char name[], char id[], int sem)
{
    char filename[100];
    sprintf(filename, "%s_%s.txt", name, id);
    FILE *file = fopen(filename, "w");
    fprintf(file, "%s|%s|%d", name, id, sem);

    fclose(file);
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
    if (text[0] == '\n')
    {
        return 1;
    }
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isdigit(text[i]) && text[i] != '-' && !isalpha(text[i]))
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int choice;
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
        isValid(id);
        if (isValid(id) == 0)
        {
            printf("Invalid ID. Please Enter Again\n");
        }
    } while (isValid(id) == 0);
    printf("Semester(1-4): ");
    int sem;
    scanf(" %d", &sem);
    int returnFile = FileExist(name, id);
    if (returnFile == 1)
    {
        printf("Welcome %s! A new file has been created for you!\n", name);
        filename(name, id, sem);
    }
    else
    {
        printf("Welcome back %s!\n", name);
        char filename[100];
        sprintf(filename, "%s_%s.txt", name, id);
        readRegistered(filename);
    }
    /*switch (sem)
    {
    case 1:
        loadCourses("semester1courses.txt", coursesForSem1);
        displayCourses(coursesForSem1);
        break;
    case 2:
        loadCourses("semester2courses.txt", coursesForSem2);
        displayCourses(coursesForSem2);
        break;
    case 3:
        loadCourses("semester3courses.txt", coursesForSem3);
        displayCourses(coursesForSem3);
        break;
    case 4:
        loadCourses("semester4courses.txt", coursesForSem4);
        displayCourses(coursesForSem4);
        break;
    } */

    return 0;
}