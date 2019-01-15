// Required header files
#include <stdio.h>
#include "read.h"
#include <stdlib.h>
#include <string.h>

/**
 * This function does a memcmp of the searchString and the buffer for the size of the search string. 
 * If they are found to be equal, TRUE (1) is returned to add one to the f->occ counter. 
 * 
 */ 
int fallbackAndVerify(int offset, FileOp *f, char searchString[]){
	if (memcmp(f->buffer, searchString, offset) == 0){
		return TRUE;
	}else{
		return FALSE;
	}
}


/**
 * Matching algo that recursivly calls itself until another first start char is found or the buffer is empty. 
 * Each recursive call increments the offset by one increasing the position in the buffer and the searchString buffer. 
 *  
 */
void match(int offset, FileOp *f, char searchString[]){
	/*
	 * If the current char in the buffer matches the start of the search string, this is where we should jump to next for the next run of the method. 
	 * However, a flag is set to prevent overwriting this if a duplicate value is found that matches the first searchString char.
	 * Additionally, it is not permitted to have the first char in the buffer to trigger this (inf loop otherwise)
	 */ 
	if (((f->buffer[offset]) == (searchString[0] & 0xff)) && f->startCharFound == FALSE && offset != 0){
		f->absoluteLocation+= offset;
		f->startCharFound = TRUE;
	}

	/*
	 * If the search string is the same length as the offset and the previous n char match (based on strlen) 
	 * then a match is found. Then match is called recursivley again if there has not been a determined next starting char.
	 * If this flag has already been set, then there is no need to continue searching. 
	 * 
	 * This will never go out of bounds because the logic is short circuited if going back would put us out of bounds. 
	 */ 
	if (offset == strlen(searchString) && fallbackAndVerify(offset, f, searchString) == TRUE){
		f->occ++;
		if (f->startCharFound != TRUE){
			match(++offset, f, searchString);
		} 
  	} else if (offset <= 20){
    	match(++offset, f, searchString);
  	}
}

/**
 * Prepares the FileOp struct for processing. 
 * Error checking in place to prevent user errors from crashing program. 
 * 
 */
FileOp* prep(int argc, char *argv[]){
	// Checks argument count 
	if (argc != 4){
		printf(ARGS_ERROR);
		exit(1);
	}

	// Init FileOp struct
  	FileOp *f = initFileOp(argv[1]);

	// Error checks search string and sets it
	if (strlen(argv[2])> 20){
		printf(SEARCH_ERROR);
		exit(1);
	}
	return f;
}

/**
 * Writes what was printed on the console to the user defined file with error checking. 
 */ 
void write(char fileName[], long long int fileSize, int occ){
	FILE *toWrite = fopen(fileName, "w");
	if (toWrite == NULL){
		printf(ERROR_WRITE);
		exit(1);
	}

	fprintf(toWrite, "Size of file is %lld\nNumber of mathces = %d\n", fileSize, occ);

	if (fclose(toWrite) == EOF){
		printf(ERROR_WRITE_CLOSE);
		exit(1);
	}
	free(toWrite);
}

int main(int argc, char *argv[]){
	// Sets up struct for writing
	FileOp *f = prep(argc, argv);

	// Counts until file is done proc
  	while (f->finalized != TRUE){
		move(f);
    	match(0, f, argv[2]);
		/**
		 * Resets the startCharFound flag and leaves absolute location alone. Otherwise
		 * we push forward the size of MAX_SEARCH_SIZE
		 */
		if (f->startCharFound == TRUE){
			f->startCharFound = FALSE;
		}else{
			f->absoluteLocation+= MAX_SEARCH_SIZE;
		}
  	}
    printf("Size of file is %lld\nNumber of matches = %lld\n", f->fileSize, f->occ);

	// Writes output
	write(argv[3], f->fileSize, f->occ);

	// Free resources
  	freeFileOp(f);
  	return 0;
}