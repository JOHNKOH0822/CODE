#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>
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


int readlines(char *lineptr[], int maxlines)
{
    int len, nlines; 
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = getline_p(line, MAXLEN)) > 0) 
    {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) 
        {
            return -1 ;
        }
        else
        {
            line[len-1] = '\0'; 
            strcpy(p, line);
            lineptr[nlines++] = p; 
        }
    }
    return nlines;
}
void swap(void *v[], int i, int j) // use void* means it can work with any pointer type
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
    {
        printf("%s\n", lineptr[i]);
    }
}

/* Exercise 5-14 */
void writelines_r(char *lineptr[], int nlines)
{
    int i;
    for(i = nlines - 1; i >= 0; i--)
    {
        printf("%s\n", lineptr[i]);
    }
}

/* comp is a POINTER TO a function that returns int */
void qsort_my(void *v[], int left, int right, int (*comp)(void *, void *)) 
{
    int i, last;
    void swap(void *[], int, int);
    if(left >= right)
    {
        return;
    }
    swap(v, left, (left + right) / 2);
    last = left;
    for(i = left + 1; i <= right ; i++)
    {
        if((*comp)(v[i], v[left]) < 0) // comp can be numcmp or strcmp here depends on the input
        {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort_my(v, left, last - 1, comp);
    qsort_my(v, last + 1, right, comp);
}
/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if(v1 < v2)
    {
        return -1;
    }
    else if (v1 > v2)
    {
        return 1;
    }
    else
    {
        return 0; // equal
    }
}

/*Exercise 5-15*/
int strcasecmp_p(char *s1, char *s2)
{
    for ( ; tolower(*s1) == tolower(*s2); s1++, s2++)
    {
        if(*s1 == '\0')
        {
            return 0;
        }
    }
    return tolower(*s1) - tolower(*s2);
}

/* Exercise 5-16 */
int strdircmp(char *s1, char *s2)
{
    for ( ; ; s1++, s2++)
    {
        while (!isalnum(*s1) && *s1 != ' ' && *s1 != '\0')
        {
            s1++;
        }
        while (!isalnum(*s2) && *s2 != ' ' && *s2 != '\0')
        {
            s2++;
        }
        if (*s1 != *s2 || *s1 == '\0')
        {
            break;
        }
    }
    return *s1 - *s2;
}
/* Exercise 5-16 */
int strdir_casecmp(char *s1, char *s2)
{
    for ( ; ; s1++, s2++)
    {
        while (!isalnum(*s1) && *s1 != ' ' && *s1 != '\0')
        {
            s1++;
        }
        while (!isalnum(*s2) && *s2 != ' ' && *s2 != '\0')
        {
            s2++;
        }
        if ( tolower(*s1) != tolower(*s2) || *s1 == '\0')
        {
            break;
        }
    }
    return tolower(*s1) - tolower(*s2);
}

int main(int argc, char *argv[])
{
    int nlines; /* number of input lines read */
    int numeric = 0; /* 1 if numeric sort */
    int reverse = 0;
    int fold = 0;
    int directory = 0;
    while (--argc > 0)
    {
        ++argv;
        if ((*argv)[0] == '-')
        {
            if((*argv)[1] == 'n')
            {
                numeric = 1;
            }
            else if((*argv)[1] == 'r')
            {
                reverse = 1;
            }
            else if((*argv)[1] == 'f')
            {
                fold = 1;
            }
            else if((*argv)[1] == 'd')
            {
                directory = 1;
            }
        }
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) 
    {
        // comp can be numcmp or strcmp depends on the input
        qsort_my((void**) lineptr, 0, nlines-1,        
        fold && directory ? (int(*)(void*,void*))strdir_casecmp :
        numeric ? (int(*)(void*,void*))numcmp : // if numeric = 1
        fold ? (int(*)(void*,void*))strcasecmp_p : // if fold = 1
        directory ? (int(*)(void*,void*))strdircmp :
        (int(*)(void*,void*))strcmp);
        if(reverse == 1)
        {
            writelines_r(lineptr, nlines);
        }
        else 
        {
            writelines(lineptr, nlines);
        }
        return 0;
    } 
    else 
    {
        printf("input too big to sort\n");
        return 1;
    }
 }