#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "sta.h"
#include "MAN.h"
#define MAX_COMMAND 1024


int sta(char * comm[MAX_COMMAND],int argc)
{
   struct stat st;
   if(argc == 1 || argc > 2)
   {
       staMAN();
       return 0;
   }


   if(stat(comm[1],&st) == -1)
   {
       perror("stat");
       return 0;
   }

   printf("File type \t:  ");

   switch(st.st_mode & S_IFMT)
   {
       case S_IFBLK:
           printf("block device\n");
           break;
       case S_IFCHR:
           printf("character device\n");
           break;
       case S_IFDIR:
           printf("Directory\n");
           break;
       case S_IFIFO:
           printf("FIFO/pipe\n");
           break;
       case S_IFLNK:
           printf("symlink\n");
           break;
       case S_IFREG:
           printf("regular file\n");
           break;
       case S_IFSOCK:
           printf("socket\n");
           break;
       default:
           printf("???\n");
   }

   printf("I-node num\t:  %d\n",(long) st.st_ino);
   printf("Mode\t\t:  %lo(octal)\n",(unsigned long) st.st_mode);
   printf("Link count\t:  %ld\n",(long)st.st_nlink);
   printf("Ownership\t:  UID=%ld\tGID=%ld\n",(long)st.st_uid,(long)st.st_gid);
   printf("I/O block size\t:  %ld btyes\n",(long)st.st_blksize);
   printf("File size\t:  %lld bytes\n",(long long)st.st_size);
   printf("Blocks allocated:  %lld\n",(long long)st.st_blocks);

   printf("Last status chage\t: %s",ctime(&st.st_ctime));
   printf("Last file access\t: %s",ctime(&st.st_atime));
   printf("Last file modificatione\t: %s",ctime(&st.st_mtime));
   return 0;
   }

   
