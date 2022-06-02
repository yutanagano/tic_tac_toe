/**
 * Logic to operate a tic-tac-toe board.
 * (c) Yuta Nagano
 */
#include <stdio.h>
#include "board.h"

int check_win(board *b)
{
    // Check horizontal wins
    if (
        b->current_player_pieces &
        (b->current_player_pieces << 1) &
        (b->current_player_pieces >> 1) &
        0x092
    ) return 1;
    
    // Check vertical wins
    if (
        b->current_player_pieces &
        (b->current_player_pieces << 3) &
        (b->current_player_pieces >> 3)
    ) return 1;

    // Check a-i diagonal
    if (
        b->current_player_pieces &
        (b->current_player_pieces << 4) &
        (b->current_player_pieces >> 4) &
        0x010
    ) return 1;

    // Check c-g diagonal
    if (
        b->current_player_pieces &
        (b->current_player_pieces << 2) &
        (b->current_player_pieces >> 2) &
        0x010
    ) return 1;

    // No wins, return 0
    return 0;
}

int board_full(board *b)
{
    return !(b->mask ^ 0x1ff);
}

void invert_board(board *b)
{
    b->current_player_pieces ^= b->mask;
    b->current_player = !b->current_player;
}

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

void print_board(board *b)
{
    puts("  0   1   2");
    printf(
        "0 %c | %c | %c\n",
        get_piece_as_char(b, 0, 0),
        get_piece_as_char(b, 0, 1),
        get_piece_as_char(b, 0, 2)
    );
    puts(" ---+---+---");
    printf(
        "1 %c | %c | %c\n",
        get_piece_as_char(b, 1, 0),
        get_piece_as_char(b, 1, 1),
        get_piece_as_char(b, 1, 2)
    );
    puts(" ---+---+---");
    printf(
        "2 %c | %c | %c\n",
        get_piece_as_char(b, 2, 0),
        get_piece_as_char(b, 2, 1),
        get_piece_as_char(b, 2, 2)
    );
}

char get_piece_as_char(board *b, short row, short col)
{
    int piece_mask = generate_piece_mask(row, col);

    // If the mask is empty there, no piece is there
    if (!(b->mask & piece_mask))
        return ' ';

    // Otherwise, figure out whose piece is there
    if ((b->current_player_pieces & piece_mask)) {
        if (b->current_player) return 'x';
        return 'o';
    }

    if (b->current_player) return 'o';
    return 'x';
}