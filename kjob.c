#include "headers.h"

void kjob(char pwcom[1024][1024],int num)
{
    if(num != 3) {printf("shell : Invalid number of arguments\n"); return;}
    int jobnum = atoi(pwcom[1]);
    int signalno = atoi(pwcom[2]);
    int flag =0;
    for(int i=0;i<process_count;i++)
    {   
        if(back_proc[i].pronum==jobnum){
            if(back_proc[i].status==1)
            {
                flag=1;  
                if(kill(back_proc[i].pd,signalno)<0) {perror("Error"); return;}
                back_proc[i].status = 0;
                if((i)==process_count) curr_bg_count--;
                break;
        // curr_bg_count--;
            }
            // else{
            //     printf("The process with given jobnumber does not exist\n");
            // }
        }
    }
    if(flag==0) printf("The process with given jobnumber deos not exist\n");
}

void overkill(int num)
{
    if(num!=1) {printf("shell : too many arguments\n"); return;}
    for(int i=0;i<process_count;i++)
    {
        if(back_proc[i].status==1)
        {
            if(kill(back_proc[i].pd,SIGKILL)<0) {perror("ERROR"); return;}
            back_proc[i].status =0;
        }
    }
    curr_bg_count =0;
}