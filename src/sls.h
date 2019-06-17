#ifndef SLS_H_
#include<sys/stat.h>
#include <dirent.h>
#define SLS_H_

#define MAX_COMMAND 1024
int sls(char * comm[MAX_COMMAND],int argc);
void sls_t(char *pathname, char *file, struct stat *st);
void sls_lt(char *pathname, char *file, struct stat *st);
char type(mode_t mode);
char* perm(mode_t mode);
void sls_l(char *pathname, char *file, struct stat *st);
void sls_(char *pathname, char *file, struct stat *st);
int dirErrorCheck(char * comm[MAX_COMMAND], char *dir, int argc, int ck);

#endif
