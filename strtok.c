#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){

    char s[] = "ab-cd:de:gh:mnpe:ger-tu";
    char *delim="-:";

    char *p;

    printf("%s\n", strtok(s,delim));
    p = strtok(NULL, delim);
    while((p=strtok(NULL, delim)))
      printf("%s\n", p);
    return 0;
}
