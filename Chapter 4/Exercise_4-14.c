#include <stdio.h>
#define swap(t,x,y) {t temp; temp = x; x = y; y = temp ;}
#define swap_pro(t, x, y) do { t _swap_temp_ = (x); (x) = (y); (y) = _swap_temp_; } while (0)
void swap_e(int v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
int main()
{
    return 0;
}
/*
The normal swap 
SUPPOSE                     
if (a > b)
    swap(int, a, b);
else
    printf("no swap\n");   

Macro expands to:
    if (a > b)
{
    int temp;
    ...
};
else
    printf("no swap\n");

Now compiler gets confused because: extra semicolon ends the if-statement

Possible syntax error.

do { } while(0) fixes this

Why (x) and (y)?  Protects against weird expressions.

while (0) means "loop while false."
*/ 