#ifndef READ_H
#define READ_H

#define MALLOC_ERROR "Error mallocing, please try again\n"
#define READ_ERROR "Error reading file, please try again\n"
#define BUFF_SIZE sizeof(char) * 4
#define FALSE 0
#define TRUE 1
#define MAX_SEARCH_SIZE 2
#include <stdio.h>

typedef struct FileOp {
  int fileSize;
  FILE *file;
  int finalized;
  char *buffer;
  char *tempBuff;
  long long int absoluteLocation;
  int buffLoc;
  int occ;
} FileOp;

FileOp* initFileOp(char fileName[]);
void freeFileOp(FileOp *f);
void readChars(FileOp *f);
void move(FileOp *f);

#endif 