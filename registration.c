#include<stdio.h>
#include<string.h>
#include "common.h"

Course registeredCourses[MAX_REGISTERED_COURSES];

int stdFileExists(const char fileName[]) {
    FILE *file = fopen(fileName, "r");

    if(file==NULL) {
        return 0;
    }
    
    fclose(file);
    return 1;
}

void createStudentFile(const char std_fileName[],char name[], char id[], int sem) {
    FILE *file = fopen(std_fileName, "w");

    if(file==NULL) {
        printf("\nError creating File");
        return;
    }
    
    fprintf(file, "%s|%s|%d", name,id,sem);
    fclose(file);
}

void readRegisteredCourses(const char fileName[]) {
    FILE *file = fopen(fileName, "r");

    if(file==NULL) {
        printf("\nError opening file");
        return;
    } else {
        int total_lines = 0;
        char line[100];
        while(fgets(line, sizeof(line),file) != NULL) {
            total_lines++;
        }
        rewind(file);
        
        fgets(line,sizeof(line),file);

        for (int i = 0; i < total_lines - 1 &&
                    i < MAX_REGISTERED_COURSES; i++) {
                        
            if (fscanf(file, "%9s", registeredCourses[i].course_code) == 1) {
            printf("Course CODE: %s\n",
                   registeredCourses[i].course_code);
            }
        }
        fclose(file);
    }
}