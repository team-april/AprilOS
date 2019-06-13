/*******************************************************/
/*file name : mkr.c,mkr.h                              */
/*made by   : jun                                      */
/*date      : 2019.06.13                               */
/*This function is create directory                    */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "mkr.h"
#define MAX_PATH 1024

void mkr(char * comm[MAX_PATH],int argc)
{
    char * buff;
    buff = (char*)malloc(sizeof(char)*MAX_PATH);
    if(argc > 3 || argc == 1) // command error
    {
        mkrMAN();
    }
    else if (argc == 3) // create dir with option
    {
        //option
    }
    else // Create dir
    {
        if(mkdir(comm[1],0755)!=0)
        {
            if(access(getcwd(buff,MAX_PATH),0)==0)
                printf("Already \"%s\" is exists.\n",comm[1]);
            else
                printf("Can not mkr");
        }
    }

    free(buff);
}

void mkrMAN()
{

}

