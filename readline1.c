#include <stdio.h>

#include <stdlib.h>

#include <readline/readline.h>

int main(int argc, char **argv){
    char *buf = NULL;
    
    while (1) {
        buf = readline(">");
        if (buf != NULL) {
            printf("get: %s\n", buf);
            add_history(buf);
            if (strcmp(buf, "quit") == 0){
                free(buf);
                break;
            } else
              free(buf);
        }  
    }  
    return 0;
}
