#include "headers.h"

void pinfo(char pwcom[1024][1024],int num)
{
    pid_t pid;
    if(num==1) {
        pid = getpid();
    }
    else if(num==2)
        pid = atoi(pwcom[1]);
    // struct stat sts;
    char path[1024];
    sprintf(path,"/proc/%d/stat",pid);
    FILE* fp = fopen(path,"r");
    if(!fp){
        perror("Error: Process doesn't exist\n");
        return;
    } 
    printf("pid -- %d\n",pid);
    char status_code; 
    long unsigned int memory;
    fscanf(fp, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &status_code, &memory);

    printf("Process Status -- %c\n",status_code);
    printf("memory -- %lu\n",memory);

    char con[1000];
    sprintf(path,"/proc/%d/exe",pid);
    int len = readlink(path,con,1050);
    if(len < 0) perror("Error while reading");
    else 
    {
        con[len] = '\0';
        printf("Executable Path -- %s\n",con);
    } 
}