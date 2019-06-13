#include <stdio.h>

#include "prompt.h"
#include "command.h"
#include "cdr.h"

int main()
{
    char argv[1024];
    char *Arr[1024];
    Arr[0]="cdr"; // init start dir

    cdr(Arr);
    while(1)
    {
        prompt();
        strDis();
    }
}

