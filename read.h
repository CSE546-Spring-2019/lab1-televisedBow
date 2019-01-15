#ifndef READ_H
#define READ_H

#define MALLOC_ERROR "Error mallocing, please try again\n"
#define READ_ERROR "Error reading file, please try again\n"
#define OPEN_ERROR "Error could not open file, please try again\n"
#define CLOSE_ERROR "Error closing file\n"
#define ARGS_ERROR "Incorrect arguments, please use \"./count <input-filename> <search-string> <output-filename>\"\n"
#define SEARCH_ERROR "Incorrect search string, please limit it to 20 bytes or less\n"
#define ERROR_WRITE "Error creating file for writing\n"
#define ERROR_WRITE_CLOSE "Error closing write file\n"
#define FALSE 0
#define TRUE 1
#define MAX_SEARCH_SIZE sizeof(char) * 20
#include <stdio.h>

typedef struct FileOp {
  long long int fileSize;
  int rewindSkip;
  int found;
  FILE *file;
  int finalized;
  char *buffer;
  long long int absoluteLocation;
  long long int occ;
} FileOp;

FileOp* initFileOp(char fileName[]);
void freeFileOp(FileOp *f);
void readChars(FileOp *f);
void move(FileOp *f);

#endif 