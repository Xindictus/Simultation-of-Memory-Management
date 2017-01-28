#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "header.h"

int main (int argc, char *argv[])
{
	int k, frames, q, max = 0, i, param_flag = 0, PF = 0, bzipLocalPF = 0, 
	gccLocalPF = 0, write_backs = 0, read_counter = 0, maxCounter = 0, 
	bzipReferences = 0, gccReferences = 0, temp_counter = 0;
	FRAME *IPT;
	char buffer[BUFFER_SIZE]; 
	FILE *bzip, *gcc;

	/* CHECK NUMBER AND KIND OF ARGUMENTS */
	for (i = 0 ; i < argc ; i++) {
		if (strncmp(argv[i] , "-k", 2) == 0) {
			k = atoi(argv[i+1]);
			param_flag++;
		}
		else if (strncmp(argv[i] , "-frames", 7) == 0) {
			frames = atoi(argv[i+1]);
			param_flag++;
		}
		else if (strncmp(argv[i] , "-q", 2) == 0) {
			q = atoi(argv[i+1]);
			param_flag++;
		}
		else if (strncmp(argv[i] , "-max", 4) == 0) {
			max = atoi(argv[i+1]);
			param_flag++;
		}
	}

	/*
	 *	N: Number of processes
	 *	K: Number of transactions
	 */
	if (param_flag != 3 &&  param_flag != 4) {
		printf("-----------------------------------------------------------\n");
		printf("There is a missing parameter....Syntax is:\n");
		printf("main -k <maxFP> -frames <numberOfFrames> -q <roundRobinQ> -max <maxReferences>\n");
		printf("-----------------------------------------------------------\n");
		exit(1);
	}

	/*
	 * Check ration of frames and k
	 */
	if ((2*k) >= frames) {
		perror("Frames should be at least 2 * k");
		return -1;
	}


	/* OPEN FILES FOR READING */
	bzip = fopen(VIRTUAL_PROCESS_1, "r");

	if (bzip == NULL) {
		perror ("Error opening VIRTUAL_PROCESS_2");
		return -1;
	}

	gcc = fopen(VIRTUAL_PROCESS_2, "r");
	
	if (gcc == NULL) {
		perror ("Error opening VIRTUAL_PROCESS_2");
		return -1;
	}

	/* CREATE IPT */
	IPT = (FRAME *) malloc(sizeof(FRAME) * frames);
	for (i = 0; i < frames; i++) {
		IPT[i].process = EMPTY_IPT_PROCESS;
		memset(IPT[i].page, 0, sizeof(IPT[i].page));
		IPT[i].functionality = ' ';
	}
	
	while (maxCounter < max) {

		/* VIRTUAL PROCESS 1 */
		for (i = 0; i < q; i++) {

			if (maxCounter >= max)
				break;

			maxCounter++;
			memset(buffer, 0, sizeof(buffer));

			if (fgets(buffer, BUFFER_SIZE, bzip) != NULL) {

				bzipReferences++;

				if (searchForPage(IPT, frames, buffer, BZIP_PROCESS, buffer[9]) == -1) {

					PF++;
					bzipLocalPF++;

					if (bzipLocalPF > k) {
						bzipLocalPF = 0;
						temp_counter = FWF(IPT, frames, BZIP_PROCESS);
						write_backs += temp_counter;
						read_counter += k - temp_counter;
						temp_counter = 0;
					}

					if (insertPage(IPT, frames, BZIP_PROCESS, buffer, buffer[9]) == -1) {
						perror("Error inserting page to IPT");
						return -1;
					}
				}
			} else {
				break;
			}
		}

		/* VIRTUAL PROCESS 2 */
		for (i = 0; i < q; i++) {

			if (maxCounter >= max)
				break;

			maxCounter++;
			memset(buffer, 0, sizeof(buffer));

			if (fgets(buffer, BUFFER_SIZE, gcc) != NULL) {

				gccReferences++;

				if (searchForPage(IPT, frames, buffer, GCC_PROCESS, buffer[9]) == -1) {

					PF++;
					gccLocalPF++;

					if (gccLocalPF > k) {
						gccLocalPF = 0;
						temp_counter = FWF(IPT, frames, GCC_PROCESS);
						write_backs += temp_counter;
						read_counter += k - temp_counter;
						temp_counter = 0;
					}

					if (insertPage(IPT, frames, GCC_PROCESS, buffer, buffer[9]) == -1) {
						perror("Error inserting page to IPT");
						return -1;
					}
				}
			} else {
				break;
			}
		}		
	}

	// printIPT(IPT, frames);

	printf("\n----------------------------STATISTICS------------------------------------\n");
	printf("BZIP References: %d (%.3f%), GCC References: %d (%.3f%)\n", 
		bzipReferences, ((float)bzipReferences*100/(float)max), gccReferences, 
		((float)gccReferences*100/(float)max));
	printf("Total Page Faults: %d\n", PF);
	printf("Total write-backs: %d (%.3f%), Total readings: %d (%.3f%)\n", 
		write_backs, ((float)write_backs*100/(float)(write_backs + read_counter)), 
		read_counter, ((float)read_counter*100/(float)(write_backs + read_counter)));
	printf("Total memory frames: %d\n", frames);
	printf("--------------------------------------------------------------------------\n");

	/* CLOSE FILES */
	if (fclose(bzip) != 0) {
		perror ("Error closing VIRTUAL_PROCESS_1");
		return -1;
	}

	if (fclose(gcc) != 0) {
		perror ("Error closing VIRTUAL_PROCESS_2");
		return -1;
	}

	/* FREE INVERTED PAGE TABLE */
	free(IPT);

	exit(0);
}