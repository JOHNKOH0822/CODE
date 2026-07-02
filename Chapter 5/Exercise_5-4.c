int strend(char s[], char t[])
{
    int i, j, lt = 0, ls = 0;
    while (s[ls] != '\0') 
    {
        ls++ ;
    }
    while (t[lt] != '\0') 
    {
        lt++ ;
    }
    if(lt > ls)
    {
        return 0;
    }
    i = ls - lt;
    j = 0;
    while(t[j] != '\0')
    {
        if(s[i] != t[j])
        {
            return 0;
        }
        i++;
        j++;
    }
    return 1;
}

int strend_p(char *s, char *t)
{
    int ls = 0, lt = 0;
    while(*s != '\0')
    {
        s++;
        ls++;
    }
    while(*t != '\0')
    {
        t++;
        lt++;
    }
    if(lt > ls)
    {
        return 0;
    }
    s = s - lt;   /* step back lt positions from the end */
    t = t - lt;   /* reset t to its beginning */
    while(*t != '\0')
    {
        if(*s != *t)
            return 0;
        s++;
        t++;
    }
    return 1;
}