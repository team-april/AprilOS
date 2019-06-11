#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "prompt.h"


void cdr(char *command){
    printf("success\n");
}

int main()
{
    char argv[1024];
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
    }
}

