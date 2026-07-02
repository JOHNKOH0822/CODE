#include <stdio.h>
void strncpy_p (char *s, char *t, int n)
{
    while(n > 0 && *t != '\0')
    {
        *s++ = *t++;
        n--;
    }
    *s = '\0';
}
void strncat_p (char *s, char *t, int n)
{
    while(*s != '\0') 
    {
        s++;
    }
    while(n > 0 && *t != '\0')
    {
        *s++ = *t++;
        n--;
    }
    *s = '\0';
}
int strncmp_p (char *s, char *t, int n)
{
    while(n > 0 && *t != '\0' && *s != '\0')
    {
        if(*s != *t)
        {
            return *s - *t; 
        }
        n--;
        s++;
        t++;
    }
     return 0;
}
int main()
{
    int c, n, i = 0, j = 0;
    char s[1000], t[1000];

    printf("Enter first string (s): ");
    while ((c = getchar()) != '\n' && c != EOF && i < 999)
        s[i++] = c;
    s[i] = '\0';

    printf("Enter second string (t): ");
    while ((c = getchar()) != '\n' && c != EOF && j < 999)
        t[j++] = c;
    t[j] = '\0';

    printf("Enter n: ");
    scanf("%d", &n);

    int result = strncmp_p(s, t, n);
    printf("Result: %d\n", result);

    return 0;
}