#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

int main(void){
    
    FILE *fp;

    fp = fopen("test.txt", "w"); //can write this file, if not exit, create it
    assert(fp);
    fclose(fp);

    fp = fopen("noexitfile.txt", "r"); //only read this file, if not exit, open faild
    assert(fp);
    fclose(fp);

    return 0;
}
