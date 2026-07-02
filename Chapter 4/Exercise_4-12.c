#include <stdio.h>
#include <string.h>
void swap(int v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
void qsort(int v[], int left, int right)
{
    int i, last;
    void swap(int v[], int i, int j);
    if(left >= right) // check isit there are 0 or 1 element only, if yes nothing to sort
    {
        return ;
    }
    swap (v, left, (left + right)/2);  // Find the middle element and move it to the first.
                                       // This will be our "partition element" (the divider)
    last = left; // set last = 0 means start
    for(i = left + 1; i <= right;  i++)
    {
        if(v[i] < v[left]) // if the v[1] > v[left] which is the middle element we swap jn
        {
            swap(v, ++last, i); // increase last to 1 then swap 
        }
        /*
        EXAMPLE : [7, 9, 2, 5] before is [9, 7, 2, 5]
        i = 1 v[1] = 9 < 7 NO then skip
        i = 2 v[2] = 2 < 7 YES increase last to 1 and swap v[1] with v[2] array become [7, 2, 9, 5]
        i = 3 v[3] = 5 < 7 YES increase last to 2 and swap v[2] with v[3] array become [7, 2, 5, 9]
        */
    }
    swap(v, left, last); 
    /*
    Depend on array, example : last = 2
    Swap v[0] with v[2] then become [5, 2, 7, 9]
    */
    qsort(v, left, last - 1);
    /*
    Recursively sort the left side (smaller elements).
    (0, 1)
    */
    qsort(v, last + 1, right);
    /*
    Recursively sort the right side (larger elements).
    (3, 3)
    */
}
void itoa(int n, char s[])
{
    static int i = 0;

    // 1. Descend to the deep base case first
    if (n / 10)
    {
        itoa(n / 10, s);
    }
    else
    {
        // 2. This else block ONLY runs at the very deepest call (the first digit)
        i = 0; // Explicitly clear the index for this execution run
        if (n < 0)
        {
            s[i++] = '-';
        }
    }

    // 3. Unwind and extract digits safely using negative-compatible modulo
    int rem = n % 10;
    s[i++] = (rem < 0 ? -rem : rem) + '0';
    s[i] = '\0';
}
void printd(int n)
{
    if(n < 0)
    {
        putchar('-');
        n = -n ;
    }
    if(n / 10)
    {
        printd(n / 10);
        putchar(n % 10 + '0');
    }
}
int main()
{
    char s[1000];
    itoa(123, s);
    printf("itoa(123) = %s\n", s);
    
    itoa(-456, s);
    printf("itoa(-456) = %s\n", s);
    
    itoa(0, s);
    printf("itoa(0) = %s\n", s);
    
    itoa(-1, s);
    printf("itoa(-1) = %s\n", s);
    return 0;
}