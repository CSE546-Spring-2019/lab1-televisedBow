// Required header files
#include <stdio.h>
#include "read.h"
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MALLOC_ERROR "Error mallocing, please try again\n"
#define READ_ERROR "Error reading file, please try again\n"
#define BUFF_SIZE 100

typedef struct FileOp {
  int fileSize;
  FILE *file;
  int finalized;
  char *buffer;
  int absoluteLocation;
  int *toReturnTo;
  int buffLoc;
  int occ;
} FileOp;

FileOp* initFileOp(char fileName[]){
  // Mallocs space
  FileOp *f = malloc (sizeof(FileOp));
  if (f == NULL){
    printf(MALLOC_ERROR);
    exit(1);
  }
  f->buffer = malloc(sizeof(BUFF_SIZE*(sizeof(char))));
  if (f->buffer == NULL){
    printf(MALLOC_ERROR);
  }

  f->toReturnTo = malloc(sizeof(BUFF_SIZE*(sizeof(int))));

  f->file = fopen(fileName, "rb");
  if (f == NULL){
      printf("Error opening file %s, please try again\n", fileName);
      exit(1);
  }

  f->fileSize = 0;
  f->buffLoc = 0;
  f->occ = 0;
  f->absoluteLocation = 0;
  f->finalized = FALSE;

  return f;
}

void freeFileOp(FileOp *f){
  if (f != NULL){
    free(f->buffer);
    free(f);
  }
}



int main(){
  openFile("test");
  FileOp *f = initFileOp("test");

  while (f->finalized != NULL){
    if (EOF == fgets(f->buffer, BUFF_SIZE, f->file)){
      printf(READ_ERROR);
      exit(1);
    }

    while (TRUE){

    }

  }

  freeFileOp(f);
  return 0;
}