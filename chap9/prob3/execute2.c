#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Parent process start\n");
    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr,"First fair");
        exit(1);
    }

	if (fork() == 0) {
		execl("/bin/date", "date", NULL);
		fprintf(stderr,"Second fair");
		exit(2);
	}

	if (fork() == 0) {
		execl("/bin/ls", "ls", "-l", NULL);
		fprintf(stderr,"Third fair");
		exit(3);
	}
    printf("Parent process end\n");
}
