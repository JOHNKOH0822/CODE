#include <stdio.h>

int main() {
    int c, i, j;
    int char_counts[128];
    for (i = 0; i < 128; i++) {
        char_counts[i] = 0;
    }
    while ((c = getchar()) != EOF) {

        if (c >= 0 && c < 128) {
            char_counts[c]++;
        }
    }
    printf("\nCharacter Frequency Histogram:\n");

    for (i = 32; i < 127; i++) {
        if (char_counts[i] > 0) {
            printf("%c : ", i);
            printf(" %d", char_counts[i]);
            printf("\n");
        }
    }

    return 0;
}
