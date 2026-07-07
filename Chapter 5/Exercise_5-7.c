// Modified readlines to readlines_mod and main to handle the change

#include <stdio.h>
#include <string.h>
#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOCSIZE 10000 
char *lineptr[MAXLINES]; /* pointers to text lines */
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int getline_p(char *line, int max);
char *alloc(int);

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

void swap(char *v[], int i, int j) // *v[i]  the first character of the ith string
                                   // *(v[i] + j) the jth character of the ith string
                                   // *v + i the ith pointer in the array
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

//reads lines from input and stores them
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines; // nlines is the total count of lines successfully read and stored in lineptr
    char *p, line[MAXLEN]; // p is a pointer to store in lineptr, line is a temporary buffer to store input
    nlines = 0;
    while ((len = getline_p(line, MAXLEN)) > 0) // if len = 0 means getline reads EOF can refer back to getline function
    {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) // failure cases : too many lines OR alloc ran out of space
        {
            return -1 ;
        }
        else
        {
            line[len-1] = '\0'; /* delete \n cuz basically input is a == "a" "\n" "\0" */
            strcpy(p, line); // copy input line to pointer p
            lineptr[nlines++] = p; // store the pointer to linepointer and increase the number of lines by 1
        }
    }
    return nlines;
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

// qsort for string store string in alphabetical order
void qsort(char *v[], int left, int right) // if have n lines left = 0 right = n
{
    int i, last;
    void swap(char *v[], int i, int j); // declaration purpose
    if (left >= right) /* do nothing if array contains fewer than two elements */
    {
        return;
    } 
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
    {
        if (strcmp(v[i], v[left]) < 0)
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

int readlines_mod(char *lineptr[], char lines[][MAXLEN], int maxlines)
{
    int len, nlines; 
    nlines = 0;
    while ((len = getline_p(lines[nlines], MAXLEN)) > 0)
    {
        if (nlines >= maxlines)
        {
            return -1;
        }
        lines[nlines][len-1] = '\0'; // remove '\n'
        lineptr[nlines] = lines[nlines]; // lineptr stores lines[nlines]
        nlines++;
    }
    return nlines;
}

char lines[MAXLINES][MAXLEN]; // an 2D array to replace allocbuf

int main()
{
    int nlines; 
    if ((nlines = readlines_mod(lineptr, lines ,MAXLINES)) >= 0) 
    {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } 
    else 
    {
        printf("error: input too big to sort\n");
        return 1;
    }
}
