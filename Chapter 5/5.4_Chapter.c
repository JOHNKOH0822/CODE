#include <stdio.h>
#define ALLOCSIZE 10000 // size of available space
static char allocbuf[ALLOCSIZE]; // store alloc
static char *allocp = allocbuf; // next free position 
                                // same with static char *allocp = &allocbuf[0]
                                // why * needed is just let it become 0 at first so it 
                                //  Set its starting value to allocbuf (the address of allocbuf's first byte
char *alloc( int n )    // the * here is for expression position which means
                        // give me the value this pointer points to
                        // the function return to pointer n characters  
{
    if(allocbuf + ALLOCSIZE - allocp >= n) // allocbuf just allocbuf[0] + allocbuf[10000] so basically
                                           // is total distance - spaces occupied = free space available
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
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE) // check p is somewhere in the buffer ?
    {
        allocp = p;
    }
}