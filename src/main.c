#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "prompt.h"
#include "cdr.h"

int main()
{
    int str[100];
    while(1)
    {
        prompt();
        cdr();
    }
}

