#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>




int main(int argc, char *argv[]) {
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }


  if(argc != 5){
    printf("Error");
    return 0;
  }



  d = 0;
  m = 0;
  j = 0;
  
//Detik
	if(isalpha(argv[1][0])){
    		printf("Int boi kalo ga *");
  	}else if(atoi(argv[1]) < 0 || atoi(argv[1]) > 59){
    		printf("Detik cuma 0 - 59");
	}else if(argv[1][0] == '*'){
		d = 0;  	
	}else{
    		d = atoi(argv[1]);
  	}
  
//Menit
  	if(isalpha(argv[2][0])){
    		printf("Int boi kalo ga *");
  	}else if(atoi(argv[2]) < 0 || atoi(argv[2]) > 59){
    		printf("Menit cuma 0 - 59");
	}else if(argv[2][0] == '*'){
		m = 0;
  	}else{
    		m = atoi(argv[2]);
  	}
  
//Jam
  	if(isalpha(argv[3][0])){
    		printf("Int boi kalo ga *");
  	}else if(atoi(argv[3]) < 0 || atoi(argv[3]) > 23){
   		printf("Jam 0 - 23");
	}else if(argv[3][0] == '*'){
		j = 0;
  	}else{
    		j = atoi(argv[3]);
  	}



  while(1) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if((j == tm.tm_hour || j == 0) && (m == tm.tm_min || m == 0) && (d == tm.tm_sec || d == 0)){
      if(fork()==0){
        char *argx[] = {"bash",argv[4], NULL};
        execv("/bin/bash", argx);
      }
    }
    sleep(1);
  }
}

