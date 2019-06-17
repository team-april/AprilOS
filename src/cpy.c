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

#include "cpy.h"
#include "cdr.h"
#define MAX_PATH 1024

int cpy(char * comm[MAX_PATH],int argc)
{
    int fd1, fd2;
    char * buf;
    buf = (char*)malloc(sizeof(char)*MAX_PATH);
    struct stat st;

    if(argc > 3){
        fprintf(stderr, "사용법: %s file1 file2 \n", comm[0]);
        return 0;
    }

    if((fd1=open(comm[1], O_RDONLY))==-1){
        perror(comm[1]);
        return 0;
    }


    if(access(comm[2],0)==0){
        if(stat(comm[2],&st)<0){
            perror("stat error");
            return 0;
        }
        if(S_ISDIR(st.st_mode)){
            printf("dir\n");
            char * a[2];
            a[0]="cdr";
            a[1]=comm[2];
            cdr(a);
            fd2=open(comm[1],O_WRONLY | O_CREAT | O_TRUNC,0644);
            while(read(fd1, buf, 1)){
                write(fd2, buf, 1);
            }
            a[1]="..";
            cdr(a);
            return 0;

        }else{
            char ans[2];
            printf("There is same name file here. Would you like to continue?(y/n)");
            while(1){
                scanf("%s",&ans);
                getchar();
                if(!strcmp(ans,"n")) return 0;
                else if(!strcmp(ans,"y")){
                    if((fd2=open(comm[2],O_WRONLY|O_CREAT|O_TRUNC,0644))==-1){
                        printf("something wrong. can't open file");
                        return 0;
                    }


                    while(read(fd1, buf, 1)){
                        write(fd2, buf, 1);
                    }

                    return 0;
                }
                else{ 
                    printf("you only answer y or n.\n");
                }
            }
        }
    }else{
        if((fd2=open(comm[2],O_WRONLY|O_CREAT|O_TRUNC,0644))==-1){
            printf("something wrong. can't open file");
            return 0;
        }


        while(read(fd1, buf, 1)){
            write(fd2, buf, 1);
        }

        return 0;

    }

    free(buf);
    return 0;
}
