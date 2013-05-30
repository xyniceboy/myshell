#include<ctype.h>
#include<stdio.h>

int main(){
    char *s = "hello 1 world";
    if(!isalpha(*s))
       printf("%c \n", *s); 
    while(*s++ != '\0'){
      if (!isalpha(*s))
        printf("%c \n" ,*s);
      else {
        ;
      }
    }
    return 0;
}
