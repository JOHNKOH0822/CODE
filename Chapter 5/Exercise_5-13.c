#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 
char *lineptr[MAXLINES]; /* pointers to text lines */


static char allocbuf[ALLOCSIZE]; 
static char *allocp = allocbuf; 
char *alloc(int n)
{
    if(allocbuf + ALLOCSIZE - allocp >= n) 
    {
        allocp += n;
        return allocp - n; 
    }
    else
    {
        return 0;
    }
}

 /* writelines: write output lines */
 void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
    {
        printf("%s\n", lineptr[i]);
    }
}

int getline_p(char *line, int max)
{
    int i = 0, c;
    while(-- max > 0 && (c = getchar()) != EOF && c != '\n')
    {
        *line++ = c;
        i++;
    }
    if(c == '\n')
    {
        *line++ = c;
        i++;
    }
    *line = '\0'; 
    return i;
}

void tail(char *lineptr[], int n)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];
    while ((len = getline_p(line, MAXLEN)) > 0)
    {
        if (nlines >= MAXLINES || (p = alloc(len)) == NULL) 
        {
            return;
        }
        else
        {
            line[len-1] = '\0'; 
            strcpy(p, line); 
            lineptr[nlines++] = p; 
        }
    }
    if(n >= nlines)
    {
        writelines(lineptr, nlines);
    }
    else if(n == 0)
    {
        ;
    }
    else if(n < 0)
    {
        printf("Invalid : Negative n");
    }
    else
    {
        writelines(lineptr + (nlines - n), n);
    }
}

int main(int argc, char *argv[])
{
    int n = 10; /* Initialize n as 10 (default)*/
    while (--argc > 0)
    {
        ++argv;
        if ((*argv)[0] == '-')
            n = atoi(*argv + 1);  // skip the '-', read the number
    }
    tail(lineptr, n);
    return 0;
}