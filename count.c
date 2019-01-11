// Required header files
#include <stdio.h>
#include "read.h"
#include <stdlib.h>
#include <string.h>

char str[] = "te";

void match(int offset, FileOp *f, int searchCharOffset){
	// Checks for completed buffer size 
	if (offset == BUFF_SIZE || f->buffer[offset] == "\0"){
		readChars(f);
		offset = 0;
	}

	if (searchCharOffset == strlen(str)){
    	f->occ++;
    	printf("offset: %d, strlen(str) %d\n", offset, strlen(str));
    	printf("FOUND ONE\n");
  	} else if (f->buffer[offset] == (str[searchCharOffset] & 0xff)){
    	printf("offset of: %d, searchCharOffset of: %d, searchChar: %c, bufferChar: %c, buffer: %s\n", offset, searchCharOffset, str[searchCharOffset], f->buffer[offset], f->buffer);
    	match(++offset, f, ++searchCharOffset);
  	}
}


int main(){
  	FileOp *f = initFileOp("test");
  	// printf("%x\n", f->buffer[0]);
  	// printf("%d\n", (f->buffer[0] == (str[0] & 0xff)));

  	// printf("%d", 0b1010100 == c[0]);
  	while (f->finalized != TRUE){
		readChars(f);
		int i;

  		for (i = 0; i < BUFF_SIZE; i++){

    		match(i, f, 0);
			f->absoluteLocation++;
			move(f);
  		}

  	}
    printf("%d\n", f->occ);
  	freeFileOp(f);
  	return 0;
}