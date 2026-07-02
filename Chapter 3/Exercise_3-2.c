#include <stdio.h>
void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int main()
{
    char input[1000];
    char escaped[1000];
    char restored[1000];
    int i = 0, c;
    while((c = getchar()) != EOF && i < 999)
    {
        if(c == '\n')
        {
            break;
        }
        input[i++] = c;
    }
    input[i] = '\0';
    unescape(restored, input);
    printf("Escaped string: %s\n", restored);
    return 0;
}
void escape(char s[], char t[])
{
    int i, j; // i is for input and j is for output
    for(i = j = 0; t[i] != '\0'; i++)
    {
        switch(t[i])
        {
            case '\n':
                s[j++] = '\\';
                s[j++] ='n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\b':
                s[j++] = '\\';
                s[j++] = 'b';
                break;
            default:                
                s[j++] = t[i];
                break;
        }
    }
}
void unescape(char s[], char t[])
{
    int i, j;
    for(i = j = 0; t[i] != '\0'; i++)
    {
        if(t[i] == '\\')
        {
            switch(t[i + 1])
            {
                case 'n':
                s[j++] = '\n';
                i++;
                break;
                case 't':
                s[j++] = '\t';
                i++;
                break;
                case 'b' :
                s[j++] = '\b';
                break;
                default:
                s[j++] = '\\';
                break;
            }
        }
        else
        {
            s[j++] = t[i];
        }
    }
    s[j] = '\0';
}