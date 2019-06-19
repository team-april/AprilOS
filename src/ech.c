/*******************************************************/
/*file name : ech.c ech.h                              */
/*made by   : jun                                      */
/*date      : 2019.06.19                               */
/*This file is showing input text or save file.        */
/*******************************************************/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "ech.h"
#include "MAN.h"
#define MAX_COMMAND 1024



int ech(char *comm[MAX_COMMAND],int argc)
{
    if(argc == 1)
    {
        echMAN();
        return 0;
    }
    int i=1;
    int flag = 0;
    
    while(1)
    {
        if(comm[i] == NULL)
            break;
        if(!strcmp(comm[i],">>"))
        {
            flag = 1;
            int fd;
            if((fd=open(comm[i+1],O_WRONLY|O_CREAT|O_APPEND,0644))<0)
            {
                printf("\"%s\" read error",comm[i+1]);
                break;
            }
            for(int j=1;j<i;j++)
            {
                write(fd,comm[j],strlen(comm[j]));
                write(fd," ",1);
            }
            write(fd,"\n",1);
            close(fd);
            break;
        }
i++;
    }

    i=1;
    if(flag == 0){
        while(1)
        {
            if(comm[i]==NULL)
                break;
            printf("%s ",comm[i]);
            i++;
        }
    }
    if(flag == 0)
        printf("\n");

}
