#include "headers.h"

void curr_path_display()
{
    char actual_path[FILENAME_MAX];
    char tilda[] = "~";
    getcwd(actual_path,sizeof(actual_path));
    if(strcmp(homdir,actual_path)==0) strcpy(display_path,tilda);
    else if(strlen(actual_path)<strlen(homdir)) strcpy(display_path,actual_path);
    else
    {
        int ind,flag; //if 1-equal, if 0 not same
        char temp[FILENAME_MAX]=" ";
        for(int i=0;i<strlen(actual_path);i++)
        {
            if(actual_path[i]==homdir[i]) {
                char ch=actual_path[i];
                flag=1; strcat(temp,&ch);
            }
            else{ind = i;flag =0; break;}
        }
        if(strcmp(temp,homdir)==0)
        {
            strcpy(display_path,tilda);
            for(int i=ind;i<strlen(actual_path);i++)
            {
                char ch = actual_path[i];
                strcat(display_path,&ch);
            }
        }
        else strcpy(display_path,actual_path);
    } 
}
void prompt()
{ 
    curr_path_display();
    getlogin_r(username,256);
    gethostname(hostname,256);
    printf("<%s%s@%s:%s%s%s%s>","\x1B[0;32m",username,hostname,"\x1B[0m","\x1B[0;34m",display_path,"\x1B[0m");
}