#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <string.h>
int main(){
    int pipefd[2];
    pid_t pid;
    pipe(pipefd);
    size_t read_buf,writh_buf;
    char buf[1024];
    pid = fork();
    if (pid != 0)
    {
        close(pipefd[0]);
        char temporary_buf[]="Hi!";
        strcpy(buf,temporary_buf);
        writh_buf = write(pipefd[1],buf,sizeof(buf));

    }else{
        close(pipefd[1]);
        read_buf = read(pipefd[0],buf,sizeof(buf));
        printf("%s\n",buf);
    }
    exit(EXIT_SUCCESS);
}