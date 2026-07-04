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
void reverse(char s[])
{
    int i, j, c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void reverse_p(char *s)
{
    int temp, end;
    char *start = s;
    for(end = strlen(s) - 1; s < start + end; s++, end--) // s and start + end both pointer (index)
    {
        temp = *s;
        *s = *(start + end);
        *(start + end) = temp;
    }
}

int getch(void) // to get the char
{
    // Ternary Check: Is bufp greater than 0?
    // IF TRUE:  Decrement bufp first, then grab and return the character from buf[--bufp].
    // IF FALSE: The buffer cache is empty; call standard getchar() to pull from the live terminal.
    return(bufp > 0) ? buf[--bufp] : getchar(); 
}

void ungetch(int c) // to release the char
{
    if(bufp >= BUFFSIZE)
    {
        printf("ungetch : too many characters\n");
    }
    else // if still got space
    {
        buf[bufp++] = c; //1. Place character 'c' into buf[bufp]. 2. Increment bufp by 1.
    }
}

int getline(char line[], int max)
{
    int c, i;
    i = 0;
    while(-- max > 0 && (c = getchar()) != EOF && c != '\n')
    {
        line[i++] = c;
    }
    if(c == '\n')
    {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
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
    *line = '\0'; // no need line + i cuz line edi pointing last char
    return i;
}

int my_atoi(char s[])
{
    int i, n;
    n = 0;
    for (i = 0;  s[i] >= '0' && s[i] <= '9'; i++)
    {
        n = 10 * n + (s[i] - '0');
    }
    return n;
}

int atoi_p(char *s)
{
    int n = 0;
    while(*s >= '0' && *s <= '9')
    {
        n = 10 * n + (*s - '0');
        s ++;
    }
    return n;
}

int htoi(char s[])
{
    int i = 0;
    int n = 0;     
    int digit = 0;
    int sign = 1;
    while (s[i] == ' ' || s[i] == '\t') 
    {
        i++;
    }
    if (s[i] == '+' || s[i] == '-')
    {
        if (s[i] == '-')
        {
            sign = -1;
        }
        i++;
    }
    
    if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
    {
        i += 2;
    }
    for ( ; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            digit = s[i] - '0' ; 
        }
        else if (s[i] >= 'a' && s[i] <= 'f') // which means (a - f) - a(97), now a-f represent 0-6 adding 10 to make it become 10-16
        {
            digit = s[i] - 'a' + 10 ;
        }
        else if (s[i] >= 'A' && s[i] <= 'F')
        {
            digit = s[i] - 'A' + 10 ; // which means (A - F) - A(65), now A-F represent 0-6 adding 10 to make it become 10-16
        }
        else
        {
            break;
        }
        n = 16 * n + digit; 
    }
    return sign * n;
}

int htoi_p(char *s)
{
    int n = 0;     
    int digit = 0;
    int sign = 1;
    while(*s == ' ' || *s == '\t')
    {
        s++;
    }
    if (*s == '+' || *s == '-')
    {
        if (*s == '-')
        {
            sign = -1;
        }
        s++;
    }
    if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
    {
        s += 2;
    }
    for ( ; *s != '\0'; s++)
    {
        if (*s >= '0' && *s <= '9')
        {
            digit = *s - '0' ; 
        }
        else if (*s >= 'a' && *s <= 'f') // which means (a - f) - a(97), now a-f represent 0-6 adding 10 to make it become 10-16
        {
            digit = *s - 'a' + 10 ;
        }
        else if (*s >= 'A' && *s <= 'F')
        {
            digit = *s - 'A' + 10 ; // which means (A - F) - A(65), now A-F represent 0-6 adding 10 to make it become 10-16
        }
        else
        {
            break;
        }
        n = 16 * n + digit; 
    }
    return sign * n;
}

void my_itoa(int n, char s[]) // can hanlde exrtreme value
{
    int i = 0, sign;
    unsigned int temp;
    if((sign = n) < 0)
    {
        temp = (unsigned int)(-(long)n); // convert int to -long then convert long to unsigned int
    }
    else
    {
        temp = n;
    }
    do
    {
        s[i++] = temp % 10 + '0';  
    }
    while((temp /= 10) > 0); 
    if(sign < 0)
    {
        s[i++] = '-'; 
    }
    s[i] = '\0';
    reverse(s);
}

void itoa_p(int n, char *s)
{
    int sign ;
    unsigned int temp;
    char *start = s; // save the starting point
    if((sign = n) < 0)
    {
        temp = (unsigned int)(-(long)n); 
    }
    else
    {
        temp = n;
    }
    do
    {
        *(s++) = temp % 10 + '0';
    }
    while((temp /= 10) > 0);
    if(sign < 0)
    {
        *s++ = '-';
    }
    *s = '\0';
    reverse (start);
}

void itob(int n, char s[], int b)
{
    int i = 0, sign;
    int digit;
    unsigned int temp;
    if((sign = n) < 0)
    {
        temp = (unsigned int)(-(long)n); 
    }
    else
    {
        temp = n;
    }
    do
    {
        digit = temp % b;
        if(digit < 10)
        {
            s[i++] = digit + '0';
        }
        else
        {
            s[i++] = digit - 10 + 'A';
        }
    }
    while((temp /= b) > 0) ;
    if(sign < 0)
    {
        s[i++] = '-'; 
    }
    s[i] = '\0';
    reverse(s);
}

void itob_p(int n, char *s, int base)
{
    int sign;
    char *start = s; // save the starting point
    int digit;
    unsigned int temp;
    if((sign = n) < 0)
    {
        temp = (unsigned int)(-(long)n); 
    }
    else
    {
        temp = n;
    }
    do
    {
        digit = temp % base;
        if(digit < 10)
        {
            *(s++) = digit + '0';
        }
        else
        {
            *(s++) = digit - 10 + 'A';
        }
    }
    while((temp /= base) > 0);
    if(sign < 0)
    {
        *(s++) = '-';
    }
    *s = '\0';
    reverse(start);
}

double my_atof(char s[])
{
    double val, power;
    int i, sign;
    for(i = 0; isspace(s[i]); i++)
    {
        ; // skip if is space
    }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) // handle integer part
    {
        val = 10.0 * val + (s[i] - '0'); // process digit ten by ten, 123 when 1 save val as 1
                                         // when 2 save val as 1 * 10 + 2
    }
    if(s[i] == '.')
    {
        i++; // skip .
    }
    for(power = 1.0; isdigit(s[i]); i++) // handle fractional part
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10; // handle 1 digit after . save 10 after this divide back
    }
    return sign * val / power;
}

double atof_p( char *s )
{
    double val, power;
    int sign;
    while(isspace(*s))
    {
        s++;
    }
    sign = (*s == '-') ? -1 : 1;
    if(*s == '+' || *s == '-')
    {
        s++;
    }
    for(val = 0.0; isdigit(*s); s++)
    {
        val = 10.0 * val + (*s - '0');
    }
    if(*s == '.')
    {
        s++;
    }
    for(power = 1.0; isdigit(*s); s++) 
    {
        val = 10.0 * val + (*s - '0');
        power *= 10; 
    }
    return sign * val / power;
}

int strindex(char s[], char t[])
{
    int i, j, k;
    for(i = 0; s[i] != '\0'; i++)
    {
        for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) // compare the first char 
                                                                  // of both input and pattern
        {
            ;
        }
        if(k > 0 && t[k] == '\0')
        {
            return i;
        }
    }
    return -1;
}

int strindex_p(char *s, char *t)
{
    int i;
    char *start_s = s;
    char *start_t = t;
    while(*s != '\0')
    {
        t = start_t;
        char *mark = s; // leave a mark on current position like i in an array s[i]
        for( ; *t != '\0' && *s == *t; s++, t++)
        {
            ;
        }
        if(*t == '\0')
        {
            return mark - start_s;
        }
        s = mark + 1;
    }
    return -1;
}

int getop (char s[]) // used in main
{
    int i, c, next;
    while ( (s[0] = c = getch()) == ' ' || c == '\t') //get character, store in c, also store in s[0]
    {
        ; // skip space and tabs
    }
    s[1] = '\0'; // temporarily makes string length 1 is very useful when we comparing it with the special function name
                 // because strcmp can only used in valid string
    if(isalpha(c)) // Exercise 4-5 identify if is an alphabet
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
            ungetch(c);
        }
        return NAME; // return as NAME Token to main
    }
    if (!isdigit(c) && c != '.' && c != '-' ) // if is not number
    {
        return c;
    }
    i = 0;
    if(c == '-') // Exercise 4-3
    {
        next = getch();
        if(!isdigit(next) && next != '.') // It's just a minus sign. Push the 'next' char back for the next read.
        {
            if(next != EOF)
            {
                ungetch(next); // throw back the char
                return c; // return as operator
            }
        }
        else
        {
            s[++i] = c = next; // store next char tgt with - sign
        }
    }
    if(isdigit(c))
    {
        while (isdigit(s[++i] = c = getch())) // keep reading next char is digit or not
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
        ungetch(c); // token parsing requires overshooting one character to know when a token ends
                    // and that character must be returned to the input stream.
    }
    return NUMBER;
}

int getop_p( char *s)
{
    int c, next;
    char *start = s;
    while ( (s[0] = c = getch()) == ' ' || c == '\t') 
    {
        ; 
    }
    *(s + 1) = '\0';
    if(isalpha(c))
    {
        s = start;
        do
        {
            *(s++) = c;
        }
        while(isalpha(c = getch()));
        *s = '\0';
        if(c != EOF)
        {
            ungetch(c);
        }
        return NAME; 
    }
    if (!isdigit(c) && c != '.' && c != '-' ) 
    {
        return c;
    }
    if(c == '-') 
    {
        next = getch();
        if(!isdigit(next) && next != '.') 
        {
            if(next != EOF)
            {
                ungetch(next); 
                return c;
            }
        }
        else
        {
            *(++s) = c = next; 
        }
    }
    if(isdigit(c))
    {
        while (isdigit(*(++s) = c = getch())) 
        {
            ;
        }
    }
    if(c == '.')
    {
        while (isdigit(*(++s) = c = getch()))
        {
            ;
        }   
    }
    *s = '\0';
    if(c != EOF)
    {
        ungetch(c); 
    }

    return NUMBER;
}
