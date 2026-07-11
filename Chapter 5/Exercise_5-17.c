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


/* Exercise 5-17 */
#define MAXKEYS 10
struct key {
    int fieldnum;
    int numeric;
    int fold;
    int directory;
    int reverse;
};

struct key keys[MAXKEYS];
int nkeys = 0;
// fieldnum is for maybe Hi JKZE 0822 fieldnum = 2 means i want JKZE
char *getfield(char *line, int fieldnum)
{
    while(*line == ' ' ||  *line == '\t') // skip leading space
    {
        line++;
    }
    while(--fieldnum > 0) // fieldnum - 1 > 0 now fieldnum = 2-1 > 0 
    {
        while(*line != ' ' && *line != '\t' && *line != '\0') // skip everything this is when running Hi
        {
            line++;
        }
        while(*line == ' ' || *line == '\t') // now pointer hit the space between Hi and JKZE so now skip 
                                             // now the pointer hit JKZE so exit loop and 1 -1 > 0 false so pointer pointing JKZE now
        {
            line++;
        }
    }
    return line;
}

/*Basically a cmp caller
figures out which field to compare via getfield
figures out which comparison function to call based on keys flags
calls it and returns the result
*/

int linecmp(char *s1, char *s2)
{
    int i, result;
    char *f1, *f2;

    for(i = 0; i < nkeys; i++)
    {
        f1 = getfield(s1, keys[i].fieldnum);  
        f2 = getfield(s2, keys[i].fieldnum);
        if (keys[i].fold && keys[i].directory)
        {
            result = strdir_casecmp(f1, f2);
        }
        else if (keys[i].numeric)
        {
            result = numcmp(f1, f2);
        }
        else if (keys[i].fold)
        {
            result = strcasecmp_p(f1, f2);
        }
        else if (keys[i].directory)
        {
            result = strdircmp(f1, f2);
        }
        else
        {
            result = strcmp(f1, f2);
        }
        if(result != 0)
        {
            return keys[i].reverse ? -result : result;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int nlines; /* number of input lines read */
    int numeric = 0; /* 1 if numeric sort */
    int reverse = 0;
    int fold = 0;
    int directory = 0;
    int fieldnum = 0;
    while (--argc > 0)
    {
        ++argv;
        if ((*argv)[0] == '-')
        {
            if((*argv)[1] == 'n')
            {
                keys[nkeys].numeric = 1;
            }
            else if((*argv)[1] == 'r')
            {
                keys[nkeys].reverse = 1;
            }
            else if((*argv)[1] == 'f')
            {
                keys[nkeys].fold = 1;
            }
            else if((*argv)[1] == 'd')
            {
                keys[nkeys].directory = 1;
            }

            if(argc > 1 && isdigit(argv[1][0]))
            {
                ++argv;
                --argc;
                fieldnum = atoi(*argv);
            }
            else
            {
                fieldnum = 1;
            }
            keys[nkeys].fieldnum = fieldnum;
            nkeys++;  
        }
    }
    if (nkeys == 0)
    {
        keys[0].fieldnum = 1;
        keys[0].numeric = 0;
        keys[0].fold = 0;
        keys[0].directory = 0;
        keys[0].reverse = 0;
        nkeys = 1;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) 
    {
        // comp can be numcmp or strcmp depends on the input
        qsort_my((void**) lineptr, 0, nlines-1, (int(*)(void*,void*))linecmp);
        writelines(lineptr, nlines);
        return 0;
    } 
    else 
    {
        printf("input too big to sort\n");
        return 1;
    }
}