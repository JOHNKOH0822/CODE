#include <ctype.h>
#include <stdio.h>
#include <math.h>
#define  MAXLINE 1000
double atof(char s[]); // convert string to double
double atof_ex(char s[]);
int main()
{
    return 0;
}
double atof(char s[])
{
    double val, power;
    int i, sign;
    for(i = 0; isspace(s[i]); i++)
    {
        ; // skip if is space
    }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) // handle integer part
    {
        val = 10.0 * val + (s[i] - '0'); // process digit ten by ten, 123 when 1 save val as 1
                                         // when 2 save val as 1 * 10 + 2
    }
    if(s[i] == '.')
    {
        i++; // skip .
    }
    for(power = 1.0; isdigit(s[i]); i++) // handle fractional part
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10; // handle 1 digit after . save 10 after this divide back
    }
    return sign * val / power;
}
double atof_ex(char s[])
{
        double val, power;
    int i, sign;
    for(i = 0; isspace(s[i]); i++)
    {
        ; // skip if is space
    }
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
    {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) // handle integer part
    {
        val = 10.0 * val + (s[i] - '0'); // process digit ten by ten, 123 when 1 save val as 1
                                         // when 2 save val as 1 * 10 + 2
    }
    if(s[i] == '.')
    {
        i++; // skip .
    }
    for(power = 1.0; isdigit(s[i]); i++) // handle fractional part
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10; // handle 1 digit after . save 10 after this divide back
    }

    val = sign * val / power;

    if(s[i] == 'e' || s[i] == 'E')
    {
        i++;
    }
    else
    {
        return val; // if  there is no exponent 
    }
    int exp_sign = 1;
    int exp = 0;
    if (s[i] == '+' || s[i] == '-')
    {
        exp_sign = (s[i] == '-') ? -1 : 1;
        i++;
    }
    for (exp = 0; isdigit(s[i]); i++)
    {
        exp = 10 * exp + (s[i] - '0');
    }
    int final_exp = exp_sign * exp; // sign * exp value
    
    double scale = 1.0;
    int j = 0;
    for(j = 0; j < exp ; j++)
    {
        scale *= 10.0; // 10e n if n = +- 3 scale = 1000
    }
    if(final_exp > 0)
    {
        val *= scale;
    }
    else
    {
        val /= scale;
    }
    return val;
}