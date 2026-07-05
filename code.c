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

void swap(char *v[], int i, int j) // v[]  the first character of the ith string
                                   // *v + i the ith pointer in the array
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
        {
            return -1 ;
        }
        else
        {
             line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
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

void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right) /* do nothing if array contains */
    {
        return; /* fewer than two elements */
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

int main()
{
    int nlines; /* number of input lines read */
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) 
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
