#include <stdio.h>
#include <stdlib.h>
#define MAX_COLS 32768

int main(int argc, char *argv[])
{
        FILE *fp;
        int c;
        int i;

        if (argc < 2) {
                fprintf(stderr, "How to use: %s <file1> <file2> <file3>\n", argv[0]);
		return 1;
	}
	for (i = 1; i < argc; i++) {
		if((fp = fopen(argv[i], "r")) == NULL) {
			fprintf(stderr, "Error open file: %s\n", argv[i]);
			return 2;
			}
			c = getc(fp);
			while (c != EOF) {
				putc(c, stdout);
				c = getc(fp);
			}
		fclose(fp);
	}
	return 0;
}
