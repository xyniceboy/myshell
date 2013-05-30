#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<assert.h>


#define MAXLINE 4096

char * getUsrName(){
    char * usrName;
    usrName = getenv("USER");

    return usrName;
}

void  getSimpleHostName(char * simpleHostName){
    
    char * ps1, *ps2;

    ps1 = ps2 = simpleHostName;

    while(*ps1++ != '\0')
      if (strcmp(ps1, "."))
        ps2 = ps1;
    *ps2 = '\0';

//    return hostName;
}

char * getHostName(){
    char * hostName, *simpleHostName;

    hostName = (char *)malloc(MAXLINE);
    //strcpy(hostName, simpleHostName);
    simpleHostName = hostName;
    if(gethostname(hostName, MAXLINE))
      perror("getHostName");
    else{
        
        getSimpleHostName(hostName);
//        printf("%s \n", hostName);
        return hostName;
    }
}

char *getPwd(){
    char *pwd, *shortPwd;
    char *saveptr, *tmp;

    pwd = get_current_dir_name(); 
    tmp = pwd;

    tmp = strtok_r(pwd, "/", &saveptr);
    while(tmp = strtok_r(NULL, "/", &saveptr)){
        shortPwd = tmp;
    }

    free(pwd);
    return shortPwd;
}

void show(){
    char *shortPwd, *hostName ,*usrName;
    
    shortPwd = getPwd();
    hostName = getHostName();
    usrName = getUsrName();

  printf("[%s@%s %s]", usrName, hostName, shortPwd);

    free(hostName);
}

void setup(){
	signal(SIGINT,SIG_IGN);  //ignore ctrl+c
	signal(SIGQUIT,SIG_IGN); //ignore \+ctrl
}

void getcmd (char *buf ,char **args){
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

void do_cd(char *argv){
	assert(argv);
	char *dirtmp;

	if(argv == NULL || strcmp(argv, "~") == 0){
		dirtmp = getenv("HOME");
		if(!dirtmp){
			perror("HOME not set");
			exit(1);
		}
		chdir(dirtmp);	
    }else{
		dirtmp = argv;
		if(chdir(dirtmp) != 0){
			perror("wrong file or dir");
			exit(1);
		}
    }
}

int main(int argc, char * argv[]){
	char buf[MAXLINE];
	pid_t pid;
	int status;
	char * args[64];
	
    show();
	setup();

	while(fgets(buf,MAXLINE,stdin) != NULL) {
        if(buf[strlen(buf) - 1]='\n'){
            buf[strlen(buf) - 1]=0;
        }
        getcmd(buf, args);
        
//        printf("%s\n", *args);
//        printf("%s\n", *(args+1));  // need to:  ls -al, then can ture!
//        printf("%x\n", args);
        
        if(!strcmp(*args, "exit")){
            exit(EXIT_SUCCESS);
        }else if(!strcmp(*args, "cd")){
            do_cd(*(args+1));
            show();
            continue;
        }
        
        if((pid = fork())<0){
			printf("fork error");
		}else if(pid == 0){
			execvp(*args,args);
			printf("couldn't execute: %s\n",buf);
            show();
        }
	   	if(pid = waitpid(pid, &status, 0))
          show();
	}
	exit(0);
}
