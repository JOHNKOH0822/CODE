/* 
Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit
in x. Explain why. 
In two’s complement, subtracting 1 flips all bits after and including the rightmost 1-bit.
When this result is ANDed with the original number, all unchanged higher bits remain, 
the flipped lower bits cancel out, and the rightmost 1-bit becomes 0 in both operands. 
Hence it is removed.
For example x = 1101, 1101 & 1100 = 1100
                      1100 & 1011 = 1000
                      1000 & 0111 = 0111
3 operations indicate 3 bits of 1
*/

#include <stdio.h>
int bitcount(unsigned x);
int bitcount_faster(unsigned x);
int main()
{
    unsigned x;
    printf("Enter a number: ");
    scanf("%u", &x);
    printf("Number of 1 bits = %d %d", bitcount(x), bitcount_faster(x));
    return 0;
}
int bitcount(unsigned x)
{
    int b; // number of bits of 1
    for (b = 0; x != 0 ; x >>= 1) // initial = 0, if x = 1101 then it runs like (why rightmost bit cuz it is LSB least significant bit)
    {                             // 1101 last bit is 1 then b = 0 + 1 and x shift right 1 bit 
        if (x & 01)               // 0110 last bit is 0 b remains shift right
        {                         // 0011 last bit is 1 b+1, then 0001 b + 1 then 0000 finish
            b++;
        }
    }
    return b;
}

int bitcount_faster(unsigned x)
{
    int b;
    while (x != 0)
    {
        x &= x - 1;
        b ++;
    }
    return b;
}