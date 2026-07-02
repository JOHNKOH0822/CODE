#include <stdio.h>
int main() {
    signed char e = (signed char)((unsigned char)~0 >> 1);
    signed short f = (signed short)((unsigned short)~0 >> 1);
    signed int g = (signed int)((unsigned int)~0 >> 1);
    signed long h = (signed long)((unsigned long)~0 >> 1);
    printf("Unsigned Char Max: %u\n", (unsigned char)~0); // bitwise NOT operator which turns 0 to 1 / 1 to 0 
    printf("Unsigned Short Max: %hu\n", (unsigned short)~0);
    printf("Unsigned Int Max: %u\n", ~0u);  // u means unsigned int
    printf("Unsigned Long Max: %lu\n", ~0ul); // ul means unsigned long

    printf("Signed Char Max: %d\n", e);
    printf("Signed Char Min: %d\n", -(e + 1));
    printf("Signed Short Max: %hd\n", f);
    printf("Signed Short Min: %hd\n", -(f + 1));
    printf("Signed Int Max: %i\n", g);
    printf("Signed Int Min: %i\n", -(g + 1));
    printf("Signed Long Max: %ld\n", h);
    printf("Signed Long Min: %ld\n", -(h + 1L));
    return 0;
}