#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>				
#include <string.h> 
#include <wait.h>
#include <sys/stat.h>
#include <unistd.h> 
 

int Status(const char *path)
{
  struct stat pathDir; 
  stat(path, &pathDir);
  return S_ISDIR(pathDir.st_mode); 
} 

int main()
{
	pid_t pidA = fork();  	
	int pidB = fork();   
	int pidC = fork();   
	int status;

if (pidB > 0 && pidC > 0){  
  while ((wait(&status)) > 0); 
  DIR *open;  
  struct dirent *directory; 
  chdir("/home/xd/Desktop/Modul2/shift/");  
  open = opendir(".");
 
	if (open){  
     	  while ((directory = readdir(open)) != NULL){
	    if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0)
	      continue;  
	      if(Status(directory->d_name)){
		if(fork() == 0){  
		  char file[700];
		  sprintf(file,"/home/xd/Desktop/Modul2/shift/%s",directory->d_name);
		  char* move[] = {"mv", file,"/home/xd/Desktop/Modul2/shift/indomie/", NULL};
		        execv("/bin/mv", move);
          		} 
		else{
            	  while ((wait(&status)) > 0); 
            	  if(fork() == 0)
			{
            	  	if(fork() == 0)
			{
            	    	  char cobadulu[700];
            	    	  FILE *file;
		          sprintf(cobadulu,"/home/xd/Desktop/Modul2/shift/indomie/%s/coba1.txt",directory->d_name);
		       	  file = fopen(cobadulu, "w");
		          fclose(file);
		        }
              		else
			{
		           while ((wait(&status)) > 0);
		           sleep(3);
		           char cobalagi[700];
		           FILE *file;
		           sprintf(cobalagi,"/home/umum/Desktop/Modul2/shift/indomie/%s/coba2.txt",directory->d_name);
		           file = fopen(cobalagi, "w");
		           fclose(file);
		           exit(0);
		        } 
            	} 
            	else{
			while ((wait(&status)) > 0);
				      exit(0);
			}
          	} 
        }
        else{
          	while ((wait(&status)) > 0);
          	if(fork() == 0)
			{ 
            	while ((wait(&status)) > 0); 
            	char okeh[700];
            	sprintf(okeh,"/home/xd/Desktop/Modul2/shift/%s",directory->d_name);
            	char* movesedap[] = {"mv", okeh,"/home/umum/Desktop/Modul2/shift/sedaap/", NULL};
            	execv("/bin/mv", movesedap);
          		}
        	}        
      	    } 
    	  } 
	} 
	else if (pidB == 0 && pidC > 0){ 
    		while ((wait(&status)) > 0);
    		if (pidA == 0){
      char *masakindomie[] = {"mkdir", "-p","/home/umum/Desktop/Modul2/shift/indomie", NULL};
      execv("/bin/mkdir", masakindomie); 
    }
    else
{
      while ((wait(&status)) > 0); 
      sleep(5); 
      char *masaksedaap[] = {"mkdir", "-p","/home/umum/Desktop/Modul2/shift/sedaap", NULL}; 
      execv("/bin/mkdir", masaksedaap); 
    }
  } 
	else if (pidB > 0 && pidC == 0)
	{ 
    char* ekstrak[] = {"unzip", "-oq","/home/umum/Desktop/Modul2/shift/jpg.zip", NULL};
    execv("/usr/bin/unzip", ekstrak);
	}
	return 0; 
} 