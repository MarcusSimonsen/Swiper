/* Game board structure */
typedef struct {
  size_t size;
  unsigned int **board;
} Board;

/* Game states */
typedef enum {
  WIN = 1,
  LOSE = 2,
  CONTINUE = 3
} GameState;

/* Move directions */
typedef enum {
  UP = 1,
  DOWN = 2,
  LEFT = 3,
  RIGHT = 4
} Direction;

/* Game functions */
Board *create_board(size_t size);
void free_board(Board *board);
int move(Board *board, Direction direction);
void show_board(Board *board);
GameState game_state(Board *board);
