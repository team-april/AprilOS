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

#define MAX_COMMAND 1024


// 받은 문자열 쪼개기
void strDis()
{
    char str[MAX_COMMAND];
    fgets(str,MAX_COMMAND,stdin);
    char* comm[100] = {NULL,};
    int i=0;

    char *temp = strtok(str," ");
    while(temp != NULL)
    {
        comm[i] = temp;
        i++;
        temp = strtok(NULL, " ");
    }

    command(comm, i);
}


//comm 을 받아서 문자에 맞게 명령어 실행
void command(char * comm[MAX_COMMAND], int i)
{
    if(!strcmp(comm[0],"cdr")){
        if(i==1) cdr(NULL);
        else if(i != 2 )
            printf("usage : cdr <dir name | path> \n");
        else
            cdr(comm);
    }
}

void cdr(char * comm[MAX_COMMAND])
{
    printf("comm1:%s\n",comm[1]);
    if(chdir(comm[1]))
        printf("error");
    else
