/*******************************************************/
/*file name : sls.c                                    */
/*made by   : sup                                      */
/*date      : 2019.06.12                               */
/*This file is about command of sls.                   */
/*sls can print present directory.                     */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#include <grp.h>
#include <pwd.h>
#include <time.h>
#include "sls.h"

#define MAX_COMMAND 1024

// sls 명령어
int sls(char * comm[MAX_COMMAND],int argc){

    DIR *dp;
    char *dir=(char *)malloc(sizeof(char)*100);
    struct dirent *d;
    struct stat st;
    char path[BUFSIZ+1];

    int i = 0;
    int flag_l=0;
    int flag_t=0;
    int flag_a=0;

    //option check
    if(argc>1 && comm[1][0]=='-'){
        while(comm[1][i++]!='\0'){
            if(comm[1][i]=='l') flag_l=1; 
            if(comm[1][i]=='t') flag_t=1;
            if(comm[1][i]=='a') flag_a=1;
        }
        if(flag_l==0 && flag_t==0 && flag_a==0 )
        {
            printf("you can use l,a,t option.\n");
            printf("usage : sls [OPTIOM] <PATH>\n");
            return 0;
        }
        if(dirErrorCheck(comm, dir, argc, 2)==-1) return 0;
    }else{
        if(dirErrorCheck(comm, dir, argc, 1)==-1) return 0;
    }

    //directory check
    if((dp=opendir(dir))==NULL){
        perror(dir);
        return 0;
    }

    //print directory
    while((d=readdir(dp)) !=NULL)
    {
        sprintf(path, "%s/%s",dir, d->d_name);
        if(lstat(path, &st)<0){
            perror(path);
            return 0;
        }
        else if(d->d_name[0]=='.' && flag_a == 0){
            continue;
        }
        else{
            if(flag_l==1) sls_l(path, d->d_name, &st);
            if(flag_t==1) sls_t(path, d->d_name, &st);
            sls_(path, d->d_name, &st);
            if(flag_l==1 || flag_t==1)printf("\n");
        }
    }

    if(flag_l==0 && flag_t==0 )printf("\n");
    
    free(dir);

    return 0;

}

int dirErrorCheck(char * comm[MAX_COMMAND], char * dir, int argc, int ck){
    if(argc == ck){
        strcpy(dir,".");
    }
    else if(argc > ck+1){
        printf("usage : sls [OPTIOM] <PATH>\n");
        return -1;

    } 
    else{
        strcpy(dir,comm[ck]);
    }

    return 0;
}


void sls_l(char *pathname, char *file, struct stat *st)
{
    printf("%c%s ",type(st->st_mode), perm(st->st_mode));
    printf("%3u ",st->st_nlink);
    printf("%6s %6s ",getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
    printf("%9ld   ",st->st_size);
}

void sls_t(char *pathname, char *file, struct stat *st)
{
    printf("%.12s   ", ctime(&st->st_mtime)+4);
}


void sls_(char *pathname, char *file, struct stat *st)
{
    printf("%.15s    ", file);
}

//파일 상태
char type(mode_t mode)
{
    if(S_ISREG(mode))
        return('-');
    if(S_ISDIR(mode))
        return('d');
    if(S_ISCHR(mode))
        return('c');
    if(S_ISBLK(mode))
        return('m');
    if(S_ISLNK(mode))
        return('b');
    if(S_ISLNK(mode))
        return('l');
    if(S_ISFIFO(mode))
        return('p');
    if(S_ISSOCK(mode))
        return('s');
}

//권한 체크
char* perm(mode_t mode)
{
    int i;
    static char perms[10]="---------";

    for(int i = 0 ; i<3; i++)
    {
        if(mode & (S_IRUSR>>i*3))
            perms[i*3]='r';
        if(mode&(S_IWUSR>>i*3))
            perms[i*3+1]='w';
        if(mode&(S_IXUSR>>i*3))
            perms[i*3+2]='x';
    }
    return(perms);
}
