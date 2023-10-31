#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc) {
    const char *file_path = "test.txt";
    char savedText[10][100];
    int row = 0, col = 0;
    char ch;

    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        perror("Error open file");
        return 1;
    }

    while (row < 10 && (ch = fgetc(file)) != EOF) {
        if (ch != '\n') 
	{
            savedText[row][col] = ch;
            col++;
        } 
	else 
	{
            savedText[row][col] = '\0';
            row++;
            col = 0;
        }
    }

    fclose(file);

int line_number;
    printf("pls 'Enter' the line to select : ");
    char input[100];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < row; i++) {
            printf("%s\n", savedText[i]);
        }
    } else if (strchr(input, '-') != NULL) {
        int start, end;
        if (sscanf(input, "%d-%d", &start, &end) == 2 && start > 0 && end <= row && start <= end) {
            for (int i = start - 1; i < end; i++) {
                printf("%s\n", savedText[i]);
            }
        } else {
            printf("Error\n");
        }
    } else if (strchr(input, ',') != NULL) {
        char *token = strtok(input, ",");
        while (token != NULL) {
            int line;
            if (sscanf(token, "%d", &line) == 1 && line > 0 && line <= row) {
                printf("%s\n", savedText[line - 1]);
            } else {
                printf("Error\n");
            }
            token = strtok(NULL, ",");
        }
    } else {
        if (sscanf(input, "%d", &line_number) == 1 && line_number > 0 && line_number <= row) {
            printf("%s\n", savedText[line_number - 1]);
        } else {
            printf("Error\n");
        }
    }
    return 0;
}
