#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAXLINE 1000
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
int main(int argc, char *argv[])
{
    int c;
    double op2;
    while(--argc > 0)
    {
        ++argv;
        // check first char of first string is digit number or . or - if is - check next char is number or not
       if (isdigit((*argv)[0]) || (*argv)[0] == '.' || ((*argv)[0] == '-' && isdigit((*argv)[1])))
        {
            push(atof(*argv));
        }
        else
        {
        /*
        *argv → the current argument string (e.g. "+")
        argv[0] → same as *argv, the current argument string
        (*argv)[0] → first character of current argument string → '+'
        argv[0][0] → same as (*argv)[0] → first character → '+'
        */
            c = (*argv)[0];
            switch(c)
            {
                case '+':
                    push(pop() + pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '*' :
                    push(pop() * pop()) ;
                    break;
                case '/' :
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
                case '%' : 
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
                default : 
                    printf("Unknown command");
            }
        }
    }
    printf("%.8g\n", pop());
    return 0;
}

