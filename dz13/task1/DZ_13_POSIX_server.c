#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_NAME "/queue_POSIX"

int main() {
    mqd_t mq;
    unsigned int prioritu;
    struct mq_attr attr ;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // Максимальное количество сообщений
    attr.mq_msgsize = 100; // Максимальный размер сообщения
    attr.mq_curmsgs = 0;
    mq_unlink(QUEUE_NAME);
    mq = mq_open(QUEUE_NAME, O_CREAT|O_RDWR, 0777, &attr);
    char buffer[1024] = {0};
    strcpy(buffer, "HI");
    mq_send(mq, buffer, strlen(buffer)+1, 2);
    while (1)
    {
    mq_receive(mq, buffer, sizeof(buffer), &prioritu)==-1;
    if(prioritu ==1){
        printf("%s\n", buffer);
        break;
    }else if(prioritu ==2){
        mq_send(mq, buffer, strlen(buffer)+1, 2);
        sleep(1);
    }
    }
    mq_close(mq);
    mq_unlink(QUEUE_NAME);
    exit(EXIT_SUCCESS);
}