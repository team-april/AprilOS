/*******************************************************/
/*file name : cdr.c,cdr.h                              */
/*made by   : jun                                      */
/*date      : 2019.06.12                               */
/*This function is change directory and bookmark       */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_COMMAND 1024
#define MAX_PATH 1024
#define PATH "/home/sup/AprilOS/usr/bookmark"
#define HOME_PATH "/home/jun/AprilOS/src"

#include "cdr.h"

void cdr(char * comm[MAX_COMMAND])
{
    if(comm[1]==NULL)
    {
        if(chdir(HOME_PATH) == -1)
            fprintf(stderr,"\"%s\" is not open\n",comm[1]);
    }
    else if(comm[1][0] == '-')
    {
        if(comm[1][1] == 'w' )
            if(comm[2]==NULL)
                cdrMAN();
            else
                SaveBookMark(comm);
        else if(comm[1][1] == 'r' )
            if(comm[2]==NULL)
                cdrMAN();
            else
                OpenBookMark();
        else if(comm[1][1] == 'b')
            BookMarkList(comm);
        else if(comm[1][1] == '\0')
            cdrMAN();
    }
    else // cdr <dir>
    {
        int flag = access(comm[1],0);
        if(flag==0)
        {
            if(chdir(comm[1]) == -1)
                fprintf(stderr,"\"%s\" is not open\n",comm[1]);
        }
        else if(flag == -1)
            printf("\"%s\" not found\n",comm[1]);
    }
}

void OpenBookMark(char * comm[MAX_COMMAND])
{
    FILE *fp;
    char * buff;
    char * print_buff;
    char * buff_temp;
    buff = (char*)malloc(sizeof(char)*MAX_COMMAND);
    buff_temp = (char*)malloc(sizeof(char)*MAX_COMMAND);
    print_buff = (char*)malloc(sizeof(char)*MAX_COMMAND);
    int checkslash = 0;
    int j=0;
    int searchNUM=1;


    fp=fopen(PATH,"r");
    while (fgets(buff, MAX_PATH,fp) != NULL)
    {
        if(buff!=NULL){
            for(int i=0;i<MAX_PATH;i++)
            {
                if(buff[i] != '/' )
                {
                    buff_temp[j]=buff[i];
                    j++;
                }
                else 
                    break;
            }
            if(strcmp(comm[2],buff_temp))
            {
                searchNUM++;
            }
            else
            {
                break;
            }
        }
        j=0;
        checkslash=0;
        memset(buff_temp,'\0',MAX_COMMAND);
    }
    fclose(fp);

    
    fp=fopen(PATH, "r");
    for(int i=0;i<searchNUM;i++)
    {
        memset(buff,'\0',MAX_COMMAND);
        fgets(buff,MAX_PATH,fp);
    }
    

    memset(buff_temp,'\0',MAX_COMMAND);
    j=0;

    for(int i=0;i<=MAX_PATH;i++)
    {
        if(buff[i] == '/' && checkslash < 1)
            checkslash++;
        else if(checkslash == 1)
        {
            buff_temp[j]=buff[i];
            j++;
        }
    }

    
    if(strlen(buff_temp)!=0)
        buff_temp[strlen(buff_temp)-1]='\0';
    chdir(buff_temp);
    fclose(fp);
    free(buff);
    free(buff_temp);
}



void SaveBookMark(char *comm[MAX_COMMAND])
{
    FILE *fp;
    char path[MAX_PATH];
    char * buff;
    char * buff_temp;
    int checkslash=0,j=0;
    int flag = 0;
    buff = (char*)malloc(sizeof(char)*MAX_COMMAND);
    buff_temp = (char*)malloc(sizeof(char)*MAX_COMMAND);
    getcwd(path,MAX_PATH);
    fp=fopen(PATH,"r");
    fgets(buff,MAX_PATH,fp);
    while (fgets(buff, MAX_PATH,fp) != NULL)
    {
        if(buff!=NULL){
            for(int i=0;i<MAX_PATH;i++)
            {
                if(buff[i] != '/' && checkslash < 2)
                {
                    buff_temp[j]=buff[i];
                    j++;
                }
                else if(buff[i] == '/')
                    checkslash++;
                if(checkslash == 2)
                    break;
            }
            if(!strcmp(comm[2],buff_temp))
            {
                flag = 1;
                break;
            }
            j=0;
            checkslash=0;
            memset(buff_temp,'\0',MAX_COMMAND);
        }
    }
    fclose(fp);
    if(flag == 1) 
        printf(" \"%s\" already exists.\n",buff_temp);
    else
    {
        fp=fopen(PATH, "a");
        fprintf(fp,"%s/%s\n",comm[2],path);
        fclose(fp);
    }
    free(buff);
    free(buff_temp);
}
void cdrMAN()
{
    printf(" usage : cdr [-option] < dir neme | bookmark num >\n");
    printf(" -option :\n");
    printf("\t -w : cdr -w <BOOK MARK NAME>\n");
    printf("\t    This option is save bookmark path.\n");
    printf("\t -r : cdr -r <BOOK MARK NAME>\n");
    printf("\t    This option is load bookmark.\n");
    printf("\t -b : cdr -b\n");
    printf("\t    This option is showing bookmark list.\n");
}


void BookMarkList(char *comm[MAX_COMMAND])
{

    FILE *fp;
    char * buff;
    int i=1;
    buff = (char*)malloc(sizeof(char)*MAX_COMMAND);

    fp=fopen(PATH, "a");
    fclose(fp);

    fp=fopen(PATH,"r");

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("\t\t\t[ Book Mark LIST ]  \n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("  BM name | BM PATH\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

    while (fgets(buff, MAX_PATH,fp) != NULL)
    {
        if(buff != NULL && i == 1)
            ;
        else if(buff != NULL && i != 1)
            printf(" [%d] %s",i-1,buff);
        i++;
    }
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    fclose(fp);
    free(buff);

}
