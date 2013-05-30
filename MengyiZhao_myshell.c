/****************myshell version2*******************/
/**add fucntion :ctrl+c reaction****/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

void setup()
{
  signal(SIGINT,SIG_IGN);  //ignore ctrl+c
	signal(SIGQUIT,SIG_IGN); //ignore \+ctrl
}


void getcmd (char *buf ,char **args)
{
	while(*buf !='\0')
	{
		while((* buf==' ')||(* buf== '\t')||(* buf == '\n'))
			*buf++ = '\0';
		*args++ = buf; 
		
		while((* buf!='\0')&&(* buf!=' ')&&(* buf!='\t')&&(*buf!='\n'))
			buf++;
	}
	*args = '\0';
}

#define MAXLINE 4096
void getcmd (char*,char * *);
int main(void)
{
	char buf[MAXLINE];
	pid_t pid;
	int status;
	char * args[64];
	void setup();
	

	printf("/*****************tip:ctrl+c=stay;ctrl+d=q*******************/\nmyshell-->  ");
	setup();
	while(fgets(buf,MAXLINE,stdin) != NULL) {
		if(buf[strlen(buf) - 1]='\n')
			buf[strlen(buf) - 1]=0;
		
		getcmd(buf, args);
	    
		if((pid = fork())<0){
			printf("fork error");
		}else if(pid == 0){
	//	signal(SIGINT,SIG_DFL);
	//	signal(SIGQUIT,SIG_DFL);

			execvp(*args,args);
			printf("couldn't execute: %s\n",buf);
			exit(0);
		}
		
	   	if(pid = waitpid(pid, &status, 0))
		//	printf("waitpid error");
		printf("myshell--> ");
	}
	exit(0);
}
