/*******************************************************/
/*file name : nfl.c nfl.h                              */
/*made by   : jun                                      */
/*date      : 2019.06.19                               */
/*This command creat new file and modificate timeinfo  */
/*******************************************************/
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "nfl.h"
#include "MAN.h"
#define MAX_COMMAND 1024



int nfl(char *comm[MAX_COMMAND],int argc)
{
    struct stat st;
    if(argc == 1)
    {
        nflMAN();
        return 0;
    }

    int tflag=0; 
    int fd;

    if(comm[1][0] == '-')
    {
        if(!strcmp(comm[1],"-t"))
            tflag = 1;
        else
            nflMAN();
    }

    if(tflag == 0)
    {
        if((fd=open(comm[1],O_WRONLY|O_CREAT,0644))<0)
            printf("\"%s\" read error",comm[1]);
    }    
    else
    {
        if((fd=open(comm[2],O_WRONLY|O_CREAT,0644))<0)
            printf("\"%s\" read error",comm[2]);
        if(stat(comm[2],&st)==-1)
            return 0;
        st.st_ctime = atof(comm[3]);
        st.st_atime = atof(comm[3]);
        printf("%f\n",atof(comm[3]));

    }

}
