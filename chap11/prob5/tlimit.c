#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int pid;
void alarmHandler();

int main(int argc, char *argv[])
{
	int child, status, limit;
	signal(SIGALRM, alarmHandler);
	sscanf(argv[1], "%d",&limit);
	alarm(limit);

	pid = fork();
	if (pid == 0) {
		execvp(argv[2],&argv[2]);
		fprintf(stderr, "%s:실행 불가\n",argv[1]);
	} else {
		child = wait(&status);
		printf("[%d] 자식 프로세스 %d 종료 \n",getpid(), child);
	}
}
void alarmHandler(int signo)
{
	printf("[알람] 자식 프로세스 %d 시간 초과\n");
	kill(pid, SIGINT);
}
