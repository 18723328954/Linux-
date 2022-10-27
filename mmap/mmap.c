#include "sys/types.h"
#include "sys/stat.h"
#include "sys/mman.h"
#include "fcntl.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "error.h"
#include "pthread.h"
#include "string.h"

// 创建文件到内存的映射
// void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
// addr：映射首地址，一般为NULL     length：共享内存映射区大小      prot：内存映射的读写属性        flgas：共享属性
// return：共享内存区的首地址

int main(int argc, char *argv[])
{
    char *p = NULL;
    int fd;

    fd = open("testmmap.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open error!");
        exit(1);
    }

    lseek(fd, 10, SEEK_END);
    write(fd, "\0", 1);

    int len_file = lseek(fd, 0, SEEK_END);
    
    p = mmap(NULL, len_file, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
        perror("mmap error!");
        exit(1);
    }

    strcpy(p, "hello mmap");
    printf("---%s\n", p);

    int ret = munmap(p, len_file);
    if (ret ==-1)
    {
        perror("mnumap error!");
        exit(1);
    }
}