/*******************************************************/
/*file name : command.c                                */
/*made by   : jun,sup                                  */
/*date      : 2019.06.11                               */
/*This file is distinguished input command.            */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "command.h"
#include "sls.h"
#include "cdr.h"
#include "mkr.h"
#include "chm.h"
#include "pdr.h"
#include "shw.h"

#define MAX_COMMAND 1024

// 받은 문자열 쪼개기
void strDis()
{
    char str[MAX_COMMAND];
    fgets(str,MAX_COMMAND,stdin);
    if(strlen(str)!=0)
        str[strlen(str)-1]='\0';
    char* comm[MAX_COMMAND] = {NULL,};
    int i=0;

    if(strlen(str)!=0 && str[0] != ' '){
        char *temp = strtok(str," ");
        while(temp != NULL)
        {
            comm[i] = temp;
            i++;
            temp = strtok(NULL, " ");
        }
        command(comm, i);
    }
}

//comm 을 받아서 문자에 맞게 명령어 실행
void command(char * comm[MAX_COMMAND], int i)
{
    if(!strcmp(comm[0],"cdr"))
    {
        cdr(comm);
    }
    else if(!strcmp(comm[0],"sls"))
    {
        sls(comm,i);
    }
    else if(!strcmp(comm[0],"chm"))
    { 
        chm(comm,i);
    }
    else if(!strcmp(comm[0],"mkr"))
    {
        mkr(comm,i);
    }
    else if(!strcmp(comm[0],"pdr"))
    {
        pdr(i);
    }
    else if(!strcmp(comm[0],"shw"))
    {
        shw(comm,i);
    }
    else if(!strcmp(comm[0],"cdr"))
    {}
    else if(!strcmp(comm[0],"cdr"))
    {}
    else if(!strcmp(comm[0],"cdr"))
    {}
    else if(!strcmp(comm[0],"cdr"))
    {}
    else if(!strcmp(comm[0],"cdr"))
    {}
    else if(!strcmp(comm[0],"cdr"))
    {}
    else if(!strcmp(comm[0],"cdr"))
    {}
    else if(!strcmp(comm[0],"cdr"))
    {}
    else
    {
        printf(" \"%s\" is not command\n",comm[0]);
    }

}
