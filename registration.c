#include <stdio.h>
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