typedef unsigned int piece;

/* Game board structure */
typedef struct {
  size_t size;
  piece *board;
} Board;

/* Game states */
typedef enum {
  GAME_NOT_OVER,
  GAME_OVER
} GameState;

/* Move directions */
typedef enum {
  UP,
  DOWN,
  LEFT,
  RIGHT
} Direction;

/* Move results */
typedef enum {
  MOVE_OK,
  MOVE_INVALID
} MoveResult;

/* Game functions */
Board *create_board(ssize_t size);
void free_board(Board *board);
MoveResult move(Board *board, Direction direction);
void show_board(Board *board);
GameState game_state(Board *board);
