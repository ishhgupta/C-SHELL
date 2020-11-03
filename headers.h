#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>

#define clear() printf("\033[H\033[J")
#define MAXCOM 1024
#define MAXLIST 100

char username[256];
char hostname[256];
char homdir[FILENAME_MAX];
char display_path[FILENAME_MAX];
char prevdir[FILENAME_MAX];

pid_t shellid;
int curr_bg_count;
int process_count;
struct procs{
    pid_t pd;
    int pronum;
    char name[500];
    int status ;  // 1 if still going on , 0 if deleted
};
struct procs back_proc[4096];
struct procs fore_proc;


int exec_curr_command(char comm[]);
void prompt();
void pwd (int num);
void cd(char path[1024][1024],int num);
void echo(char args[1024][1024],int num);
void ls(char args[1024][1024],int num);
void fg_proc(char args[1024][1024],int num);
void bg_proc(char pwcom[1024][1024],int num);
void pinfo(char pwcom[1024][1024],int num);
void child_handler();
void set(char args[1024][1024],int num);
void unset(char args[1024][1024],int num);
void jobs(int num);
void kjob(char pwcom[1024][1024],int num);
void overkill(int num);
void ctrlc_handler();
void ctrlz_handler();
void fg(char pwcom[1024][1024],int num);
void bg(char pwcom[1024][1024],int num);
void redirection(char pwcom[1024][1024],int num);
void piping(char comm[]);