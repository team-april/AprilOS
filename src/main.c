#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "prompt.h"
#include "command.h"

int main()
{
    char argv[1024];
    while(1)
    {
        prompt();
        strDis();
    }
}

