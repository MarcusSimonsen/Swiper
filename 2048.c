#include <stdlib.h>
#ifndef GAME
#define GAME
#include "2048.h"
#endif

Board *empty_board(ssize_t size) {
  Board *board = malloc(sizeof(Board));
  piece *arr = calloc(size * size, sizeof(piece));

  board->size = size;
  board->board = arr;

  return board;
}
