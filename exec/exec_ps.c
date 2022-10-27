#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"

// 查看系统属性并写入文件

int main(int argc,char *argv[])
{
    int fd; // 文件描述符

    fd = open("ps.txt",O_WRONLY | O_CREAT | O_TRUNC,0644); // 打开或者创建文件
    if (fd < 0)
    {
        perror("file open error!");
        exit(1);
    }

    dup2(fd,STDOUT_FILENO); // 将fd文件重定向为输出文件

    pid_t son = fork(); // 创建子进程

    if (son == 0){
        char *argv_[] = {"ps","ax"};
        execlp("ps",argv_,NULL); // 子进程执行
    }

    close(fd);

    return 0;
}