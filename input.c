#include "myheader.h"

// Maximum and minimum values
#define MAX 100
#define MIN 10
#define VALUE  MAX

int main()
{
    /* Variable declarations */
    int a = MAX;
    int b = MIN;
    int c = VALUE;

    // Macro replacement multiple times
    int total = MAX + MIN;

    printf("MAX = %d\n", a);
    printf("MIN = %d\n", b);
    printf("VALUE = %d\n", c);

    /* Preserve comments inside strings */
    printf("// This is not a comment\n");
    printf("/* This is not a comment */\n");

    return 0;
}
