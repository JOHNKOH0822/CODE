#include <stdio.h>
int atoi(char s[]);
int htoi(char line[]);
int main()
{
    int c, i = 0;
    char s[1000];

    while ((c = getchar()) != EOF && i < 999)
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            if (i > 0)
            {
                s[i] = '\0';
                printf("Decimal value: %d\n", htoi(s));
                i = 0;
            }
        }
        else if (i < 999)
        {
            s[i++] = c;
        } 
    }
    if (i > 0)
    {
        s[i] = '\0';
        printf("Decimal value: %d\n", htoi(s));
    }   
    return 0;
}
int atoi(char s[])
{
    int i, n;
    n = 0;
    for (i = 0;  s[i] >= '0' && s[i] <= '9'; i++)
    {
        n = 10 * n + (s[i] - '0');
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