void strcat(char s[], char t[])
{
    int i, j;
    i = j = 0;
    while (s[i] != '\0') /* find end of s */
        i++;
    while ((s[i++] = t[j++]) != '\0') /* copy t */
        ;
}

void strcat_p(char *s, char *t)
{
    while(*s != '\0') // find the end of s
    {
        s++;
    }
    while(*(s++) = *(t++)) // Why not *(s++) = *(t++) != '\0'
                           // != has higher precedence than = so it just show true or false which is 1 or 0
    {
        ;
    }
}
