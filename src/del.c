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

#define MAX_PATH 1024

int del(char * comm[MAX_PATH],int argc){
    DIR * dir = NULL;
    //struct dirent *file = NULL;
    
    if((dir=opendir(comm[1]))==NULL){
        return unlink(comm[1]);
    }
    printf("This is directory. you can use option\n");

    return 0;
}
