#include <stdio.h>
<<<<<<< HEAD
=======
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
>>>>>>> e0e7bdd39d3b7d077c9067068f9de966cb3f23c8

#include "prompt.h"
#include "command.h"


void cdr(char *command){
    printf("success\n");
}

int main()
{
    char argv[1024];
<<<<<<< HEAD
    while(1)
    {
        prompt();
        strDis();
=======
    char *command[1024];
    int argc;

    while(1)
    {
        prompt();
        fgets(argv,1024, stdin);
       // printf("%s", argv);
        command[0] = strtok(argv, " ");
      //  if(command[0]==NULL) continue;
        argc=1;

        while((command[argc]=strtok(NULL," ")) !=NULL){
            argc++;
        }

        //printf("%d",argc);        
        if(!strcmp(command[0],"cdr")){
            if( argc == 1 ) cdr(NULL);
            else if( argc != 2 ){
                printf("usage : cdr <dir name | path> \n");
                continue;
            }
            else
            { 
                cdr(command[1]);
                 continue;
            }


        } 
>>>>>>> e0e7bdd39d3b7d077c9067068f9de966cb3f23c8
    }
}

