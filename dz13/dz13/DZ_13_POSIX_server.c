#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define QUEUE_NAME "/queue_NAME_POSIX"
#define QUEUE_ALL "/queue_ALL_POSIX"
#define QUEUE_MESS "/queue_MESS_POSIX"

pthread_mutex_t info_mutex = PTHREAD_MUTEX_INITIALIZER;

struct all_info info;
struct all_info {
    char buf_name[100];
    char buf_onemess[100];
    char buf_allmess[100];
};

void *thread_name_first_input(void *arg){

    mqd_t name,send_all;
    struct mq_attr attr ;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // Максимальное количество сообщений
    attr.mq_msgsize = 100; // Максимальный размер сообщения
    attr.mq_curmsgs = 0;
    name = mq_open(QUEUE_NAME, O_CREAT|O_RDWR, 0777, &attr);
    send_all = mq_open(QUEUE_ALL, O_CREAT|O_RDWR, 0777, &attr);
    while (1)
    {
        char buf_help[100];
        mq_receive(name,buf_help,sizeof(buf_help),NULL);
        pthread_mutex_lock(&info_mutex);
        strcat(info.buf_name,buf_help);
        strcat(info.buf_name,"\n");
        pthread_mutex_unlock(&info_mutex);
        mq_send(send_all,info.buf_name,strlen(info.buf_name)+1,1);
        mq_send(send_all,info.buf_allmess,strlen(info.buf_allmess)+1,2);
    }
    
    }
void *thread_all_send(void *arg){

    mqd_t mess;
    struct mq_attr attr ;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // Максимальное количество сообщений
    attr.mq_msgsize = 100; // Максимальный размер сообщения
    attr.mq_curmsgs = 0;
    mess = mq_open(QUEUE_MESS, O_CREAT|O_RDWR, 0777, &attr);
    mqd_t send_all = mq_open(QUEUE_ALL, O_RDWR);
    while (1)
    {
        char buf_help[100];
        mq_receive(mess,buf_help,sizeof(buf_help),NULL);
        pthread_mutex_lock(&info_mutex);
        strcat(info.buf_allmess,buf_help);
        strcat(info.buf_allmess,"\n");
        pthread_mutex_unlock(&info_mutex);
        mq_send(send_all,info.buf_name,strlen(info.buf_name)+1,1);
        mq_send(send_all,info.buf_allmess,strlen(info.buf_allmess)+1,2);
    }
    
    }


int main() {
    mq_unlink(QUEUE_NAME);
    mq_unlink(QUEUE_ALL);
    mq_unlink(QUEUE_MESS);
    pthread_t ptr_name_first_input;
    pthread_t ptr_all;
    pthread_create(&ptr_name_first_input,NULL,thread_name_first_input,NULL);
    pthread_create(&ptr_all,NULL,thread_all_send,NULL);
    sleep(300);



   exit(EXIT_SUCCESS);
}