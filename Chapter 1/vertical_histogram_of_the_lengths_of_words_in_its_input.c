#include <stdio.h>

#define IN 1
#define OUT 0

int main() {
    int c, i, j, len, state;
    int nchar[11];

    state = OUT;
    len = 0;

    for (i = 0; i <= 10; i++) {
        nchar[i] = 0;
    }
    while ((c = getchar()) != EOF) {

        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                if (len >= 10)
                    len = 10;

                nchar[len]++;
                len = 0;
                state = OUT;
            }
        }
        else {
            if (state == OUT) {
                state = IN;
                len = 1;
            } else {
                len++;
            }
        }
    }
    if (state == IN) {
        if (len >= 10)
        {
            len = 10;
        }
        nchar[len]++;
    }

    printf("\nWord length histogram:\n");

    for (i = 1; i <= 10; i++) {
        if (i == 10) {
            printf("10+: ");
        } else {
            printf("%2d : ", i);
        }
	printf(" %d", nchar[i]);
        printf("\n");
    }

    return 0;
}
