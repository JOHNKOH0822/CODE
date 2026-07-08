#include <stdio.h>
// argc and argv are how your program receives input from the terminal when it starts.
// if u type ./code hello world then u can pass it directly to the command

/* 1st version
    int i;
    for (i = 1; i < argc; i++)
    {
        printf("%s%s", argv[i], (i < argc-1) ? " " : ""); // print the command after ./code and the if loop is for spacing if is the last word no space needed
    }
    printf("\n");
    return 0;
*/
int main(int argc, char *argv[])
{
    while (--argc > 0) // check whether still got command pre-decrement to exclude ./code
    {
        printf("%s%s", *++argv, (argc > 1) ? " " : ""); // increase argv first then print argc
    }
    printf("\n");
    return 0;
}

