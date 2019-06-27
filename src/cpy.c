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
#define HOME_PATH "/home/sup/AprilOS/src"

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
                printf("There is same name directory here.\n");
                if(sameCheck()==1){
                    dirCpy(comm[2],comm[3]);
                }
                //아니면 -> 새로생성
            }else
            {
                mkdir(comm[3],0776);

                //복사
                dirCpy(comm[2], comm[3]);
            }
        }

        //not option
    }else{

        char *path = (char*)malloc(sizeof(char)*MAX_PATH);
        strcpy(path,".");
        strcat(path,"/");
        strcat(path,comm[1]);
        if((fd1=open(path, O_RDONLY))==-1){
            perror(path);
            return 0;
        }
        free(path);

        if(checkFile(comm[1])==2){
            printf("only file name, this is directory\n");
            return 0;
        }

        //file2가 존재한다면
        if(access(comm[2],0)==0){

            if(checkFile(comm[2])==2){
                //file2가 dir라면 dir 밑에 복사
                openCpy(fd1, fd2, comm[1], comm[2]);
                return 0;

            }else{
                //같은 이름 파일 존재할 경우
                printf("There is same name file here.\n");
                if(sameCheck()==1) openCpy(fd1,fd2, comm[2], '\0');
            }
        }
        else openCpy(fd1, fd2, comm[2], '\0');
    }
    return 0;
}

//file2 open 후 복사
int openCpy(int fd1, int fd2, char * comm1, char * comm2){
    char * buf;
    buf = (char*)malloc(sizeof(char)*MAX_PATH);
    int i =0;
    char *path = (char*)malloc(sizeof(char)*MAX_PATH);
    char *temp = strtok(comm1,"/");
    char **file = (char**)malloc(sizeof(char)*MAX_PATH);

    while(temp != NULL)
    {
        file[i] = temp;
        i++;
        temp = strtok(NULL,"/");
    }


    if(comm2==NULL) sprintf(path,"./%s",comm1);
    else sprintf(path,"./%s/%s",comm2, file[i-1]);
    if(access(path,0)==0){
        printf("There is same name file here.\n");
        if(sameCheck()==0) return 0;
    }

    if((fd2=open(path,O_WRONLY|O_CREAT|O_TRUNC,0644))==-1){
        printf("something wrong. can't open file\n");
        return 0;
    }

    while(read(fd1, buf, 1)){
        write(fd2, buf, 1);
    }
    free(buf);
    free(path);
    free(temp);
    free(file);
    return 0;
}

//dir 복사
int dirCpy(char * comm1, char * comm2){
    DIR * dir = NULL;
    struct dirent *dir_entry=NULL;
    char *preDir = (char*)malloc(sizeof(char)*MAX_PATH);
    char *path1 = (char*)malloc(sizeof(char)*MAX_PATH);
    strcpy(path1,".");
    strcat(path1,"/");
    strcat(path1,comm1);
    dir = opendir(path1);
    strcpy(preDir,"./");
    strcat(preDir,comm2);
    if(NULL != dir){
        while((dir_entry = readdir(dir))!=NULL){
            if(!strcmp(dir_entry->d_name,".") || !strcmp(dir_entry->d_name,".."))
                continue;
            char *path2 = (char*)malloc(sizeof(char)*MAX_PATH);
            sprintf(path2,"./%s/%s",comm1, dir_entry->d_name);
            if(checkFile(path2)==2){
                char * a[4];
                a[0]="cpy";
                a[1]="-d";
                a[2]=path2;
                sprintf(preDir,"./%s/%s",comm2,dir_entry->d_name);
                a[3]=preDir;
                cpy(a,4);
            }
            else{
                char * a1[3];
                a1[0]="cpy";
                a1[1]=path2;
                a1[2]=comm2;
                cpy(a1,3);
            }

            free(path2);

        }
        return 0;
    }
    free(path1);
    free(preDir);
    return 0;
}

//dir인지 아닌지 검사
int checkFile(char * comm){
    struct stat st;
    if(stat(comm,&st)<0){
        printf("check : stat error\n");
        return 0;
    }

    if(S_ISDIR(st.st_mode)) return 2;

    return 0;
}

int sameCheck(){
    char ans[2];
    printf("Would you like to continue?(y/n)");
    while(1){
        scanf("%s",ans);
        getchar();
        if(!strcmp(ans,"n")) return 0;
        else if(!strcmp(ans,"y")) {
            return 1;
        }
        else printf("you only answer y or n.\n");    
    }
}
