#ifndef GAME
#define GAME
#include "2048.h"
#endif

void print_board(Board *board) {
	int i, j;
	ssize_t s;
	piece *arr;

	s = board->size;
	arr = board->board;

	printf("+-");
	for (i = 0; i < s; i++) printf("--");
	printf("+\n");
	for (i = 0; i < s; i++) {
		printf("| ");
		for (j = 0; j < s; j++) {
			arr[i*s+j] == 0 ? printf(" ") : printf("%c", 96 + arr[i*s+j]);
			printf(" ");
		}
		printf("|\n");
	}
	printf("+-");
	for (i = 0; i < s; i++) printf("--");
	printf("+\n");
}
