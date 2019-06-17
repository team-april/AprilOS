/*******************************************************/
/*file name : mkr.c,mkr.h                              */
/*made by   : jun                                      */
/*date      : 2019.06.13                               */
/*This function is create directory                    */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "mkr.h"
#include "MAN.h"
#define MAX_PATH 1024
#define MAX_COMMAND 1024


int mkr(char * comm[MAX_PATH],int argc)
{
    char * buff;
    int  i=0;
    int flag=0;
    buff = (char*)malloc(sizeof(char)*MAX_PATH);
    char * mkrTEMP[MAX_COMMAND]={'\0'};
    int dirLog=0;

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
        if(comm[1] != "-")
        {
            if(strlen(comm[1])!=0){
                char *temp = strtok(comm[1],"/");
                while(temp != NULL)
                {
                    mkrTEMP[i] = temp;
                    i++;
                    temp = strtok(NULL, "/");
                }
            }
        }
        for(int j=0; j<i;j++)
        {
            dirLog++;
            if(access(mkrTEMP[j],0) == -1 && j<i-1)
            {
                printf("\"%s\" is not found\n",mkrTEMP[j]);
                flag = 1;
                break;
            }
            else
                chdir(mkrTEMP[j]);
        }
        if(flag == 0)
        {
            if(mkdir(mkrTEMP[i-1],0755)!=0)
            {
                if(access(getcwd(buff,MAX_PATH),0)==0)
                    printf("Already \"%s\" is exists.\n",mkrTEMP[i-1]);
                else
                    printf("Can not mkr");
            }
        }
        for(int j=0; j<dirLog-1;j++)
        {
            chdir("..");
        }
        free(buff);
        return 0;
    }
}


