/*******************************************************/
/*file name : kil.c,kil.h                              */
/*made by   : jun                                      */
/*date      : 2019.06.18                               */
/*This function is kill process              .         */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "kil.h"
#include "MAN.h"

#define MAX_COMMAND 1024

void kil(char * comm[MAX_COMMAND],int argc)
{
	if(argc == 1)
		kilMAN();
	else if(argc == 2)
	{
		if(comm[1] != "-")
		{
			// 있으며 삭제하는거 구현
			kill(atoi(comm[1]),SIGKILL);
		}
	}
	else if(argc == 3)
	{
		//option
	}
}
