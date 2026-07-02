#include <stdio.h>
unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);
int main()
{
    unsigned x, y;
    int p, n;
    // printf("Enter x y p n (in correct order) :"); Exercise 2-6 Testing
    // scanf("%u %u %d %d", &x, &y, &p, &n);
    // unsigned result = setbits(x, p, n, y);
    // printf("Result : %u\n", result);
    // printf("Enter x p n (in correct order) :"); /*Exercise 2-7 Testing*/
    // scanf("%u %d %d", &x, &p, &n);
    // unsigned result = invert(x, p, n);
    // printf("Result : %u\n", result);
    printf("Enter x n (in correct order) :"); /*Exercise 2-8 Testing*/
    scanf("%u %d", &x, &n);
    unsigned result = rightrot(x, n);
    printf("Result : %u\n", result);
    return 0;
}
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned tempy = ((y & ~(~ 0 << n)) << (p + 1 - n));
    unsigned tempx = (x & ~(~(~0 << n) << (p + 1 - n)));
    return(tempx | tempy);
}
unsigned invert(unsigned x, int p, int n)
{
    return(x ^ ( (~(~0 << n)) << (p + 1 - n) ));
}
unsigned rightrot(unsigned x, int n)
{
    int width = sizeof(x) * 8; // sizeof(x) give the number of bytes of value 
                               //for example int have 4 bytes so * 8 have 32bits
    n = n % width; // rotate 35 == rotate 3 so 35 % 32 = 3 prevent undefined behaviour
    if (n == 0)
    {
        return x;
    }
    
    return(x >> n) | (x << (width - n)); // return (unsigned char)((x >> n) | (x << (width - n))); if playing 8 bits
}