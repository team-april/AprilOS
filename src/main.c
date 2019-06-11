#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "prompt.h"

int main()
{
    char argv[1024];
    int str[100];
    while(1)
    {
        prompt();
        scanf("%s",argv);
    }
}

