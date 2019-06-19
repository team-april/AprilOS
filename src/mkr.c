/*******************************************************/
/*file name : mkr.c,mkr.h                              */
/*made by   : jun                                      */
/*date      : 2019.06.13                               */
/*            2019.06.19                               */
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
    int  i = 0;
    int k=0;
    int flag=0;
    int pflag=0;
    int mflag=0;
    int count=1; // option count
    int dirLog=0;
    char * mkrTEMP[MAX_COMMAND]={'\0'};

    buff = (char*)malloc(sizeof(char)*MAX_PATH);

    if(argc > 3 || argc == 1) // command error
        mkrMAN();
    else // Create dir
    {
        while(1) // option check
        {
            if(comm[1][0] == '-')
            {
                if(comm[1][count]=='m')
                    mflag=1;
                else if(comm[1][count] == 'p')
                    pflag=1;
                else if(comm[1][count] == ' ')
                    break;
                else
                    mkrMAN();
            }
            else
                break;
            count++;
        }

        i=mkrDis(comm,mkrTEMP,k);            

        for(int j=0; j<i;j++)
        {
            dirLog++;
            if(mflag == 0)
            {
                if(access(mkrTEMP[j],0) == -1 && j<i-1)
                {
                    printf("\"%s\" is not found\n",mkrTEMP[j]);
                    flag = 1;
                    break;
                }
                else
                    chdir(mkrTEMP[j]);
            }
            else
            {
                if(access(mkrTEMP[j],0) == -1 && j<i-1)
                {
                    mkdir(mkrTEMP[j],0755);
                    chdir(mkrTEMP[j]);
                }
                else
                    chdir(mkrTEMP[j]);
            }
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

        if(pflag != 1)
            for(int j=0; j<dirLog-1;j++)
                chdir("..");
        else 
            chdir(mkrTEMP[i-1]);
        free(buff);
        return 0;
    }
}


int mkrDis(char * comm[MAX_COMMAND],char * mkrTEMP[MAX_COMMAND],int i)
{
    if(comm[1][0] != '-')
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
    else if(comm[1][0] == '-')
    {
        if(strlen(comm[2])!=0){
            char *temp = strtok(comm[2],"/");
            while(temp != NULL)
            {
                mkrTEMP[i] = temp;
                i++;
                temp = strtok(NULL, "/");
            }
        }
    }
    return i;
}
