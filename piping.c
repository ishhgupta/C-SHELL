#include "headers.h"

void piping(char comm[])
{
    char pwcom[1024][1024];   //pipe arguments
    for(int i=0;i<1024;i++)  for(int j=0;j<1024;j++) pwcom[i][j] = '\0';
    char* token = strtok(comm,"|");
    int num=0; //num of pipe separated commands
    while (token!=NULL)
    {
        strcpy(pwcom[num],token);
        num++;
        token = strtok(NULL,"|");
    }
    // separated pipe wali commands
    
    int pipe_arr[2],fd =0;
    for(int i=0;i<num;i++)
    {
        pipe(pipe_arr);
        pid_t pid = fork();
        if(pid < 0) perror("error");
        else if(pid == 0)
        {
            dup2(fd,0);
            if(i!=num-1) dup2(pipe_arr[1],1);
            close(pipe_arr[0]);
            exec_curr_command(pwcom[i]);
            exit(1);
        }
        else{
            wait(NULL);
            fd = pipe_arr[0];
            close(pipe_arr[1]);
        }
    }
}