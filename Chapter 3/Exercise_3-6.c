#include <stdio.h>
#include <string.h>
void itoa_width(int n, char s[], int width);
void reverse(char s[]); 
int trim(char s[]);
int main()
{
    int n, w;
    char s[1000];
    printf("Enter integers (Ctrl+D / Ctrl+Z to stop):\n");

    while (scanf("%d %d", &n, &w) != EOF)
    {
        itoa_width(n, s, w);
        printf("%s\n", s);
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
void itoa_width(int n, char s[], int width)
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
    while (i < width) // While the array length is less than the requested width
                      // keep appending spaces.
    {
        s[i++] = ' ';
    }
    s[i] = '\0';
    reverse(s);
}
int trim(char s[])
{
    int n;
    for (n = strlen(s)-1; n >= 0; n--)
    {
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
        {
            break;
        }
    }
    s[n+1] = '\0';
    return n;
}
