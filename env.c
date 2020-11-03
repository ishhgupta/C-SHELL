#include "headers.h"

void set(char args[1024][1024],int num)
{
    // printf("num is %d\n",num);
    if(num == 1 ) printf("setenv: Too few arguments\n");
    else if(num >3) printf("setenv: Too many argumetns\n");
    else if(num == 2) { if(setenv(args[1],"",1)<0) perror("err");}
    else{
        if(setenv(args[1],args[2],1)<0) perror("err");
    }    
}

void unset(char args[1024][1024],int num)
{
    if(num==1) printf("unsetenv: Too few arguments\n");
    else if(num >2) printf("unseten: Too many arguments\n");
    else{
        if(unsetenv(args[1])<0) perror("err");
    }
} 