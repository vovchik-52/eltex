#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_NAME "/queue_POSIX"

int main() {
    mqd_t mq = mq_open(QUEUE_NAME, O_RDWR);
    char buffer[1024] = {0};
    mq_receive(mq, buffer, sizeof(buffer), NULL);
    printf("%s\n", buffer);
    strcpy(buffer, "Hello");
    mq_send(mq, buffer, strlen(buffer)+1, 1);
    mq_close(mq);
    return 0;
}