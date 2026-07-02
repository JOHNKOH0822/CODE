#include <stdio.h>  
#include <ctype.h>  
#define SIZE 10     
#define BUFSIZE 100 
char buf[BUFSIZE];  
int bufp = 0;       

int getch(void) // pop something off the buffer
{
    return (bufp > 0) ? buf[--bufp] : getchar(); 
}

void ungetch(int c) // push something onto buffer or fail if is full
{
    if (bufp >= BUFSIZE) 
        printf("ungetch: too many characters\n"); 
    else 
        buf[bufp++] = c; 
}



int getint_mod(int *pn) 
{
    int c, sign, next_c ; 

    while (isspace(c = getch())) 
        ; 

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') 
    { 
        ungetch(c); 
        return 0; 
    }

    sign = (c == '-') ? -1 : 1;  

    if (c == '+' || c == '-')
    {
        next_c = getch();
        if(!isdigit(next_c))
        {
            if(next_c != EOF)
            {
                ungetch(next_c);
            }
            ungetch(c);
            return 0;
        }
        // transfer the digit into c so the for loop can use the digit
        // without this line when handle +5 since now c is + and next_c is 5
        // and with + it cannot passes the next for loop
        // this line enable when next_c is a valid digit u must assign the value back to c
        c = next_c;
    }
        
    for (*pn = 0; isdigit(c); c = getch()) 
        *pn = 10 * *pn + (c - '0'); 
                                    
    *pn *= sign; 

    if (c != EOF) 
        ungetch(c); 

    return c; 
}
int getint(int *pn) 
{
    int c, sign, next_c ; 

    while (isspace(c = getch())) 
        ; 

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') { 
        ungetch(c); 
        return 0; 
    }

    sign = (c == '-') ? -1 : 1;  

    if (c == '+' || c == '-') 
        c = getch();

    for (*pn = 0; isdigit(c); c = getch()) 
        *pn = 10 * *pn + (c - '0'); 
                                    

    *pn *= sign; 

    if (c != EOF) 
        ungetch(c); 

    return c; 
}

float getfloat(float *pn)
{
    int c, sign, next_c;
    float power ;
    while (isspace(c = getch())) 
    {
        ;
    }
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') 
    { 
        ungetch(c); 
        return 0; 
    }
    sign = (c == '-') ? -1 : 1;
        if (c == '+' || c == '-')
    {
        next_c = getch();
        if(!isdigit(next_c))
        {
            if(next_c != EOF && next_c != '.')
            {
                ungetch(next_c);
            }
            ungetch(c);
            return 0;
        }
        c = next_c;
    }
    for (*pn = 0; isdigit(c); c = getch())
    {
        *pn = 10 * *pn + (c - '0'); 
    }
    if(c == '.')
    {
        c = getch();
    }
    for(power = 1.0; isdigit(c); c = getch())
    {
        *pn = 10 * *pn + (c - '0'); 
        power *= 10.0;
    }
    *pn = (*pn * sign) / power;
    if (c != EOF) 
    {
        ungetch(c);
    }
    return c; 
}
//If the user types 12.34
//The first loop builds 12
//It hits the . and moves to the second loop
//It reads 3 -> Total becomes 123, Power becomes 10.0
//It reads 4 -> Total becomes 1234, Power becomes 100.0
//Final calculation: 1234 / 100.0 = 12.34
int main(void) 
{
    int n; 
    float array[SIZE]; 
    int type ;
    for (n = 0; n < SIZE && (type = getfloat(&array[n])) != EOF; )
        if(type == 0) // type = 0 means invalid input 
        {
            getch();
        }
        else
        {
            n++;
        }
    for (int i = 0; i < n; i++) 
        printf("array[%d] = %f\n", i, array[i]); 

    return 0; 
}