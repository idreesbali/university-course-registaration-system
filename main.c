#include <stdio.h>
#include "common.h"
int main()
{
    int choice;
    printf("NAME: ");
    char name[50];
    scanf("%s", name);
    printf("STUDENT ID: ");
    char id[8];
    scanf("%s", id);
    printf("Semester: ");
    int sem;
    scanf("%d", &sem);
    switch (sem)
    {
    case 1:
        loadCourses("semester1courses.txt", coursesForSem1);
        displayCourses(coursesForSem1);
        break;
    }

    return 0;
}