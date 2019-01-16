#include "read.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Inits FileOp struct with initial values and reserves space for it in the heap. 
 */  
FileOp* initFileOp(char fileName[]){
    // Mallocs space
    FileOp *f = malloc (sizeof(FileOp));
    if (f == NULL){
        printf(MALLOC_ERROR);
        exit(1);
    }
    f->buffer = calloc(MAX_SEARCH_SIZE, sizeof(MAX_SEARCH_SIZE*(sizeof(char))));
    if (f->buffer == NULL){
        printf(MALLOC_ERROR);
    }
    f->file = fopen(fileName, "rb");
    if (f->file == NULL){
        printf(OPEN_ERROR);
        exit(1);
    }
    f->startCharFound = FALSE;
    f->fileSize = 0;
    f->found = FALSE;
    f->occ = 0;
    f->absoluteLocation = 0;
    f->finalized = FALSE;


    return f;
}

/**
 * Reads the next N chars. Clears out the buffer each time to prevent junk data from being 
 * read if what is read isn't the max length of the buffer.  
 * 
 */
void readChars(FileOp *f){
    // Clears buffer junk, could be done much better but meh 
    // free(f->buffer);
    // f->buffer = calloc(MAX_SEARCH_SIZE, sizeof(MAX_SEARCH_SIZE*(sizeof(char))));

    int read = fread(f->buffer, sizeof(char), MAX_SEARCH_SIZE , f->file);
    // Null term after the last read
    if (read < MAX_SEARCH_SIZE && read > 0){
        f->buffer[read] = '\0';
    }

    // If nothing is read from the file, it is ready to be closed. 
    if (read == 0){
        f->finalized = TRUE;
        // Moves pointer to end of file to get the size
        fseek(f->file, 0, SEEK_END);
        f->fileSize = ftell(f->file);
        // Clears the buffer to prevent dup search
        free(f->buffer);
        f->buffer = calloc(MAX_SEARCH_SIZE, sizeof(MAX_SEARCH_SIZE*(sizeof(char))));
        if (fclose(f->file) != 0){
            printf(CLOSE_ERROR);
            exit(1);
        }
    }
}

/**
 * Frees the FileOp struct
 */ 
void freeFileOp(FileOp *f){
    if (f != NULL){
        free(f->buffer);
        free(f);
    }
}

/**
 * Resets the fseek position to the next char in the buffer that contains the start_char (or +20)
 * Override in place to prevent moving out of bounds if at the end of the file. 
 */ 
void move(FileOp *f){
    if (f->absoluteLocation > ftell(f->file)){
        fseek(f->file, 0, SEEK_END);
    }else{
        fseek(f->file, f->absoluteLocation, SEEK_SET);
    }
    readChars(f);
}

