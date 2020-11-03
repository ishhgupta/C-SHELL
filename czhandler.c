#include "headers.h"

void ctrlc_handler()
{
    // int abc =2;
    if(getpid()!=shellid) return;
    if(fore_proc.status==1)
    {
        if(kill(fore_proc.pd,SIGINT)<0) {perror("error"); };
        // printf("Exited\n");
        fore_proc.status = 0;
    }
    else{
        printf("\n");
        fflush(stdout);
        prompt();
    }
    signal(SIGINT,ctrlc_handler);
    fflush(stdout);
}

void ctrlz_handler()
{
    // if(getpid()!=shellid) return;
    // if(fore_proc.status==1)
    // {
    //     // kill(fore_proc.pd,SIGTTIN);
    //     // kill(fore_proc.pd,SIGTSTP);
    //     fore_proc.status=0;
    //     curr_bg_count++;
    //     back_proc[process_count].status=1;
    //     back_proc[process_count].pd = fore_proc.pd;
    //     strcpy(back_proc[process_count].name,fore_proc.name);
    //     back_proc[process_count].pronum = curr_bg_count;
    //     process_count++;
    //     printf("\n[%d] Stopped %s\n",curr_bg_count,fore_proc.name);
    //     // return;
    // }
    
    //     fflush(stdout);
 
    signal(SIGTSTP,ctrlz_handler);
    // return;
}