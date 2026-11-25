#include<stdio.h>
#include<string.h>
#include"fileoperation.h"
#include"mystring.h"
#include<stdlib.h>
int main(int argc, char **argv)
{
    system("clear");
    int lenIn;
    if (argc != 2) {
        printf("USAGE : ./mypreprocessor input.c\n");
        return 1;
    }
//-------------------READING THE SOURCE FILE-----------------------
    FILE *src = fopen(argv[1], "r"), *dest;
    if (src == NULL) {
        printf("\033[33m*******************\033[0m\n");
        printf("\033[33mFile is not present\033[0m\n");
        printf("\033[33m*******************\033[0m\n");
        return 1;
    }
    lenIn = strlen(argv[1]);
    char iFile[lenIn+1];
    ifilegenerator(iFile, argv[1]);
//----------------------------COMMENT REMOVAL-------------------------
    dest = fopen("temp.i", "w");
    if (dest == NULL) {
        printf("\033[33m**********************\033[0m\n");
        printf("\033[33m.i File is not created\033[0m\n");
        printf("\033[33m**********************\033[0m\n");
        fclose(src); // CHANGE
        return 1;
    }
    commentRemoval(src, dest);
    fclose(src);
    fclose(dest);
//--------------------------HEADER INCLUSION--------------------------
    src = fopen("temp.i", "r");
    dest = fopen("temp2.i", "w");
    if (src == NULL || dest == NULL) { // CHANGE
        printf("Unable to open temporary files\n");
        if (src != NULL)
            fclose(src);
        if (dest != NULL)
            fclose(dest);
        remove("temp.i");
        return 1;
    }
    fileInclusion(src, dest);
    fclose(src);
    fclose(dest);
    remove("temp.i");
//-------------------------MACRO REPLACEMENT-------------------------
    src = fopen("temp2.i", "r");
    dest = fopen(iFile, "w");
    if (src == NULL || dest == NULL) { // CHANGE
        printf("Unable to open files for macro replacement\n");
        if (src != NULL)
            fclose(src);
        if (dest != NULL)
            fclose(dest);
        remove("temp2.i");
        return 1;
    }
    macroReplacement(src, dest);
    fclose(src);
    fclose(dest);
    remove("temp2.i");
//------------------------------------------------------------------
    printf("\033[34m*******************\033[0m\n");
    printf("\033[35m%s is created.\033[0m\n", iFile); // CHANGE
    printf("\033[34m*******************\033[0m\n");
    return 0;
}
