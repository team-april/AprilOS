/*******************************************************/
/*file name : psl.c,psl.h                              */
/*made by   : jun                                      */
/*date      : 2019.06.18                               */
/*This function is showing process list                */
/*******************************************************/
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND 1024
#define MAX_PATH 1024
void psl()
{
	DIR *dir;
	struct dirent *entry;
	struct stat fileStat;
	
	int pid;
	char path[MAX_PATH];
	
	dir = opendir("/proc");

	printf(" [PID]\t [PPID]\t [NAME]\t[State]\t[UID]  \n");
	while((entry =readdir(dir)) != NULL)
	{
		FILE *fp;
		char * statDia[MAX_COMMAND];
		char str[MAX_COMMAND];
		lstat(entry->d_name,&fileStat);

		if(!S_ISDIR(fileStat.st_mode))
			continue;
		pid = atoi(entry->d_name);
		if(pid <= 0)
			continue;
		sprintf(path,"/proc/%d/stat",pid);
		fp=fopen(path,"r");
		memset(str,'\0',MAX_COMMAND);
		fgets(str,MAX_COMMAND,fp);
		statDis(statDia,str);
		printf(" %s\t   %s\t %s\t   %s\t%d\t\n",statDia[0],statDia[3],statDia[1],statDia[2],fileStat.st_uid);
		fclose(fp);
		
	}
	closedir(dir);
}

void statDis(char * statDia[MAX_COMMAND], char * str)
{
	int i =0;
	if(strlen(str) != 0 && str[0] != ' ')
	{
		char * temp = strtok(str," ");
		while(temp != NULL)
		{
			statDia[i] = temp;
			i++;
			temp = strtok(NULL," ");
		}
	}
		statDia[1][strlen(statDia[1])-1] = ' ';
		statDia[1][0]=' ';
}
