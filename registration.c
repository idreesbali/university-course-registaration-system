#include <stdio.h>
void readRegistered(char filename[])
{
    int courseCount = 0;
    char code[7];
    FILE *file = fopen(filename, "r");
    fscanf(file, "%*[^\n]%*c");
    while (fscanf(file, "%6s\n", code) == 1)
    {
        printf("%s\n", code);
    }
    fclose(file);
}