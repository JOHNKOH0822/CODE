#include <stdio.h>
#define ALLOCSIZE 10000 // size of available space
// why static is because of private so it hides hides allocbuf and allocp from other .c
static char allocbuf[ALLOCSIZE]; // store alloc
static char *allocp = allocbuf; // next free position 
                                // same with static char *allocp = &allocbuf[0]
                                // why * needed is just let it become 0 at first so it 
                                //  Set its starting value to allocbuf (the address of allocbuf's first byte
char *alloc( int n )    // the * here is for expression position which means
                        // this function returns a char*
{
    if(allocbuf + ALLOCSIZE - allocp >= n) // is address of start + end - address of next free slot  = free space available
    {
        allocp += n;
        return allocp - n; // pointer to the start of the block you just claimed
    }
    else
    {
        return 0;
    }
}
void afree(char *p)
{
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE) // checking if p is a valid address inside the buffer 
    {
        allocp = p;
    }
}