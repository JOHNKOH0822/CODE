#include <stdio.h>
int any(char s1[], char s2[]);
int main()
{
    char s1[1000], s2[1000];
    int c, i = 0, j = 0;
    while ((c = getchar()) != '\n' && c != EOF && i < 999)
    {
        s1[i++] = c;
    }
    s1[i] = '\0';
        while ((c = getchar()) != '\n' && c != EOF && j < 999)
    {
        s2[j++] = c;
    }
    s2[j] = '\0';
    int location = any(s1, s2);
    printf("%d\n", location);
    return 0;
}
int any(char s1[], char s2[])
{
    int i, k;
    for (i = 0; s1[i] != '\0' ; i++)
    {
        for ( k = 0; s2[k] != '\0'; k++)
        {
            if (s1[i] == s2[k])
            {
                return i;

            }
            
        }
    }
    return -1;    
}
