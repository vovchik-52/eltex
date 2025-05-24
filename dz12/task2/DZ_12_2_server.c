#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define FIFO "./FIFO"
int main(){
    unlink(FIFO);
    mkfifo(FIFO,0600);
    int fd_server_writh = open(FIFO,O_WRONLY);
    char buf_server[]="Hi!";
    size_t write_serwer = write(fd_server_writh,buf_server,sizeof(buf_server));
    //sleep(30);
    close(fd_server_writh);
    exit(EXIT_SUCCESS);
}