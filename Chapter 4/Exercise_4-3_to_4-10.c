// Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the input.
// Should ungets know about buf and bufp, or should it just use ungetch? 
// ANS : It should only use ungetch. This maintains abstraction. 
// ungets doesn't need to know how the buffer is implemented; 
// it just trusts ungetch to handle the data storage



//Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF correctly.
// Decide what their properties ought to be if an EOF is pushed back, then implement your design. 
// ANS : In the original code, buf was declared as char buf[BUFFSIZE].
// EOF is defined as -1. On many systems, char is an unsigned 8-bit integer. 
// If we pass -1 into a char array, it wraps around and stores 255. 
// When we read it back out, it reads as 255, not -1 (EOF).
// Therefore, your program will never terminate properly if an EOF gets pushed back.
// SOL : switch char to int
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */
#define BUFFSIZE 100 
#define NAME 'n' // Modify for Exercise 4-5 adding math function
#define MAXLINE 1000
int getop(char []);
void push (double );
double pop (void);
double atof(const char s[]);
int getch(void);
void ungetch(int);
int getop(char s[]);
void print_top(void);               // Exercise 4-4
void duplicate_top(void);           // Exercise 4-4
void swap_top(void);                // Exercise 4-4
void clear_stack(void);             // Exercise 4-4
void ungets(char s[]);              // Exercise 4-7 ungetch but push back entire string
int getch_mod(void);                // Exercise 4-8
void ungetch_mod(int);              // Exercise 4-8
int getline(char line[], int max); 
int getop_using_getline(char s[]);  // Exercise 4-10
/* Stack purpose */
int sp = 0;
double val[MAXVAL];
int buf[BUFFSIZE]; // (internal cache array) Changed from char to int for Exercise 4-9 
int bufp = 0; // tracks how many characters are currently sitting inside the storage bin

/*FOR EXERCISE 4-8*/
int buf_mod = 0;


int main()
{
    int type;
    int var = 0;
    double variables[26];
    double v = 0;
    double op2;
    char s[MAXOP];
    while((type = getop(s)) != EOF )
    {
        switch(type)
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-': // subtract and divide is speacial case cuz order matters
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if(op2 != 0.0)
                {
                    push(pop() / op2);
                }
                else
                {
                    printf("Error : zero divisor\n");
                }
                break;
            case '%' : //  Exercise 4-3
                op2 = pop();
                if(op2 != 0.0)
                {
                    push(fmod(pop(), op2));
                }
                else
                {
                    printf("Error : zero divisor\n");
                }
                break;
            case '?' :
                print_top();
                break;
            case 'd' :
                duplicate_top();
                break;
            case 's' :
                swap_top();
                break;
            case 'c' :
                clear_stack();
                break;
            case NAME : // Exercise 4-5 all angle are in radians
                if(strcmp(s, "sin") == 0) 
                {
                    push(sin(pop()));
                }
                else if(strcmp(s, "cos") == 0)
                {
                    push(cos(pop()));
                }
                else if(strcmp(s, "tan") == 0)
                {
                    push(tan(pop()));
                }
                else if(strcmp(s, "exp") == 0)
                {
                    push(exp(pop()));
                }
                else if(strcmp(s, "pow") == 0)
                {
                    op2 = pop();
                    push(pow(pop(), op2));
                }
                else
                {
                    printf("Erorr : Unknown Function %s\n", s);
                }
                break;
            case '=':
                pop(); // remove the variable e.g A , pop the value we are assigning
                if(var >= 'A' && var <= 'Z')
                {
                    variables[var - 'A' /*why - 'A' just to let it become 0/1/2..*/] = pop(); // pop the value we assigning 
                    push(variables[var - 'A']); // push back 
                }
                else
                {
                    printf("Error : No variable name\n");
                }
                break;
            case '\n':
                v = pop(); // Save most recently printed value
                printf("\t%.8g\n", v);
                break;
            default:
                if(type >= 'A' && type <= 'Z') 
                {
                    push(variables[type - 'A']);// Push the variable's value onto the stack
                    var = type; // Remember this letter in case the next operator is '='
                }
                else if (type == 'v')
                {
                    push(v); //  Push most recent value
                }
                else
                {
                    printf("Error: unknown command %s\n", s);
                }
                break;
        }
    }
    return 0;
}
double atof(const char s[])
{
    double val, power;
    int i, sign;
    for(i = 0; isspace(s[i]); i++)
    {
        ; 
    }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) 
    {
        val = 10.0 * val + (s[i] - '0'); 

    }
    if(s[i] == '.')
    {
        i++; 
    }
    for(power = 1.0; isdigit(s[i]); i++) 
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10; 
    }
    return sign * val / power;
}

void push(double f)
{
    if (sp < MAXVAL) // check is there still got space left
    {
        val[sp++] = f; // store into stack
    }
    else // exceed maximum storage
    {
        printf("Error : stack full, cant push %g\n", f);
    }
}
double pop(void)
{
    if(sp > 0) // check is there any numbers currently sitting in array
    {
        return val[--sp];   // pre decrement value of i is decreased by 1 first,
                            // and then the new value is returned , if sp = 1 return val[0]
    }
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
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
void print_top(void) // Exercise 4-4
{
    if(sp > 0)
    {
        printf("%.8g\n", val[sp - 1]);
    }
    else
    {
        printf("Stack Empty : cant print top");
    }
}
void duplicate_top(void) // Exercise 4-4
{
    if(sp > 0)
    {
        push(val[sp - 1]);
    }
    else
    {
        printf("Stack Empty : cant duplicate");
    }
}
void swap_top(void) // Exercise 4-4
{
    if(sp > 1)
    {
        double temp = val[sp - 1];
        val[sp - 1] = val[sp -2];
        val[sp - 2] = temp;
    }
    else
    {
        printf("Error: need at least two elements to swap\n");
    }
}
void clear_stack(void) // Exercise 4-4
{
    sp = 0;
}
void ungets(char s[])
{
    int len = strlen(s);
    while(len > 0)
    {
        ungetch(s[--len]);
    }
}

int getch_mod(void) // only handle 1 char 
{
    int c;
    if(buf_mod != 0)
    {
        c = buf_mod;
        buf_mod = 0;
        return c;
    }
    else
    {
        return getchar();
    }
}
void ungetch_mod(int c)
{
    if(buf_mod != 0)
    {
        printf("ungetch : too many characters\n");
    }
    else
    {
        buf_mod = c;
    }
}
int getline(char line[], int max)
{
    int c, i;
    i = 0;
    while(-- max > 0 && (c = getchar()) != EOF && c != '\n') // keep reading till buffer full/ EOF / next line 
    {
        line[i++] = c;
    }
    if(c == '\n')
    {
        line[i++] = c;  // store '\n'
    }
    line[i] = '\0';
    return i;
}

/*FOR EXERCISE 4-10*/
char line[MAXLINE];
int line_idx = 0;

int getop_using_getline(char s[])
{
    int i = 0;
    int c;

    /* Load a new line if current line finished */
    if (line[line_idx] == '\0') // reached the end of line
    {
        if (getline(line, MAXLINE) == 0) // If cannot read a new line from input, stop processing
        {
            return EOF;
        }

        line_idx = 0;
    }

    /* Skip spaces and tabs */
    while (line[line_idx] == ' ' || line[line_idx] == '\t')
    {
        line_idx++;
    }

    /* Peek current character */
    c = line[line_idx]; // check current char

    /* if (i < MAXOP - 1) means only write into array if there is still space left for characters + null terminator */

    /* Handle identifiers/functions */
    if (isalpha(c))
    {
        while (isalnum(line[line_idx])) // check isit alphabet or number 
        {
            if (i < MAXOP - 1)
            {
                s[i++] = line[line_idx];
            }

            line_idx++;
        }

        s[i] = '\0';
        return NAME;
    }

    /* Handle operators/newline */
    if (!isdigit(c) && c != '.' && c != '-')
    {
        line_idx++;
        return c;
    }

    /* Handle minus sign */
    if (c == '-')
    {
        /* Check if this is subtraction operator */
        if (!isdigit(line[line_idx + 1]) && line[line_idx + 1] != '.')
        {
            line_idx++;
            return '-'; // is an subtraction operator
        }

        /* It's a negative number */
        if (i < MAXOP - 1)
        {
            s[i++] = line[line_idx]; // is negative number handle it properly
        }
        line_idx++;
    }

    /* Integer part */
    while (isdigit(line[line_idx]))
    {
        if (i < MAXOP - 1)
        {
            s[i++] = line[line_idx];
        }

        line_idx++;
    }

    /* Fractional part */
    if (line[line_idx] == '.')
    {
        if (i < MAXOP - 1)
        {
            s[i++] = line[line_idx];
        }

        line_idx++;

        while (isdigit(line[line_idx]))
        {
            if (i < MAXOP - 1)
            {
                s[i++] = line[line_idx];
            }

            line_idx++;
        }
    }

    s[i] = '\0';

    return NUMBER;
}