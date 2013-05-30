
#include<stdio.h>

int main(void) {
    char * argv[] = {"ls", "-al","/etc/passwd",0};

    execvp("ls", argv);

    return 0;
}
