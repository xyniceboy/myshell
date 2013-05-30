#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<assert.h>

void do_cd(char *argv[]){
  assert(argv);
	char *dirtmp;

	//if(argv[1] == NULL || strcmp(argv[1], "~") == 0){
	if(strncmp(argv[1], "~", 1) == 0){
		dirtmp = getenv("HOME");
		if(!dirtmp)
		{
			perror("HOME not set");
			exit(1);
		}

		chdir(dirtmp);	
	}else{
		dirtmp = argv[1];
		if(chdir(dirtmp) != 0){
			perror("wrong file or dir");
			exit(1);
		}
	}
}

void show(){
	printf("myshell-->");
}

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
		//printf("*buf = %x\n", *buf);
        
        *args++ = buf; 

		//printf("*args = %s\n", **args);
		while((* buf!='\0')&&(* buf!=' ')&&(* buf!='\t')&&(*buf!='\n'))
			buf++;
	}
	*args = '\0';
}

#define MAXLINE 4096
void getcmd (char*,char * *);

int main(int argc, char * argv[])
{
	char buf[MAXLINE];
	pid_t pid;
	int status;
	char * args[64];
	void setup();
	
    show();

	setup();

	while(fgets(buf,MAXLINE,stdin) != NULL) {
		if(buf[strlen(buf) - 1]='\n'){
          buf[strlen(buf) - 1]=0;
        }
        getcmd(buf, args);
        
/*        if(strcmp(*args, "exit") == 0){
			exit(EXIT_SUCCESS);
		}else if(strcmp(*args, "cd") == 0){
			do_cd(args+1);
		}else{
            execvp(*args, args);
			//do_cmd(arglist);			// do it
		}
*/
        printf("%s\n", *args);
        printf("%s\n", *(args+1));  // need to:  ls -al, then can ture!
        printf("%x\n", args);

        if((pid = fork())<0){
			printf("fork error");
		}else if(pid == 0){
            if(!strcmp(*args, "exit")){
                exit(EXIT_SUCCESS);
            }else if(!strcmp(*args, "cd")){
                do_cd(args);
            }else{
			execvp(*args,args);
			printf("couldn't execute: %s\n",buf);
			exit(0);
            }
		}
		
	   	if(pid = waitpid(pid, &status, 0))
		//	printf("waitpid error");
          printf("myshell--> ");
	}
	exit(0);
}
