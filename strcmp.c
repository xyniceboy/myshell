#include<string.h>
#include<stdio.h>

int main(){
    char *s = "hell.word";
    char *ps1, *ps2;
    //ps2 = NULL; 
    ps1 = ps2 = s;

    while(*ps1++ != '\0')  { 
            //printf("%c\n", *ps1);
        //if (strncmp(ps1 ,".", 1) == 0)
        if (*ps1 == ".")
        {  
            printf("%c\n", *ps1);
            printf("%s\n", s);
            ps2 = ps1;
        }
        *ps2 = '\0';
    }
    printf("%s \n", s);
    return 0;
}
