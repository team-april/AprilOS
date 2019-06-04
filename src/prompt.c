/*******************************************************/
/*file name : prompt.c                                 */
/*made by   : jun                                      */
/*date      : 2019.06.03                               */
/*This file is show prompt and current directory      */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "prompt.h"

#define MAX_PATH 100

void prompt()
{
    char * buff;
    char * print_buff;
    int checkslash=0;
    int j=0;
    buff = (char*) malloc(sizeof(char)*MAX_PATH);
    print_buff = (char*) malloc(sizeof(char)*MAX_PATH);

    /* getcwd function is return current directory */
    /* char *getcwd(char *buf, size_t size)        */
    /* error return -1                             */
    getcwd(buff,MAX_PATH); 

    for(int i=0;i<MAX_PATH;i++)
    {
       if(buff[i] == '/' && checkslash < 4)
           checkslash++;
       if(checkslash == 4)
       {
           print_buff[j]=buff[i];
           j++;
       }
    }
    printf("[ ~%s ] A)> ",print_buff);

    free(buff);
    free(print_buff);
}
