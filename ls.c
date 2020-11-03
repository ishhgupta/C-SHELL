#include "headers.h"
void display_dir(int l,int a,char path[4096],int dir_num)
{
    struct dirent *de;
    DIR *dr = opendir(path); 
    if(dir_num>1) printf("%s:\n",path);
    if(l!=1)
    {
        while ((de = readdir(dr)) != NULL) 
        {
            if(a==0)
            {
                if(de->d_name[0]!='.') 
                printf("%s  ", de->d_name);
            }
            else 
                printf("%s  ", de->d_name); 
        }
        printf("\n");
    }
    else if(l==1)
    {
        while ((de= readdir(dr))!=NULL)
        {
            if(a==0 && de->d_name[0] == '.') continue;

            char file_path[4096];
            strcpy(file_path,path);
            strcat(file_path,"/");
            strcat(file_path,de->d_name);

            struct stat sfile;
            stat(file_path,&sfile);

            printf((S_ISDIR(sfile.st_mode)) ? "d" : "-");
            printf((sfile.st_mode & S_IRUSR) ? "r" : "-");
            printf((sfile.st_mode & S_IWUSR) ? "w" : "-");
            printf((sfile.st_mode & S_IXUSR) ? "x" : "-");
            printf((sfile.st_mode & S_IRGRP) ? "r" : "-");
            printf((sfile.st_mode & S_IWGRP) ? "w" : "-");
            printf((sfile.st_mode & S_IXGRP) ? "x" : "-");
            printf((sfile.st_mode & S_IROTH) ? "r" : "-");
            printf((sfile.st_mode & S_IWOTH) ? "w" : "-");
            printf((sfile.st_mode & S_IXOTH) ? "x" : "-");
            printf(" %ld", sfile.st_nlink);
            struct group *gr;
            struct passwd *usr;
            usr=getpwuid(sfile.st_uid);
            gr=getgrgid(sfile.st_gid);
            
            char tim[200] = "";
            time_t present = time(NULL);
            struct tm tmfile, prestim;
            localtime_r(&present, &prestim);
            localtime_r(&sfile.st_mtime, &tmfile);
            if (tmfile.tm_year == prestim.tm_year)
                strftime(tim, sizeof(tim), "%b %e %H:%M", &tmfile);
            else
                strftime(tim, sizeof(tim), "%b %e  %Y", &tmfile);

            printf(" %s %s %ld\t%s %s\n",usr->pw_name,gr->gr_name,sfile.st_size,tim,de->d_name);
        }       
    }
    closedir(dr);
}
void ls(char args[1024][1024],int num)
{
    char dirname[4096];
    int l=0,a=0,dir_num=0,act_dir = 0;
    for(int i=1;i<num;i++)
    {
        if(args[i][0]=='-')
        {
            for(int j=1;j<strlen(args[i]);j++)
            {
                if(args[i][j]=='l') l=1;
                else if(args[i][j]=='a') a=1;
                else{ printf("only l and a flags are allowed\n"); return;}
            }
        }
        if(args[i][0]!='-') 
        { 
            char error[4096+100];
            DIR *d1 = opendir(args[i]);
            if(d1==NULL) 
            {
                strcpy(error,"ls: cannot access '");
                strcat(error,args[i]);
                strcat(error,"'");
                perror(error);
            }
            else act_dir ++; 
            closedir(d1);   
            dir_num++;
        }
    }
    for(int i=1;i<num;i++)
    {
        if(args[i][0]!='-')
        {
            if(args[i][0]=='~')
            {
                strcpy(dirname,homdir);
                display_dir(l,a,dirname,dir_num);
            }
            else
            { 
                DIR *d2 = opendir(args[i]);
                if(d2!=NULL)
                {
                    // strcpy(dirname,args[i]);
                    display_dir(l,a,args[i],dir_num);
                }
                closedir(d2);       
            }           
        }
    }
    if(act_dir==0) {dir_num =1; display_dir(l,a,".",dir_num); return;}
}