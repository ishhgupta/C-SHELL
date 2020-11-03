#include "headers.h"

void fg(char pwcom[1024][1024],int num)
{
    if(num!=2) {printf("Invalid number of arguments\n"); return;}
    int jobnum = atoi(pwcom[1]);
    int flag=0;
    for(int i=0;i<process_count;i++)
    {
        if(back_proc[i].pronum==jobnum && back_proc[i].status==1)
        {
            flag=1;
            int pid,stat; pid = back_proc[i].pd;
            back_proc[i].status = 0;
            strcpy(fore_proc.name,back_proc[i].name);
            printf("%s\n",fore_proc.name);
            fore_proc.pd = pid;
            fore_proc.status = 1;
            curr_bg_count--;
            signal(SIGTTOU,SIG_IGN);
            tcsetpgrp(0,pid);
            kill(pid,SIGCONT);
            waitpid(pid,&stat, WUNTRACED);
            tcsetpgrp(0,getpid());
            signal(SIGTTOU,SIG_DFL);
            break;
        }
    }
    if(flag==0) printf("shell: fg: %d: no such job\n",jobnum);
}
