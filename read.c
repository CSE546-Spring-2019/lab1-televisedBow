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

    f->fileSize = 0;
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
    free(f->buffer);
    f->buffer = calloc(MAX_SEARCH_SIZE, sizeof(MAX_SEARCH_SIZE*(sizeof(char))));

    int read = fread(f->buffer, sizeof(char), MAX_SEARCH_SIZE , f->file);

    // If nothing is read from the file, it is ready to be closed. 
    if (read == 0){
        f->finalized = TRUE;
        // Moves pointer to end of file to get the size
        fseek(f->file, 0, SEEK_END);
        f->fileSize = ftell(f->file);
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
        free(f->file);
        free(f);
    }
}

/**
 *  Resets the fseek position to just one more than the previous read. Then 
 *  calls readChars to read in the next N chars. 
 */ 
void move(FileOp *f){
    if (fseek(f->file, f->absoluteLocation, SEEK_SET) != 0){
        printf(READ_ERROR);
        exit(1);
    }
    readChars(f);
}

