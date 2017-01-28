#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

/*
 * Prints IPT
 */
void printIPT(FRAME *IPT, int size)
{
	int i;

	for (i = 0; i < size; i++) {
		printf("Process: %c, Page: %s, Functionality: %c\n", 
			IPT[i].process, IPT[i].page, IPT[i].functionality);
	}
}

/*
 * 1. Searches if page already exists.
 * 2. If exists -> return 0 else -1.
 * 3. If exists, change functionality if != WRITEBACK
 */
int searchForPage(FRAME *IPT, int size, char *buffer, char process, char functionality) 
{
	int i;

	for (i = 0; i < size; i++) {
		if (IPT[i].process != EMPTY_IPT_PROCESS) {
			if (strncmp(IPT[i].page, buffer, 5) == 0 && IPT[i].process == process) {
				//if (IPT[i].functionality != WRITEBACK)
				IPT[i].functionality = functionality;
				return 0;	
			}
		}
	}
	
	return -1;
}

/*
 * Inserts a new page to our IPT.
 * @return: 0 for success, -1 for error
 */
int insertPage(FRAME *IPT, int size, char process, char *page, char functionality)
{
	int i;

	for (i = 0; i < size; i++) {
		if (IPT[i].process == EMPTY_IPT_PROCESS) {
			IPT[i].process = process;
			strncpy(IPT[i].page, page, 5);
			IPT[i].functionality = functionality;
			return 0;
		}
	}
	
	return -1;
}

/*
 * Flushes the insertions made by PROCESS
 */
int FWF(FRAME *IPT, int size, char process)
{
	int i, write_backs = 0;

	for (i = 0; i < size; i++) {
		if (IPT[i].process == process) {
			/* LOG PROCESS' WRITES */
			if (IPT[i].functionality == WRITEBACK)
				write_backs++;

			/* RE-INITIALIZE IPT'S FRAME */
			IPT[i].process = EMPTY_IPT_PROCESS;
			memset(IPT[i].page, 0, sizeof(IPT[i].page));
			IPT[i].functionality = ' ';
		}
	}

	/* RETURN TOTAL write_backs FLUSHED */
	return write_backs;
}