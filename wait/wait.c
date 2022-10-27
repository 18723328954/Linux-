#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"
#include "sys/wait.h"

/*
 * 函数原型：pid_t wait(int *status)
 * 等待该进程的全部子进程结束后再启动父进程的运行
 * status：用于保存子进程结束情况
 * return：成功返回回收子进程的id，失败-1
*/

int main(int argv,char *argc[])
{
    int status;
    pid_t pid, wpid;

    pid = fork(); // 创建子进程，父进程返回>0，子进程返回0，失败-1

    if (pid == 0)
    {
        // 子进程
        printf("It is child process, my parent id is %d, going to sleep 10s\n",getppid());
        sleep(10); // 睡10s
        printf("child process die!\n");
    }
    else if (pid > 0)
    {
        // 父进程
        wpid = wait(&status); // 指针变量修改status的值 
        if (wpid == -1)
        {
            perror("wait error!");
            exit(1);
        }
        printf("parent process finish\n");
    }
    else{
        perror("fork error!");
        exit(1);
    }
}