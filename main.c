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
    scanf(" %d", &sem);
    switch (sem)
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
    }

    return 0;
}