#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define FIFO "./FIFO"
int main(){
    int fd_user_read = open(FIFO,O_RDONLY);
    char buf_user[1024];
    size_t read_user =read(fd_user_read,buf_user,sizeof(buf_user)) ;
    printf("%s\n",buf_user);
    close(fd_user_read);
    unlink(FIFO);
    exit(EXIT_SUCCESS);
}