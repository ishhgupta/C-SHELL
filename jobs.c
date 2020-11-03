#include "headers.h"

void jobs(int num)
{
    if(num>1) {printf("jobs: too many arguments"); return;}
    int ind =0;   //
    // printf("process count %d\n",process_count);
    for(int i=0;i<process_count;i++)
    {
        // printf("HEllO : in jobs\n");
        if(back_proc[i].status==1)
        {
            ind ++;   //
            char sfile[4096];
            sprintf(sfile,"/proc/%d/stat",back_proc[i].pd);
            FILE *fd;
            fd = fopen(sfile,"r");
            if (fd == NULL) back_proc[i].status = 0;
            else if (fd!=NULL)
            {
                char state;
                fscanf(fd, "%*d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d", &state);
                fclose(fd);
                char status_name[500];
                if(state == 'T' || state == 't') strcpy(status_name,"Stopped");
                else  strcpy(status_name,"Running");
                printf("[%d]",back_proc[i].pronum);
                // printf("[%d]",ind);
                printf(" %s %s [%d]\n",status_name,back_proc[i].name,back_proc[i].pd );
            }
        }
    }
}