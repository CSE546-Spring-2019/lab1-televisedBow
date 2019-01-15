// Required header files
#include <stdio.h>
#include "read.h"
#include <stdlib.h>
#include <string.h>

/**
 * Matching algo that recursivly calls itself if a matching char is found. 
 * Each recursive call  increments the offset by one increasing the position in the buffer and the searchString buffer. 
 * 
 * The boundary condition that can occur if there is a potential match is not handled here. Instead the method terminates. The boundary will be 
 * caught in the next buffer because it only advances one char at a time and is as large as the maximum search string. 
 * 
 */
void match(int offset, FileOp *f, char searchString[]){
	if (offset == strlen(searchString)){
    	f->occ++;
  	} else if (f->buffer[offset] == (searchString[offset] & 0xff)){
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
 * 
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
		f->absoluteLocation++;
  	}
    printf("Size of file is %lld\nNumber of matches = %lld\n", f->fileSize, f->occ);

	// Writes output
	write(argv[3], f->fileSize, f->occ);

	// Frees resources
  	freeFileOp(f);
  	return 0;
}