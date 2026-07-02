#include <stdio.h>
#include <string.h>

void reverse_r(char s[], int i, int j)
{
    /*
    Initial:        h e l l o     i=0, j=4

    1st call:       swap s[0]='h' ↔ s[4]='o'
                    o e l l h     recurse(s, 1, 3)

    2nd call:       swap s[1]='e' ↔ s[3]='l'
                    o l l e h     recurse(s, 2, 2)

    3rd call:       i == j (2 == 2) → return
    */
   // base case return when i = j means reach the mid pos
    if(i >= j)
    {
        return ;
    }
    // swap function
    int temp;
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    // recall and increase i by 1 (move right first)
    // decrease j by 1 (move left last)
    reverse_r(s, i + 1, j - 1) ;
}
void reverse(char s[]) 
{
    int len = strlen(s);
    if (len > 1) 
    {
        reverse_r(s, 0, len - 1);
    }
}
int main()
{
    char s[1000];
    int c, i = 0;
    printf("Enter a string: ");
    while ((c = getchar()) != EOF && c != '\n' && i < 999)
    {
        s[i++] = c;
    }
    s[i] = '\0';

    reverse(s);

    printf("Reversed string: %s\n", s);

    return 0;
}