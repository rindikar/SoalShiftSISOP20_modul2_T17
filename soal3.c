#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(){
pid_t child_id1, child_id2;

int proses;
child_id1 = fork();

	if (child_id == 0)	{
	sleep(3);
	char *argv[3] = {"mkdir", "sedaap", NULL};
	execv("/bin/mkdir", argv);
	  }
	else {
	child_id2 = fork();
	if (child_id2 == 0)	{
	char *argv[3] = {"unzip", "jpg.zip", NULL};
	execv("/usr/bin/unzip", argv);
	else {
	char *argv[3] = {"mkdir", "indomie", NULL};
	execv("/bin/mkdir", argv);
	while ((wait($proses)) > 0);
	     }
}
}