#include "headers.h"

int checkredir(char pwcom[1024][1024],int num)
{
    for(int i=0;i<num;i++)
    {
        if(strcmp(pwcom[i],"<")==0 || strcmp(pwcom[i],">")==0 || strcmp(pwcom[i],">>")==0)
         return 1;
    }
    return 0;
}

int checkingpipe(char comm[]){
    for(int i=0;i<strlen(comm);i++)
    {
        if(comm[i]=='|') return 1;
    }
    return 0;
}

int exec_curr_command(char comm[])
{  
    char pwcom[1024][1024];
    for(int i=0;i<1024;i++)  for(int j=0;j<1024;j++) pwcom[i][j] = '\0';
    char* token = strtok(comm," \n\r\t");
    int num=0; //num of arguments in a given command
    while (token!=NULL)
    {
        strcpy(pwcom[num],token);
        num++;
        token = strtok(NULL," \n\r\t");
    }
    
    if(checkredir(pwcom,num)==1) {redirection(pwcom,num); return 0;}
    int ifand = 0; //for background process checking if & is present
    if(strcmp(pwcom[num-1],"&")==0) ifand =1 ;
    if(num<1) return 0;
    else if(strcmp(pwcom[0],"cd")==0 && ifand==0){
        cd(pwcom,num);
    }
    else if(strcmp(pwcom[0],"pwd")==0 && ifand==0){
        pwd(num);
    }
    else if(strcmp(pwcom[0],"echo")==0 && ifand==0){
        echo(pwcom,num);
    }
    else if(strcmp(pwcom[0],"ls")==0 && ifand==0){
        ls(pwcom,num);
    }
    else if(strcmp(pwcom[0],"pinfo")==0 && ifand == 0){
        pinfo(pwcom,num);
    }
    else if(strcmp(pwcom[0],"setenv")==0 && ifand==0){
        set(pwcom,num);
    }
    else if(strcmp(pwcom[0],"unsetenv")==0 && ifand==0){
        unset(pwcom,num);
    }
    else if(strcmp(pwcom[0],"jobs")==0 && ifand==0){
        jobs(num);
    }
    else if(strcmp(pwcom[0],"kjob")==0 && ifand ==0){
        kjob(pwcom,num);
    }
    else if(strcmp(pwcom[0],"overkill")==0 && ifand ==0){
        overkill(num);
    }
    else if(strcmp(pwcom[0],"fg")==0 && ifand ==0){
        fg(pwcom,num);
    }
    else if(strcmp(pwcom[0],"bg")==0 && ifand ==0){
        bg(pwcom,num);
    }
    else if(strcmp(pwcom[0],"quit")==0 && ifand ==0){
        // printf("\n");
        // exit(0);
        if(num>1) printf("bash: too many arguments\n");
        else
        {
            // printf("hiiii\n");
            overkill(1);
            // exit(0);
            return 1;
        }
    }
    else if(ifand==1)
    {
        num--;
        bg_proc(pwcom,num);
    }
    else if(pwcom[0]!="\n") fg_proc(pwcom,num);
    // else if(pwcom[0]==)
    return 0;
}
 
int main()
{
    clear();
    getcwd(homdir,sizeof(homdir)); //homdirectory wrt this shell
    getcwd(prevdir,sizeof(prevdir));
    shellid =  getpid();
    curr_bg_count = 0;
    process_count=0;
    while (1)
    {
        signal(SIGCHLD,child_handler);
        signal(SIGINT,ctrlc_handler);
        signal(SIGTSTP,ctrlz_handler);

        prompt();
    
        // TAKING INPUT OF A COMMAND
        size_t bytes_read;
        size_t size = 0;
        char *read_comm = NULL;
        read_comm = (char *)malloc(size*sizeof(char));
        bytes_read = getline(&read_comm,&size,stdin); 
        //handling ctrl-D(it works as a null character)
        if(strcmp(read_comm,"\0")==0) {
            printf("\n");
            // exit(0);
            return 0;
        }
         //separating different commands in a single line using strtok and ; delimiter
        char comm_arr[MAXLIST][MAXCOM] ;
        char* token1 = strtok(read_comm,";");
        int nofcom=0;
        while (token1 != NULL)
        {
            strcpy(comm_arr[nofcom],token1);
            nofcom++;
            token1 = strtok(NULL,";");
        }  
        //running loop for working a given commands separated by ';'     
        for(int i=0;i<nofcom;i++)
        {
            // checking piping
            if((checkingpipe(comm_arr[i]))==1) {piping(comm_arr[i]); continue;}
            if((exec_curr_command(comm_arr[i]))==1) { free(read_comm); exit(0);} 
        }
        free(read_comm);       
    }
    return 0;
}
