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
void psl()
{
	DIR *dir;
	struct dirent *entry;
	struct stat fileStat;
	
	char termPath[256];
	char cmdLine[256];
	char UID;
	int pid;
	char path[256];
	
	dir = opendir("/proc");



	printf("[PID]\t [NAME] \n");
	while((entry =readdir(dir)) != NULL)
	{
		FILE *fp;
		lstat(entry->d_name,&fileStat);

		if(!S_ISDIR(fileStat.st_mode))
			continue;
		pid = atoi(entry->d_name);
		if(pid <= 0)
			continue;

		char ppid[256];
		sprintf(termPath,"/proc/%d/comm",pid);
		sprintf(path,"/proc/%d/stat",pid);
		printf("%s",path);
		fp=fopen(path,"r");
		fscanf(fp,"%*[^ ] %*[^ ] %*[^ ] %*[^ ]",ppid);
		getCmdLine(termPath,cmdLine);
		printf(" %d\t %s %s\n",pid,cmdLine,ppid);
		fclose(fp);
		
	}
	closedir(dir);
}

int getCmdLine(char *file, char *buf) {
	FILE *fp;
	int i;
	fp = fopen(file, "r");            //   /proc/pid/cmdline에 이름이 있습니다.

	memset(buf, 0, sizeof(buf));
	fgets(buf, 256, fp);
	if(strlen(buf) != 0)
		buf[strlen(buf)-1]='\0';
	fclose(fp);
}





