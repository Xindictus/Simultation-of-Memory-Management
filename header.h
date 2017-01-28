#ifndef __HEADER_H__
#define __HEADER_H__

#define VIRTUAL_PROCESS_1 "bzip.trace"
#define VIRTUAL_PROCESS_2 "gcc.trace"
#define BZIP_PROCESS 'B'
#define GCC_PROCESS 'G'
#define EMPTY_IPT_PROCESS 'X'
#define WRITEBACK 'W'
#define READ 'R'
#define BUFFER_SIZE 12

typedef struct frame {
	char process;
	char page[6];
	char functionality;	
} FRAME; 

void printIPT(FRAME *IPT, int size);

int searchForPage(FRAME *, int, char *, char, char); 

int insertPage(FRAME *, int, char, char *, char);

int FWF(FRAME *, int, char);

#endif