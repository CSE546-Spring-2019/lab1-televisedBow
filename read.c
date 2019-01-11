#include "read.h"
#include <stdio.h>
#include <stdlib.h>

int firstRead = TRUE;



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
    f->tempBuff = malloc(sizeof(MAX_SEARCH_SIZE*(sizeof(char))));
    if (f->tempBuff == NULL){
        printf(MALLOC_ERROR);
    }
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

void readChars(FileOp *f){
    int read = fread(f->buffer, sizeof(char), BUFF_SIZE - MAX_SEARCH_SIZE  , f->file);
    printf("READ: %d\n", read);
    if (read != BUFF_SIZE){
        f->finalized = TRUE;
    }
    firstRead = FALSE;
    f->fileSize += read;
}

void freeFileOp(FileOp *f){
    if (f != NULL){
        free(f->buffer);
        free(f->file);
        free(f);
    }
}

void move(FileOp *f){
    printf("FTELL: %d\n", ftell(f->file));
    if (fseek(f->file, f->absoluteLocation, SEEK_SET) != 0){
        printf(READ_ERROR);
        exit(1);
    }
}

