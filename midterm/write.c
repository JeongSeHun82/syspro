#include <stdio.h>

int main(char* argv[])
{
	FILE *fp;

	fp = fopen(argv[1], "w");
	printf("%-7s", "input");

	fclose(fp);
	return 0;
}
