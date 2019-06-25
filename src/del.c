/*******************************************************/
/*file name : del.c, del.h                             */
/*made by   : sup                                      */
/*date      : 2019.06.18                               */
/*This function is to delete file or directory.        */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#include "del.h"
#include "cpy.h"

#define MAX_PATH 1024

int del(char * comm[MAX_PATH],int argc){

	//확인여부-디렉토리-디렉토리 비어있지 않아도 삭제
	int flag_y=0;
	int flag_d=0;
	int flag_r=0;
	int i =0;

	if(argc > 3){
		fprintf(stderr, "사용법: %s [OPTION] <file/path> \n", comm[0]);
		return 0;
	}

	//option check
	if(argc == 3 && comm[1][0]=='-'){
		while(comm[1][i++]!='\0'){
			if(comm[1][i]=='y') flag_y=1; 
			if(comm[1][i]=='d') flag_d=1;
			if(comm[1][i]=='r') flag_r=1;
		}

		//error
		if(flag_y==0 && flag_d==0 && flag_r==0)
		{
			printf("you can use y,d,r option.\n");
			printf("usage : del [OPTIOM] <file/path> \n");
			return 0;
		}

		//option 'y'
		if(flag_y==1 && flag_d ==0 && flag_r ==0){
			if(access(comm[2],0)==0 && checkFile(comm[2])==0) 
				return unlink(comm[2]);
			else if(checkFile(comm[2])==2)
				printf("This is directory, you can use option.\n");
			else printf("There is no file here.\n");

			return 0;
		}

		//option 'd' with 'y'
		if(flag_d ==1 && flag_r ==0){

			if(checkFile(comm[2])==2){
				if(flag_y==0){
					printf("Really delete this directory?(y/n)\n");
					char ans[2];
					while(1){
						scanf("%s",ans);
						getchar();
						if(!strcmp(ans,"n")) return 0;
						else if(!strcmp(ans,"y")) {

							if(rmdir(comm[2])==-1)
							{
								printf("In directory there exist file.\n");
								printf("If you delete this, you can use option r\n");
							}

							return 0;
						}
						else printf("you only answer y or n.\n");    
					}
				}else {

					if(rmdir(comm[2])==-1)
					{
						printf("In directory there exist file.\n");
						printf("If you delete this, you can use option r.\n");
					}

				}
			}else printf("This is not directory\n");

			return 0;
		}

		//option 'r'
		if(flag_r ==1){
			if(checkFile(comm[2])==2){
				if(flag_y==0){
					printf("Really delete this directory?(y/n)\n");
					char ans[2];
					while(1){
						scanf("%s",ans);
						getchar();
						if(!strcmp(ans,"n")) return 0;
						else if(!strcmp(ans,"y")) {
							dirDel(comm[2]);
							return 0;
						}
						else printf("you only answer y or n.\n");    
					}
				}else dirDel(comm[2]);

			}else printf("This is not directory\n");

			return 0;
		}

	}else if(argc==2){
		//not option
		//exist file
		if(access(comm[1],0)==0 && checkFile(comm[1])==0){
			printf("Really delete this file?(y/n)\n");

			char ans[2];
			while(1){
				scanf("%s",ans);
				getchar();
				if(!strcmp(ans,"n")) return 0;
				else if(!strcmp(ans,"y")) return unlink(comm[1]);
				else printf("you only answer y or n.\n");    
			} 
		}else if(checkFile(comm[1])==2)
			printf("This is directory, you can use option.\n");
		else printf("There is no file here.\n");
	}
	else printf("usage : del [OPTIOM] <file/path> \n");

	return 0;
}

int dirDel(char * comm){
     DIR * dir = NULL;
     struct dirent *dir_entry=NULL;
     char *preDir = (char*)malloc(sizeof(char)*MAX_PATH);
     char *path1 = (char*)malloc(sizeof(char)*MAX_PATH);
     char *path2 = (char*)malloc(sizeof(char)*MAX_PATH);
     char *path3 = (char*)malloc(sizeof(char)*MAX_PATH);
	 
	 strcpy(path1,".");
     strcat(path1,"/");
     strcat(path1,comm);
     dir = opendir(path1);
    
         while((dir_entry = readdir(dir))!=NULL){
             if(!strcmp(dir_entry->d_name,".") || !strcmp(dir_entry->d_name,".."))
                 continue;
             sprintf(path2,"./%s/%s",comm, dir_entry->d_name);
             if(checkFile(path2)==2){
                 char * a[3];
                 a[0]="del";
                 a[1]="-yr";
                 a[2]=path2;
                 del(a,3);
             }
             else{
                 char * a1[3];
                 a1[0]="del";
				 a1[1]= "-y";
                 a1[2]=path2;
                 del(a1,3);
             }
         } 

		
     	dir = opendir(path1);
         while((dir_entry = readdir(dir))!=NULL){
             if(!strcmp(dir_entry->d_name,".") || !strcmp(dir_entry->d_name,".."))
                 continue;
             sprintf(path3,"./%s/%s",comm, dir_entry->d_name);
                 char * a[3];
                 a[0]="del";
                 a[1]="-dy";
                 a[2]=path3;
                 del(a,3);
         } 

		 if(dir_entry==NULL){
                 char * a[3];
                 a[0]="del";
                 a[1]="-dy";
                 a[2]=comm;
                 del(a,3);

		 }


     free(path1);
     free(preDir);
     free(path2);
	 free(path3);
     
	 return 0;
 }
