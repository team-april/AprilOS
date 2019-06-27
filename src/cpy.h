#ifndef CPY_H_
#define CPY_H_

#include <stdio.h>

int cpy(char * [],int);
int openCpy(int fd1, int fd2, char *, char *);
int dirCpy(char *, char *);
int checkFile(char *);
int sameCheck();

#endif
