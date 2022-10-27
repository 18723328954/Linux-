#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "error.h"
#include "pthread.h"

/*
 * int pipe(int fd[2])
 * 管道函数，用于在该进程申请一个管道
 * fd：文件描述符的数组，fd[0]表示读，fd[1]表示写，只能打开一个
 * return：-1表示创建失败
 */

/*
 * int dup2(int fd1, int fd2)
 * 重定向操作，将fd2指向fd1
 * fd1表示旧文件描述符，fd2表示新文件描述符
 * return：-1表示失败
 */

int main(int agrc, char *argv[])
{
    int fd[2];          // 管道参数数组
    int ret = pipe(fd); // 创建管道
    pid_t pid = fork(); // 创建子进程

    if (ret == -1)
    {
        perror("pipe error!");
        exit(1);
    }

    if (pid == -1)
    {
        perror("fork error!");
        exit(1);
    }
    else if (pid > 0)
    {
        // 父进程用于写内容到管道
        close(fd[0]);               // 关闭管道读端
        dup2(fd[1], STDOUT_FILENO); // 标准输出重定向到fd[1]中，即输出不显示
        char *agrv_[] = {"ls"};
        execlp("ls", agrv_, NULL); // 父进程执行ls
        sleep(1);
        perror("exclp error!");
        exit(1);
    }
    else if (pid == 0)
    {
        // 子进程用于读管道内容到终端
        close(fd[1]);              // 关闭管道写端
        dup2(fd[0], STDIN_FILENO); // 标准输入重定向到fd[2]中
        char *agrv_[] = {"wc", "-l"};
        execlp("wc", agrv_, NULL); // 子进程指向wc -l
        perror("wc error!");
        exit(1);
    }

    return 0;
}