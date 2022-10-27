#include "sys/types.h"
#include "sys/stat.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"

int main(int argc,char *argv[])
{
    pid_t pid = fork(); // 创建子进程

    if (pid == 0)
    {
        // 子进程
        char *argv_[] = {"ls","-a"};
        execlp("ls",argv_,NULL);
    }

    return 0;
}