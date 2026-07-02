#include <stdio.h>
#include <string.h>
void itoa(int n, char s[]);
void itoa_pro(int n, char s[]);
void reverse(char s[]); 
int main()
{
    int n;
    char s[1000];
    printf("Enter integers (Ctrl+D / Ctrl+Z to stop):\n");

    while (scanf("%d", &n) != EOF)
    {
        itoa_pro(n, s);
        printf("n = %s\n", s);
    }
    return 0;
}
void itoa(int n, char s[])
{
    int i = 0, sign;
    if((sign = n) < 0)
    {
        n = -n; // make number positive temporarily 
                // because digit extraction easier with positive numbers
                // but when handle min int (negative) it will cause error 
                //cuz the most negative int is out of range when is positive
    }
    do
    {
        s[i++] = n % 10 + '0'; // take the single digits into string 123 % 10 = 3 then 12 % 10 = 2 ....
    }
    while((n /= 10) > 0); // remove last digit 123/10 = 12
    if(sign < 0)
    {
        s[i++] = '-'; // put the negative sign back
    }
    s[i] = '\0';
    reverse(s); // if is 123 cuz we produce 3 first then 2 then 1 so output is 321 so we need to reverse it
}
void itoa_pro(int n, char s[])
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
    s[i] = '\0';
    reverse(s);
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

// In a two's complement number representation, our version of itoa does not
//handle the largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why not.
//Modify it to print that value correctly, regardless of the machine on which it runs.

// The function fails because negating the most negative two’s complement integer 
//causes overflow (its positive counterpart cannot be represented), 
//so the fix is to avoid direct negation by using a larger or unsigned type 
//to safely extract digits.