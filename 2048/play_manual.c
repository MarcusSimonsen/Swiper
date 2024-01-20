#include <stdio.h>
#ifndef GAME
#define GAME
#include "2048.h"
#endif
#ifndef CLIENT
#define CLIENT
#include "2048_client.h"
#endif
#include "2048.c"
#include "2048_ascii.c"
#include <time.h>

Direction get_move(Board *board) {
	char c;
	
	c = getchar();	/* Read move from user */
	getchar();		/* Consume trailing newline */

	switch(c) {
		case 'w':
			return UP;
		case 's':
			return DOWN;
		case 'a':
			return LEFT;
		case 'd':
			return RIGHT;
		default:
			printf("Please input a valid move\n");
			return get_move(board);
	}
}

void main() {
	srand(time(NULL));

	Board *board;
	Direction move_dir;
	MoveResult res;

	board = create_board(4);

	while (/*game_state(board) == GAME_NOT_OVER && */ 1) {
		/* Print board to user */
		print_board(board);
		/* Get input from user */
		res = MOVE_INVALID;
		while (res != MOVE_OK) {
			move_dir = get_move(board);
			/* Make move */
			res = move(board, move_dir);
			/* Check if move was invalid */
			if (res == MOVE_INVALID)
				printf("Invalid move\n");
		}
	}

	free_board(board);
}
