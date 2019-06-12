#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_COMMAND 1024
#define MAX_PATH 1024
#define PATH "/home/jun/AprilOS/usr/bookmark"
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

void OpenBookMark(int bookNum)
{
    FILE *fp;
    char * buff;
    char * print_buff;
    buff = (char*)malloc(sizeof(char)*MAX_COMMAND);
    print_buff = (char*)malloc(sizeof(char)*MAX_COMMAND);
    int checkslash = 0;
    int j=0;
    fp=fopen(PATH, "r");
    fgets(buff,MAX_PATH,fp);
    for(int i=0;i<MAX_PATH;i++)
    {
        if(buff[i] == '/' && checkslash < 2)
            checkslash++;
        if(checkslash == 2)
        {
            print_buff[j]=buff[i];
            j++;
        }
    }
    if(strlen(print_buff)!=0)
        print_buff[strlen(print_buff)-1]='\0';
    printf("%s!\n",print_buff);
    chdir(print_buff);
    fclose(fp);
    free(buff);
    free(print_buff);
}



void SaveBookMark(char *comm[MAX_COMMAND])
{
    FILE *fp;
    char path[MAX_PATH];
    char * buff;
    buff = (char*)malloc(sizeof(char)*MAX_COMMAND);
    getcwd(path,MAX_PATH);
    fp=fopen(PATH, "a");
    fprintf(fp,"%s/%s\n",comm[2],path);
    fclose(fp);
    free(buff);
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

    fp=fopen(PATH, "r");

    printf("==================================\n");
    printf("\t[ Book Mark LIST ]\n");
    printf("==================================\n");
    printf("  BM name | BM PATH\n");
    printf("==================================\n");

    while (fgets(buff, MAX_PATH,fp) != NULL)
    {
        printf(" [%d] %s",i,buff);
        i++;
    }

    fclose(fp);
    free(buff);

}
