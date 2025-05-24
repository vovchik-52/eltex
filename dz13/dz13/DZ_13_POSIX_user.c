#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>

#define QUEUE_NAME "/queue_NAME_POSIX"
#define QUEUE_ALL "/queue_ALL_POSIX"
#define QUEUE_MESS "/queue_MESS_POSIX"

char buffer_name_one_user[100] = {0};
char buffer_name_many_user[100] = {};
char buffer_all[100] = {0};
char buf_help[100]={0};
char buf_input_mess[100]={0};

void draw_menu() {

    static bool ncurses_initialized = false;
    if (!ncurses_initialized) {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        ncurses_initialized = true;
    }

    WINDOW *msg_win = newwin(LINES-5, COLS/2, 0, 1);
    box(msg_win, 0, 0);
    mvwprintw(msg_win, 1, 1, "Messages:\n %s", buffer_all);
    wrefresh(msg_win);
    delwin(msg_win);

    // Правая панель (пользователи)
    WINDOW *users_win = newwin(LINES-5, COLS/2, 0, COLS/2);
    box(users_win, 0, 0);
    mvwprintw(users_win, 1, 1, "Users:\n %s", buffer_name_many_user);
    wrefresh(users_win);
    delwin(users_win);

    // Окно ввода
    WINDOW *input_win = newwin(5, COLS, LINES-5, 0);
    box(input_win, 0, 0);
    mvwprintw(input_win, 0, 0, "Input message: ");
    wrefresh(input_win);
    delwin(input_win);

    refresh();
}
int main() {
   
    mqd_t mq_name = mq_open(QUEUE_NAME, O_RDWR);
    mqd_t mq_all = mq_open(QUEUE_ALL, O_RDWR);
    mqd_t mq_mess = mq_open(QUEUE_MESS, O_RDWR);
   
    unsigned int prioritu;
    int count = 2;
    //char buffer3[100] = {0};
    printf("input name plz \n");
    scanf("%99s",buffer_name_one_user);
    while(getchar() != '\n'); 
    mq_send(mq_name,buffer_name_one_user,strlen(buffer_name_one_user)+1,1);
    
    
    while (count>0)
    {
        mq_receive(mq_all, buf_help, sizeof(buf_help), &prioritu);
        if (prioritu == 1)
        {
            strcat(buffer_name_many_user,buf_help);
            count--;
        }
        else{
            strcat(buffer_all,buf_help);
            
            count--;
        }     
    }
    while(1) {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        draw_menu();
        // Ввод сообщения через ncurses
        WINDOW *input_win = newwin(5, COLS, LINES-5, 0);
        wmove(input_win, 1, 2); // Позиция для ввода
        echo();
        wgetnstr(input_win, buf_input_mess, sizeof(buf_input_mess)-1);
        noecho();
        delwin(input_win);

        // Отправка сообщения
        mq_send(mq_mess, buf_input_mess, strlen(buf_input_mess)+1, 1);

        // Обновление данных
        count = 2;
        while(count > 0) {
            mq_receive(mq_all, buf_help, sizeof(buf_help), &prioritu);
            if(prioritu == 1) strcpy(buffer_name_many_user, buf_help);
            else strcpy(buffer_all, buf_help);
            count--;
        }
    }

    endwin();
    exit(EXIT_SUCCESS);
}