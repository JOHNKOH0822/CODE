/*
sizeof(int)        // usually 4
sizeof(double)     // usually 8
sizeof(char)       // always 1
sizeof(struct key) // size of the whole struct
to calculate the elements in key automatically we use #define NKEYS (sizeof keytab / sizeof(struct key))
sizeof keytab → total bytes of the whole array
sizeof(struct key) → bytes of one element
so whole / one = number of element

#define NKEYS (sizeof keytab / sizeof(keytab[0])) is better
because if u change struct key to maybe struct keyword or other this automatically works

*/



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

/* binsearch: find word in tab[0]...tab[n-1] */
// word is the keyword we finding 
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while(low <= high)
    {
        mid = (low + high) / 2;
        //  keys in keytab must be in alphabetical order so strcmp works
        if((cond = strcmp(word, tab[mid].word)) < 0) // cond is negative when target word appear before the mid word
        {
            high = mid - 1; // decrease high to have smaller range
        }
        else if(cond > 0) // word appear after the mid work
        {
            low = mid + 1; // increase low to have smaller range
        }
        else
        {
            return mid ; // = 0 means the word at mid
        }
    }
    return -1;
}

// original getword
/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

// getword_mod Exercise 6-1
// break if u found end .....  ; while u still havent found the end 
int getword_mod(char *word, int lim)
{
    int c, next_c;
    char *w = word;

    while ((c = getch()) != EOF)
    {
        if (isspace(c))
        {
            ; // keep looping/skipping spaces
        }
        else if (c == '#')
        {
            while ((c = getch()) != '\n' && c != EOF)
            {
                ; // skip preprocessor lines
            }
        }
        else if (c == '/')
        {
            next_c = getch();
            if (next_c == '*')
            {
                // Skip block comments /* ... */
                int prev = 0;
                while ((c = getch()) != EOF) // can reuse c cuz old c is no longer neededd and the outer loop will reset c
                {
                    if (prev == '*' && c == '/')
                    {
                        break;
                    }
                    prev = c;
                }
            }
            else if (next_c == '/')
            {
                // Skip single-line comments // ...
                while ((c = getch()) != '\n' && c != EOF)
                {
                    ;
                }
            }
            else
            {
                ungetch(next_c);
                break; // It's a division operator, exit loop to process it
            }
        }   
        else if (c == '"')
        {
            // Skip string constants
            while ((c = getch()) != '"' && c != EOF)
            {
                if (c == '\\') 
                {
                    getch(); // skip escaped characters like \"
                }
            }
        }
        else if (c == '\'')
        {
            // Skip character constants like "\n"
            while ((c = getch()) != '\'' && c != EOF)
            {
                if (c == '\\') 
                {
                    getch(); // skip escaped characters like \'
                }
            }
        }
        else
        {
            break; // Found a valid target character, exit loop
        }
    }

    // If we reached the end of the file, exit immediately and signal EOF
    if (c == EOF)
    {
        return EOF;
    }

    // Store the first validated character
    *w++ = c; 

    // If it is not an identifier starter, treat it as a single-char token
    if (!isalpha(c) && c != '_') 
    {
        *w = '\0'; 
        return c; 
    }

    // Collect valid identifier characters (alphanumeric + underscores)
    for ( ; --lim > 1; w++) 
    {
        c = getch();
        if (isalnum(c) || c == '_')
        {
            *w = c;
        }
        else
        {
            ungetch(c); // Push back the non-identifier character boundary
            break;
        }
    }
    *w = '\0'; 
    return word[0]; 
}

int main()
{
    int n;
    char word[MAXWORD];
    while(getword_mod(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0]))
        {
            if((n = binsearch(word, keytab, NKEYS)) >= 0)
            {
                keytab[n].count++ ;
            }
        }
    }
    for(n = 0; n < NKEYS ; n++)
    {
        if(keytab[n].count > 0)
        {
            printf("%4d %s\n", keytab[n].count, keytab[n].word );
        }
    }
    return 0;
}

