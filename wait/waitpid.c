#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"
#include "sys/wait.h"

int main(int argv, char *argc[])
{
    int i = 0;
    pid_t pid, wpid;

    for (i=0; i < 5; i++)
    {
        if (fork() == 0) // 子进程才执行 
        {
            if (i == 2)
                pid = getpid(); // 获取当前子进程的id
            break; // 子进程本身不再创建子进程
        }
    }

    if (i==5)
    {
        sleep(5);
        wpid = waitpid(pid, NULL, WNOHANG); // 指定一个进程回收
        if (wpid == -1){
            perror("waitpid error!");
            exit(1);
        }
        printf("parent process, waiting %d\n ",pid);
    }
    else{ // 子进程，从break跳出
        sleep(i);
        printf("%dth child process, pid=%d\n",i+1,getpid());
    }
}