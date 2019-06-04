#include <stdio.h>
#include <unistd.h>
#define PATH_MAX 100
void cdr(char * argv)
{
    if(chdir(argv)==-1)
    {
        printf("error!!\n");
    }

}
