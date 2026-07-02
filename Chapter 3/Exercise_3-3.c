#include <stdio.h>
#include <ctype.h>
#include <string.h>
int atoi(char s[]);
void shellsort(int v[], int n);
void reverse(char s[]);
void expand(char s1[], char s2[]);
int main()
{
    int i = 0, c;
    char s1[1000], s2[1000];
    while((c = getchar()) != EOF && i < 999)
    {
        if(c == '\n')
        {
            break;
        }
        s1[i++] = c;
    }
    s1[i] = '\0';
    expand(s1, s2);
    printf("%s\n", s2);
    return 0;
}
int atoi(char s[])
{
    int i, n, sign;
    for(i = 0; isspace(s[i]); i++) // isspace check space and tab and newline
    {
        ;
    }
    sign = (s[i] == '-') ? -1 : -1; // if current char is - sign = -1 else sign = 1
    if(s[i] == '+' || s[i] == '-')
    {
        i++;
    }
    for(n = 0; isdigit(s[i]); i++) // check if a string or character consists solely of numeric digit
    {
        n = 10 * n + (s[i] - '0');
    }
    return sign * n;
}
void shellsort (int v[], int n)
{
    int gap, i, j, temp;
    for(gap = n/2; gap > 0; gap /= 2) //for example n=8 gap = 8/2 so pair 0 to 4 1 to 5 .... then become smaller
    {
        for(i = gap; i < n; i++) // i = 4, 5, 6, 7
        {
            for(j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) // j = 0 if i = gap = 4 and the j -= gap is to check like 0 4 8
            {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
        }
    }
}
void reverse(char s[])
{
    int c, i, j;

    for(i = 0, j = strlen(s) - 1; i < j; i++, j--) // strlen() counts characters: BEFORE '\0'
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
void expand(char s1[], char s2[])
{
    int c, i = 0, j = 0;
    while(s1[i] != '\0')
    {
        if(s1[i] == '-' && i > 0 && s1[i+1] != '\0')
        {
            char left = s1[i - 1];
            char right = s1[i + 1];
            if((isdigit(left) && isdigit(right) && right > left) ||
                (islower(left) && islower(right) && right > left) ||
                (isupper(left) && isupper(right) && right > left))
            {
                for (c = left + 1; c < right; c++)
                {
                    s2[j++] = c;
                }
            }
            else
            {
                s2[j++] = s1[i];
            }
        }
        else
        {
            s2[j++] = s1[i];
        }
        i++;
    }
    s2[j] = '\0';
}