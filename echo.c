#include "headers.h"

void echo(char args[1024][1024],int num)
{
    if(num<2)
    {
        printf("\n"); return;
    }
    else
    {
        for(int i=1;i<num;i++)
        {
            printf("%s ",args[i]);
        }
        printf("\n");
    }
}