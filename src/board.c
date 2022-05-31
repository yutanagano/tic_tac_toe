/**
 * Logic to operate a tic-tac-toe board.
 * (c) Yuta Nagano
 */
#include <stdio.h>
#include "board.h"

int place_piece(board *b, short row, short col)
{
    // No-op if move is illegal
    if (!is_legal_move(b, row, col))
        return 1;

    int piece_mask = generate_piece_mask(row, col);
    b->current_player_pieces |= piece_mask;
    b->mask |= piece_mask;

    // Operation successful
    return 0;
}

int is_legal_move(board *b, short row, short col)
{
    // Always illegal if coordinates out of bounds
    if ((row < 0) || (row > 2) || (col < 0) || (col > 2))
        return 0;
    
    return !(b->mask & generate_piece_mask(row, col));
}

int generate_piece_mask(short row, short col)
{
    return 1 << ((row * 3) + col);
}