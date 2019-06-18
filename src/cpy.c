/*******************************************************/
/*file name : cpy.c,cpy.h                              */
/*made by   : sup                                      */
/*date      : 2019.06.17                               */
/*This function is to copy file or directory.          */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

#include "cpy.h"
#include "cdr.h"
#include "mkr.h"
#define MAX_PATH 1024

int cpy(char * comm[MAX_PATH],int argc)
{
    int fd1, fd2, i=0;

    int flag_d=0;
    int flag_r=0;

    if(argc > 4){
        fprintf(stderr, "사용법: %s [OPTION] file1 file2 \n", comm[0]);
        return 0;
    }

    //option check
    if(comm[1][0]=='-'){
        while(comm[1][i++]!='\0'){
            if(comm[1][i]=='d') flag_d=1; 
            if(comm[1][i]=='r') flag_r=1;
        }
        //error
        if(flag_d==0 && flag_r==0)
        {
            printf("you can use d,r option.\n");
            printf("usage : cpy [OPTIOM] file1 file2\n");
            return 0;
        }

        if(flag_r==1)
        {
            //mov-d
            if(flag_d==1) {
                printf("mov-d\n");
                return 0;
            }
            //mov
            else{
                printf("mov\n");
                return 0;
            }
        //cpy -d
        }else{
            //유무 확인
            if((fd1=open(comm[2], O_RDONLY))==-1){
                perror(comm[2]);
                return 0;
            }
            if(checkFile(comm[2])!=2){
                printf("this is not directory\n");
                return 0;
            }

            //기존 이름 확인
            if(access(comm[3],0)==0){
                if(checkFile(comm[3])!=2){
                    printf("this is not directory\n");
                    return 0;
                }
                //물어본 후 복사
                char ans[2];
                printf("There is same name directory here.\nWould you like to continue?(y/n) ");
                while(1){
                    scanf("%s",&ans);
                    getchar();
                    if(!strcmp(ans,"n")) return 0;
                    else if(!strcmp(ans,"y")) {
                        //del
                        dirCpy(comm[2],comm[3]);
                        return 0;
                    }
                    else printf("you only answer y or n.\n");    
                }

                //아니면 -> 새로생성
            }else
            {
                char * a[2];
                a[0]="mkr";
                a[1]=comm[3];
                mkr(a,2);

                //복사
                dirCpy(comm[2], comm[3]);
            }
        }

        //not option
    }else{
        if((fd1=open(comm[1], O_RDONLY))==-1){
            perror(comm[1]);
            return 0;
        }


        if( checkFile(comm[1])==2){
            printf("only file name, this is directory\n");
            return 0;
        }

        //file2가 존재한다면
        if(access(comm[2],0)==0){

            if(checkFile(comm[2])==2){
                //file2가 dir라면 dir 밑에 복사
                char * a[2];
                a[0]="cdr";
                a[1]=comm[2];
                cdr(a);
                openCpy(fd1, fd2, comm[1]);
                a[1]="..";
                cdr(a);
                return 0;

            }else{
                //같은 이름 파일 존재할 경우
                char ans[2];
                printf("There is same name file here.\nWould you like to continue?(y/n) ");
                while(1){
                    scanf("%s",&ans);
                    getchar();
                    if(!strcmp(ans,"n")) return 0;
                    else if(!strcmp(ans,"y")) {
                        openCpy(fd1, fd2, comm[2]);
                        return 0;
                    }
                    else printf("you only answer y or n.\n");    
                }
            }
        }
        else openCpy(fd1, fd2, comm[2]);
    }
    return 0;
}

//file2 open 후 복사
int openCpy(int fd1, int fd2, char * comm){
    char * buf;
    buf = (char*)malloc(sizeof(char)*MAX_PATH);

    if((fd2=open(comm,O_WRONLY|O_CREAT|O_TRUNC,0644))==-1){
        printf("something wrong. can't open file");
        return 0;
    }

    while(read(fd1, buf, 1)){
        write(fd2, buf, 1);
    }
    free(buf);

    return 0;
}

//dir 복사
int dirCpy(char * comm1, char * comm2){
    DIR * dir = NULL;
    struct dirent *dir_entry=NULL;

    dir= opendir(comm1);

    if(NULL != dir){
        while((dir_entry = readdir(dir)!=NULL)){
            if(!strcmp(dir_entry->d_name,".") || !strcmp(dir_entry->d_name,".."))
                continue;
            
            if(checkFile(dir_entry->d_name)==2){
               char * a[4];
               a[0]="cpy";
               a[1]="-d";
               a[2]=dir_entry->d_name;
               a[3]=dir_entry->d_name;
            }
            else{
                char * a[3];
                a[0]="cpy";
                a[1]=dir_entry->d_name;
                a[2]=comm2;
                cpy(a,3);
            }
            
        }
        return 0;
    }
    printf("dirCpy()\n");
    return 0;
}

//dir인지 아닌지 검사
int checkFile(char * comm){
    struct stat st;
    if(stat(comm,&st)<0){
        printf("stat error\n");
        return 0;
    }

    if(S_ISDIR(st.st_mode)) return 2;

    return 0;
}
