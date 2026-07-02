#include <stdio.h>
#include <string.h>
void reverse(char s[]); 
void itob(int n, char s[], int b);
int main()
{
    int n, b;
    char s[1000];
    while (scanf("%d %d", &n, &b) == 2) // “Keep looping while scanf successfully reads TWO integers.”
    {
        itob(n, s, b);
        printf("%d in base %d = %s\n", n, b, s);
    }
    return 0;
}
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