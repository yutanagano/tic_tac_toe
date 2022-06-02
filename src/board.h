/**
 * Header file for board.c
 * (c) Yuta Nagano
 * 
 * The board struct uses 9-bit bitfields to represent the tic-tac-toe board.
 * The digits correspond to the board square as below:
 * 
 * The digits 'ihgfedcba' of a 9-bit binary value represent the below board:
 * 
 *  a | b | c
 * ---+---+---
 *  d | e | f
 * ---+---+---
 *  g | h | i
 * 
 * The tic-tac-toe board is considered to be zero-indexed. That is, digit 'a'
 * represents the coordinate (row=0, col=0); the digit 'f' represents the
 * coordinate (row=1, col=2); etc.
 */

/**
 * Struct representing a tic-tac-toe board state. The mask bitfield can be
 * thought of as a bitmask representing all coordintaes currently occupied
 * by any piece. The current_player_pieces bitfield shows coordinates occupied
 * by pieces of the current player.
 * 
 * The current_player bit represents the current player being either noughts
 * (0) or crosses (1).
 */
typedef struct
{
    unsigned int current_player_pieces:9;
    unsigned int mask:9;
    unsigned int current_player:1;
} board;

/**
 * @param b: pointer to a board struct
 * @return 1 if current player has won, 0 otherwise
 */
int check_win(board *b);

/**
 * @param b: pointer to a board struct
 * @return 1 if board full, 0 otherwise
 */
int board_full(board *b);

/**
 * Invert the board so that the current player alternates
 * @param b: pointer to a board struct
 */
void invert_board(board *b);

/**
 * Place a current player piecce on a given coordinate if possible.
 * @param b: pointer to a board struct
 * @param row: row index
 * @param col: col index
 * @return 0 if operation successful, 1 if failure
 */
int place_piece(board *b, short row, short col);

/**
 * @param b: pointer to a board struct
 * @param row: row index
 * @param col: col index
 * @return 1 if move at (row,col) on board b is legal, 0 otherwise
 */
int is_legal_move(board *b, short row, short col);

/**
 * @param row: row index
 * @param col: col index
 * @return bitfield with single bit turned on, corresponding to the provided
 * coordinates
 */
int generate_piece_mask(short row, short col);

/**
 * Print the board to the screen.
 * @param b: pointer to board struct
 * @param current_cross: whether or not current player should be drawn as cross
 */
void print_board(board *b);

/**
 * @param b: pointer to a board struct
 * @param row: row index
 * @param col: col index
 * @return character representation of a particular coordinate on the board
 */
char get_piece_as_char(board *b, short row, short col);