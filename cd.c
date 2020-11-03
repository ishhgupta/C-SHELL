#include "headers.h"

void cd(char path[1024][1024],int num)
{
    char temp[FILENAME_MAX];
    char curr_dir[FILENAME_MAX];
    getcwd(curr_dir,sizeof(curr_dir));

    if(num ==2 && path[1][0]=='-') {chdir(prevdir); printf("%s\n",prevdir);} 
    else if(num==1 || (path[1][0]=='~')){
        chdir(homdir);
    }
    else if(num == 2){
        strcpy(temp,path[1]);
        if(chdir(temp)!=0) perror("cd");
    }
    else if(num>2) printf("shell: cd: too many arguments\n");

    if(strcmp(curr_dir,prevdir)!=0){
	strcpy(prevdir,curr_dir);
    }
    // printf("current using cd :%s\n",t); 
}
void pwd (int num)
{
    char temp[FILENAME_MAX];
    getcwd(temp,sizeof(temp));
    printf("%s\n",temp);  // doubt regarding more than 1 arg ..no error in
                            //in real shell
}