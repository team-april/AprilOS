/*******************************************************/
/*file name : mov.c, mov.h                             */
/*made by   : sup                                      */
/*date      : 2019.06.18                               */
/*This function is to move file or directory.          */
/*******************************************************/
#include <stdio.h>

#include "mov.h"
#include "cpy.h"
#include "del.h"

#define MAX_PATH 1024

void mov(char * comm[MAX_PATH],int argc){
    cpy(comm,argc);
    del(comm,argc);

}
