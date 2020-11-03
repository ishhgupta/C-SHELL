#include "headers.h"

void child_handler()
{
    pid_t pid;
    int stat;
    pid = waitpid(-1,&stat,WNOHANG | WUNTRACED);

    for(int i=0;i<process_count;i++)
    {
        if(pid == back_proc[i].pd && WIFEXITED(stat))
        {
            int exit_stat = WEXITSTATUS(stat);
            if(exit_stat == 0) printf("\n%s with pid %d exited normally.\n",back_proc[i].name,pid);
            else printf("\n %s with pid %d exited abnormally with status %d\n",back_proc[i].name,pid,exit_stat);
            back_proc[i].status = 0;
            if(i==process_count-1) curr_bg_count--;
            // curr_bg_count--;
            prompt();
            fflush(stdout);
        }
    }
}
void fg_proc(char pwcom[1024][1024],int num)
{
    char *args[1024]; for(int i=0;i<1024;i++) args[i] = NULL;
    for(int i=0;i<num;i++)
    {
        // printf("%s ",pwcom[i]);
        args[i]=pwcom[i];
    }
    pid_t child_pid;
    child_pid = fork();
    if(child_pid == 0) 
    {
        // printf("in child\n");
        if(execvp(args[0],args)<0){
            printf("%s: command not found\n",args[0]);
            exit(0);
            // return;
        }
        // exit(0);
    }
    else{
        fore_proc.pd = child_pid;
        fore_proc.status = 1;
        char proc_name[500];
        strcpy(proc_name,args[0]);
        for(int i=1;i<num;i++)
        {
            strcat(proc_name," ");
            strcat(proc_name,args[i]);
        }
        strcpy(fore_proc.name,proc_name);
        // printf("in foreground\n");
        pid_t tpid = waitpid(-1,NULL,WUNTRACED);
    }
}

void bg_proc(char pwcom[1024][1024],int num)
{
    // printf("background\n");
    char* args[1024];
    for(int i=0;i<num;i++)
        args[i]=pwcom[i];
    pid_t child_pid;
    child_pid = fork();
    setpgid(0,0);
    if(child_pid == 0) 
    {
        if(signal(SIGTSTP,ctrlz_handler));
        if(execvp(args[0],args)<0){
            // perror("error");
            printf("%s: command not found\n",args[0]);
            exit(0);
            return;
        }
        exit(0);
    }
    else{
        curr_bg_count++;
        printf("[%d] %d\n",curr_bg_count,child_pid);
        back_proc[process_count].pronum = curr_bg_count;
        char proc_name[500];
        strcpy(proc_name,args[0]);
        for(int i=1;i<num;i++)
        {
            strcat(proc_name," ");
            strcat(proc_name,args[i]);
        }
        strcpy(back_proc[process_count].name,proc_name);
        // printf("proc name %s\n",back_proc[process_count].name);
        back_proc[process_count].pd = child_pid;
        back_proc[process_count].status = 1;
        process_count++;
    }
}

