#include <stdlib.h>
#ifndef GAME
#define GAME
#include "2048.h"
#endif


/**
 * Helper function for getting random value for a new tile
 */
int get_rand_val() {
	int rnd = rand() % 10;	/* 10 % chance of 4, otherwise 2 */
	if (rnd == 0)
		return 2;
	return 1;
}

/**
 * Helper function for spawning tiles
 */
void spawn_tile(Board *board) {
	int availables[board->size * board->size];
	int available, avail_idx, idx;
	int val;
	ssize_t s;
	piece *arr;

	available = -1;
	s = board->size;
	arr = board->board;

	/* Find all free slots */
	for (int i = 0; i < s; i++)
		for (int j = 0; j < s; j++)
			if (arr[i*s+j] == 0)
				availables[++available] = i*s+j;

	/* If no free slots, return */
	if (available < 0)
		return;

	/* Choose a random free slot and fill it in with either 2 or 4 */
	val = get_rand_val();
	avail_idx = rand() % (available + 1);
	idx = availables[avail_idx];
	arr[idx] = val;
}

Board *create_board(ssize_t size) {
	Board *board = malloc(sizeof(Board));
	piece *arr = calloc(size * size, sizeof(piece));

	board->size = size;
	board->board = arr;

//	spawn_tile(board);
//	spawn_tile(board);
	board->board[0] = 1;
	board->board[4] = 2;

	return board;
}

void free_board(Board *board) {
	free(board->board);
	free(board);
}

/**
 * Helper function for moving tiles up
 */
unsigned int move_up(Board *board) {
	int i, j, k;
	ssize_t s;
	unsigned int moved;
	piece *arr;

	s = board->size;
	arr = board->board;
	moved = 0;

	/* Go through each column */
	for (i = 0; i < s; i++) {
		k = i;
		/* Go trough each row */
		for (j = 1; j < s; j++) {
			/* Is current piece empty? */
			if (arr[i+j*s] == 0)
				continue;
			/* Can pieces be merged? */
			if (arr[i+j*s] == arr[k]) {	/* Merge pieces */
				arr[k]++;				/* Upgrade piece */
				arr[i+j*s] = 0;			/* Remove other piece */
				k += s;
			} else { /* Pieces couldn't be merged,
						so just move piece */
				if (arr[k] == 0)
					arr[k] = arr[i+j*s];
				else {
					arr[k+s] = arr[i+j*s];
					k += s;
				}
				if (k == i+j*s)
					continue;
				arr[i+j*s] = 0;
			}
			moved++;
		}
	}
	return moved;
}

/**
 * Helper function for moving tiles down
 */
unsigned int move_down(Board *board) {
	int i, j, k;
	ssize_t s;
	unsigned int moved;
	piece *arr;

	s = board->size;
	arr = board->board;
	moved = 0;

	/* Go through each column */
	for (i = 0; i < s; i++) {
		k = i + (s-1)*s;
		/* Go trough each row */
		for (j = s-2; j >= 0; j--) {
			/* Is current piece empty? */
			if (arr[i+j*s] == 0)
				continue;
			/* Can pieces be merged? */
			if (arr[i+j*s] == arr[k]) {	/* Merge pieces */
				arr[k]++;				/* Upgrade piece */
				arr[i+j*s] = 0;			/* Remove other piece */
				k -= s;
			} else { /* Pieces couldn't be merged,
						so just move piece */
				if (arr[k] == 0)
					arr[k] = arr[i+j*s];
				else {
					arr[k-s] = arr[i+j*s];
					k -= s;
				}
				if (k == i+j*s)
					continue;
				arr[i+j*s] = 0;
			}
			moved++;
		}
	}
	return moved;
}

/**
 * Helper function for moving tiles left
 */
unsigned int move_left(Board *board) {
	int i, j, k;
	ssize_t s;
	unsigned int moved;
	piece *arr;

	s = board->size;
	arr = board->board;
	moved = 0;

	/* Go through each row */
	for (j = 0; j < s; j++) {
		k = j*s;
		/* Go trough each column */
		for (i = 1; i < s; i++) {
			/* Is current piece empty? */
			if (arr[i+j*s] == 0)
				continue;
			/* Can pieces be merged? */
			if (arr[i+j*s] == arr[k]) {	/* Merge pieces */
				arr[k]++;				/* Upgrade piece */
				arr[i+j*s] = 0;			/* Remove other piece */
				k++;
			} else { /* Pieces couldn't be merged,
						so just move piece */
				if (arr[k] == 0)
					arr[k] = arr[i+j*s];
				else {
					arr[k+1] = arr[i+j*s];
					k++;
				}
				if (k == i+j*s)
					continue;
				arr[i+j*s] = 0;
			}
			moved++;
		}
	}
	return moved;
}

/**
 * Helper function for moving tiles right
 */
unsigned int move_right(Board *board) {
	int i, j, k;
	ssize_t s;
	unsigned int moved;
	piece *arr;

	s = board->size;
	arr = board->board;
	moved = 0;

	/* Go through each row */
	for (j = 0; j < s; j++) {
		k = j*s + s-1;
		/* Go trough each column */
		for (i = s-2; i >= 0; i--) {
			/* Is current piece empty? */
			if (arr[i+j*s] == 0)
				continue;
			/* Can pieces be merged? */
			if (arr[i+j*s] == arr[k]) {	/* Merge pieces */
				arr[k]++;				/* Upgrade piece */
				arr[i+j*s] = 0;			/* Remove other piece */
				k--;
			} else { /* Pieces couldn't be merged,
						so just move piece */
				if (arr[k] == 0)
					arr[k] = arr[i+j*s];
				else {
					arr[k-1] = arr[i+j*s];
					k--;
				}
				if (k == i+j*s)
					continue;
				arr[i+j*s] = 0;
			}
			moved++;
		}
	}
	return moved;
}

/**
 * Moves tiles in the given direction
 */
MoveResult move(Board *board, Direction direction) {
	unsigned int res;
	/* Perform actual move of pieces */
	switch(direction) {
		case UP:
			res = move_up(board);
			break;
		case DOWN:
			res = move_down(board);
			break;
		case LEFT:
			res = move_left(board);
			break;
		case RIGHT:
			res = move_right(board);
			break;
	}

	printf("Moved %d pieces\n", res);

	if (res > 0) {
		/* Spawn new pieces */
		spawn_tile(board);

		return MOVE_OK;
	}
	return MOVE_INVALID;
}
