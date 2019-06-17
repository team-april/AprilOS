#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "shw.h"
#include "MAN.h"

#define MAX_COMMAND 1024
#define MAX_WORD 100000
void shw(char * comm[MAX_COMMAND],int argc)
{
    char buff;
    int fd;

    
    if(argc == 2)
    {
        fd = open(comm[1],O_RDONLY);
        while(read(fd,&buff,1))
            write(1,&buff,1);
    }
    else if(argc == 3) // option
    {
        if(comm[1] == "-")
            ;
        else if(comm[1] == ">>")
            ;
        else
            shwMAN();
    }
    else
        shwMAN();
}
