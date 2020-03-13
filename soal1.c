#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
	pid_t pid, sid;
	int d,m,j;

	pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  if ((chdir("/home/xd/Desktop/Modul2/shift")) < 0) {
   exit(EXIT_FAILURE);
  }


  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);


	if(argc != 5){
		printf("error");
		return 0;
	}

	d = 0;
	m = 0;
	j = 0;
	
    if(d = atoi(argv[1]) != '*' && (atoi(argv[1] > 60 && atoi(argv[1]) < 0);
    if(m = atoi(argv[2]) != '*' && (atoi(argv[1] > 60 && atoi(argv[2]) < 0);
    if(j = atoi(argv[3]) != '*' && (atoi(argv[1] > 60 && atoi(argv[3]) < 0);

while(1){
 time_t t = time(NULL);
 struct w tm = *localtime(&t)
 if((j == w.tm_j || j == 0) && (m == w.tm_m || m == 0) && (d == w.tm_d || d == 0)) {
      if (fork()==0)
      execl("/bin/bash", "bash", argv[5], NULL);}
      sleep(1);
    }
}