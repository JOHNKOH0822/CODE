#include <stdio.h>
int main()
{
    int c, n, i = 0, j = 0;
    char s[1000], t[1000];

    printf("Enter first string (s): ");
    while ((c = getchar()) != '\n' && c != EOF && i < 999)
        s[i++] = c;
    s[i] = '\0';

    printf("Enter second string (t): ");
    while ((c = getchar()) != '\n' && c != EOF && j < 999)
        t[j++] = c;
    t[j] = '\0';

    printf("Enter n: ");
    scanf("%d", &n);

    int result = strncmp_p(s, t, n);
    printf("Result: %d\n", result);

    return 0;
}