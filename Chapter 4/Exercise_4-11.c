#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXOP 100   
#define NUMBER '0'  
#define MAXVAL 100  
#define BUFFSIZE 100 
#define NAME 'n' 
#define MAXLINE 1000
int sp = 0;
double val[MAXVAL];
int buf[BUFFSIZE]; 
int bufp = 0;
int main()
{
    return 0;
}
int getop (char s[]) 
{
    static int lastchar = EOF; 
    int i, c, next;
    if(lastchar != EOF) // check whether lastchar storing anything ?
    {
        c = lastchar; // if yes let c be the last char
        lastchar = EOF; // consume saved char
    }
    else
    {
        c = getch(); // np then get char
    }
    while ( (s[0] = c = getch()) == ' ' || c == '\t') 
    {
        ; 
    }
    s[1] = '\0'; 
    if(isalpha(c)) 
    {
        i = 0;
        do
        {
            s[i++] = c;
        }
        while(isalpha(c = getch()));
        s[i] = '\0';
        if(c != EOF)
        {
            lastchar = c;
        }
        return NAME; 
    }
    if (!isdigit(c) && c != '.' && c != '-' ) 
    {
        return c;
    }
    i = 0;
    if(c == '-') 
    {
        next = getch();
        if(!isdigit(next) && next != '.') 
        {
            if(next != EOF)
            {
                lastchar = next;
                return c; 
            }
        }
        else
        {
            s[++i] = c = next; 
        }
    }
    if(isdigit(c))
    {
        while (isdigit(s[++i] = c = getch())) 
        {
            ;
        }
    }
    if(c == '.')
    {
        while (isdigit(s[++i] = c = getch()))
        {
            ;
        }   
    }
    s[i] = '\0';
    if(c != EOF)
    {
        lastchar = c;
    }
    return NUMBER;
}

int getch(void) 
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