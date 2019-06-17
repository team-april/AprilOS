/*******************************************************/
/*file name : mkr.c,mkr.h                              */
/*made by   : jun                                      */
/*date      : 2019.06.17                               */
/*This function is change permisions.                  */
/*******************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>


#include "MAN.h"
#include "chm.h"
#define MAX_COMMAND 1024
#define MAX_PATH 1024


void chm(char * comm[MAX_COMMAND],int argc)
{
    char *stop;

    if(argc > 4 || argc == 1 || argc == 2)
        chmMAN();
    else if(argc == 3 )
    {
        if(comm[1] == "-")
            chmMAN();
        else // basic function
        {
            int mod = strtol(comm[2],&stop,8); // string -> 8.int 
            if(chmod(comm[1],mod) == -1)
                printf("Permission error!\n");
        }
    }
    else //option
    {

    }
}
