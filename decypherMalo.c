#include <stdio.h>
#include <string.h>

void decrypt(char *src) {

    int i, shifts = 0;
    int mix = 1;
    int max_shifts = 95;
    char *patterns[] = {" the ", " is ", "ing", " was ", " do ", " a ", "for"};
    int patterns_count = sizeof(patterns) / sizeof(patterns[0]);

    if (src == NULL || *src == '\0') {
            printf("Invalid input string.\n");
            return;
        }

    while(shifts < max_shifts) {
        for(i = 0; i < patterns_count; i++) {
            if (strstr(src, patterns[i]) != NULL) {
                printf("the text was probably : '%s'\n", src);
                return;
            }
        }
        for(i = 0; src[i] != '\0'; i++) {
            src[i] = ((src[i] - ' ') + mix) % 95 + ' ';
        }
        shifts++;
    }
    printf("No matching pattern found after %d shifts.\n", max_shifts);
}

int main () {

    char src[200];

    printf("enter your phrase : ");
    scanf(" %[^\n]", src);

    decrypt(src);

    return 0;
}
