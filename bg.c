#include "headers.h"

void bg(char pwcom[1024][1024],int num)
{
    if(num != 2) {printf("Invalid number of arguments\n"); return ;}
    int jobnum = atoi(pwcom[1]);
    int flag=0;
    for(int i=0;i<process_count;i++)
    {
        if(back_proc[i].pronum==jobnum && back_proc[i].status==1)
        {
            flag=1;
            kill(back_proc[i].pd,SIGTTIN);
            kill(back_proc[i].pd,SIGCONT);
            break;
        }
    }
    if(flag==0) printf("shell: bg: %d: no such job\n",jobnum);
}