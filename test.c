#include <stdio.h>

int counter1 = 0;
int counter2 = 0;
int count = 0;
char *string1 = "hello";
char *string2 = "world";
int variable_long = 5;
int variable_short = 3;

int main()
{
    int local_var1 = 10;
    int local_var2 = 20;
    /* this is a comment with counter3 inside */
    char *ignored = "string_var1 string_var2";
    
    counter1++;
    counter2++;
    variable_long = variable_short + local_var1;
    return 0;
}