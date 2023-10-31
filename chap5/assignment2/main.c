#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 80

int main(int argc, char *argv[])
{
        FILE *fp;
        int line = 0;
        char buffer[MAXLINE];
        char **lines = NULL;

        if (argc != 2) {
                fprintf(stderr, "How to use: %s test.txt\n", argv[0]);
                return 1;
        }

        if ( (fp = fopen(argv[1],"r")) == NULL) {
                fprintf(stderr, "Error file open\n");
                return 2;
        }

        while (fgets(buffer, MAXLINE, fp) != NULL) {
                line++;
                char *copy = malloc(strlen(buffer) + 1);
                strcpy(copy, buffer);
                lines = (char **)realloc(lines, line * sizeof(char *));
                lines[line - 1] = copy;
        }

        fclose(fp);

        for (int i = line - 1; i >= 0; i--) {
            printf("%s", lines[i]);
            free(lines[i]);
        }

        free(lines);

        return 0;
}

