#include <stdio.h>
#include <string.h>
#include "copy.h"

char str[5][MAXLINE];
char temp[MAXLINE];

int main() {
    int i = 0;
    while (i < 5) {
        fgets(temp, MAXLINE - 1, stdin);
        temp[strcspn(temp, "\n")] = '\0'; 
        strcat(str[i], temp);
        i++;
    }

    int m = 0;
    while (m < 4) {
        int n = 0;
        while (n < 4 - m) {
            if (strlen(str[n]) < strlen(str[n + 1])) {
                copy(str[n], temp);
                copy(str[n + 1], str[n]);
                copy(temp, str[n + 1]);
             }
            n++;
        }
        m++;
    }

    int j = 0;
    while (j < 5) {
        puts(str[j]);
        j++;
    }

    return 0;
}
