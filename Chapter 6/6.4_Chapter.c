#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0])) 
#define MAXVAL 100  
#define BUFFSIZE 100 
#define MAXLINE 1000
int sp = 0;
double val[MAXVAL];
int buf[BUFFSIZE]; 
int bufp = 0; 
int getch(void) // to get the char
{
    return(bufp > 0) ? buf[--bufp] : getchar(); 
}
void ungetch(int c) 
{
    if(bufp >= BUFFSIZE)
    {
        printf("ungetch : too many characters\n");
    }
    else 
    {
        buf[bufp++] = c; 
    }
}

struct key {
    char * word;
    int count;
};

struct key keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
};

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while(isspace(c =getch()))
    {
        ; 
    }
    if(c != EOF)
    {
        *w++ = c; // store c first 
    }
    if(!isalpha(c)) // check the first char is alphabet 
    {
        *w = '\0'; // if is not alphabet immediately null terminate
    }
    for( ; --lim > 0; w++) // start at second slot cuz first slot have c already
    {
        if(!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    }
    *w = '\0'; // if for loop breaks or word too long null terminates
    return word[0]; // return the first char of whatever was read
}
/*
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if((cond = strcmp(word, tab[mid].word)) < 0) 
        {
            high = mid - 1; 
        }
        else if(cond > 0) 
        {
            low = mid + 1; 
        }
        else
        {
            return mid ; 
        }
    }
    return -1;
}
*/
struct key *binsearch(char *word, struct key *tab, int n)
{
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;
    while(low < high)
    {
        mid = low + (high - low) / 2;
        if((cond = strcmp(word, mid-> word)) < 0)
        {
            high = mid;
        }
        else if(cond > 0)
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
    }
    return NULL;
}

int main()
{
    struct key *p;
    char word[MAXWORD];
    
    while(getword(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0]))
        {
            if(p = binsearch(word, keytab, NKEYS) != NULL)
            {
                p -> count++; // same with (*p).count++
            }
        }
    }
    for(p = keytab; p < keytab + NKEYS; p++) // increments by the full size of the struct automatically — not by 1 byte
    {
        if(p -> count > 0)
        {
            printf("%4d %s\n", p->count, p->word);
        }
    }
    return 0;
}

