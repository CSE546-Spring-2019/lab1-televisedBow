#include "read.h"
#include <stdio.h>
#include <stdlib.h>

#define COUNT 100
#define TRUE 1
#define FALSE 0


int fileLength = -1;
int finalized = FALSE;
FILE *fp;

/**
 * Opens a file for reading in binary mode. Keeps information encap inside file. 
 * 
 */
void openFile(char fileName[]){
    fp = fopen(fileName, "rb");
    if (fp == NULL){
        printf("Error opening file %s, please try again\n", fileName);
        exit(1);
    }
}

/**
 * Returns the filesize of the file iff it has been finalized. 
 * 
 */
int getFileLength(){
    if (finalized == TRUE){
        return fileLength;
    }else{
        return NULL;
    }
}