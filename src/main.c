#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "prompt.h"
#include "command.h"


int main()
{
    while(1)
    {
        prompt();
        strDis();
    }
}

