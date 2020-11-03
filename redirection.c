#include "headers.h"

void redirection(char pwcom[1024][1024],int num)
{
    char infile[1024],outfile[1024];
    int i1=0,i2=0,i3=0;
    int in,out;
    int commlength=2000;
    for(int i=0;i<num;i++)
    {
        if(strcmp(pwcom[i],"<")==0){
            strcpy(infile,pwcom[i+1]);
            commlength = i;
            i1 = i;
            
        }
        if(strcmp(pwcom[i],">")==0){
            i2 = i;
            if(i<=commlength) commlength = i;
            strcpy(outfile,pwcom[i+1]);
            out = open(outfile, O_TRUNC | O_WRONLY | O_CREAT ,0644);
            close(out);
        }
        if(strcmp(pwcom[i],">>") == 0){
            i3 = i;
            if(i<=commlength) commlength = i;
            out = open(outfile,O_APPEND | O_WRONLY | O_CREAT ,0644);
            close(out);
        }
    }
    // num = commlength;
    char command[1024];
        strcpy(command,pwcom[0]);
        for(int i=1;i<commlength;i++)
        {
            strcat(command," ");
            strcat(command,pwcom[i]);
        }
    // strcat(command[commlength],NULL);
    // command[commlength] = NULL;
    // char *command[1024];
    // for(int i=0;i<commlength;i++)
    // {
    //     strcpy(command,pwcom[i]);
    // }
    // exec_curr_command(command);
    int pid = fork();
    if(pid<0) {printf("Error while forking\n");}
    else if(pid ==0)
    {
        if(i1!=0){
            in = open(infile, O_RDONLY,0644);
            if(in<0){ printf("Error in opening %s file\n",infile); exit(0);}
            else { dup2(in,0); close(in);}
        }
        if(i2>i3)
            out = open(outfile,O_WRONLY | O_CREAT | O_TRUNC,0644);
        else
            out=open(outfile,O_WRONLY | O_CREAT | O_APPEND,0644);
        if(out){
            dup2(out,1);
            close(out);
        }
        exec_curr_command(command);
        exit(0);
    }
    else{
        wait(NULL);
    }
    return;
}