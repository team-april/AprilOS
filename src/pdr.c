/*******************************************************/
/*file name : pdr.c,pdr.h                              */
/*made by   : jun                                      */
/*date      : 2019.06.17                               */
/*This function is showing current  directory.         */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "MAN.h"

#define MAX_PATH 1024

void pdr(int argc)
{

    char *buff;
    buff = (char*)malloc(sizeof(char)*MAX_PATH);
    if(argc == 1)
    {
        if(getcwd(buff,MAX_PATH)==NULL)
            printf("not working pdr\n");
        else
            printf("%s\n",buff);
    }
    else
        pdrMAN();

    free(buff);
}
