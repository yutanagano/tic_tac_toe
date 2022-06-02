/**
 * Unit tests for board.c
 * (c) Yuta Nagano
 */
#include <stdio.h>
#include <assert.h>
#include "test_board.h"
#include "../src/board.h"

void test_board()
{
    puts("Testing board.c...");

    // Run unit tests
    test_generate_piece_mask();
    test_is_legal_move();
    test_place_piece();
    test_invert_board();
    test_check_win();
    test_board_full();
}

void test_generate_piece_mask()
{
    fputs("\ttest_generate_piece_mask...", stdout);

    // Bitmask for piece at (0,0) should be 000000001, or 1
    assert(generate_piece_mask(0,0) == 1);
    // (0,1) should be 000000010, or 2
    assert(generate_piece_mask(0,1) == 2);
    // (0,2) should be 000000100, or 4
    assert(generate_piece_mask(0,2) == 4);
    // and so on
    assert(generate_piece_mask(1,1) == 16);
    assert(generate_piece_mask(2,2) == 256);

    puts("PASSED");
}

void test_is_legal_move()
{
    fputs("\ttest_is_legal_move...", stdout);

    /* Make board with the top row occupied by pieces, where the middle column
    is occupied by a current-player piece */
    board b = {
        .current_player_pieces = 0x002,
        .mask = 0x007
    };

    // Check various positions within board
    assert(!is_legal_move(&b, 0, 0));
    assert(!is_legal_move(&b, 0, 1));
    assert(!is_legal_move(&b, 0, 2));
    assert(is_legal_move(&b, 1, 0));
    assert(is_legal_move(&b, 1, 2));
    assert(is_legal_move(&b, 2, 1));

    // Out of bounds coordinates should always be illegal
    assert(!is_legal_move(&b, 0, 5));
    assert(!is_legal_move(&b, 3, 1));
    assert(!is_legal_move(&b, 2, -1));
    assert(!is_legal_move(&b, -4, 1));
    assert(!is_legal_move(&b, -3, -1));
    assert(!is_legal_move(&b, 3, 7));

    puts("PASSED");
}

void test_place_piece()
{
    fputs("\ttest_place_piece...", stdout);

    /* Make board with the top row occupied by pieces, where the middle column
    is occupied by a current-player piece */
    board b = {
        .current_player_pieces = 0x002,
        .mask = 0x007
    };

    // Try legal moves
    assert(!place_piece(&b, 1, 0));
    assert(b.current_player_pieces == 0x00a);
    assert(b.mask == 0x00f);
    b.current_player_pieces = 0x002;
    b.mask = 0x007;

    assert(!place_piece(&b, 2, 1));
    assert(b.current_player_pieces == 0x082);
    assert(b.mask == 0x087);
    b.current_player_pieces = 0x002;
    b.mask = 0x007;

    // Try illegal moves
    assert(place_piece(&b, 0, 0));
    assert(b.current_player_pieces == 0x002);
    assert(b.mask == 0x007);

    assert(place_piece(&b, 0, 1));
    assert(b.current_player_pieces == 0x002);
    assert(b.mask == 0x007);

    assert(place_piece(&b, 0, 2));
    assert(b.current_player_pieces == 0x002);
    assert(b.mask == 0x007);

    assert(place_piece(&b, 5, 5));
    assert(b.current_player_pieces == 0x002);
    assert(b.mask == 0x007);

    assert(place_piece(&b, -1, -2));
    assert(b.current_player_pieces == 0x002);
    assert(b.mask == 0x007);

    puts("PASSED");
}

void test_invert_board()
{
    fputs("\ttest_invert_board...", stdout);

    /* Make board with the top row occupied by pieces, where the middle column
    is occupied by a current-player piece */
    board b = {
        .current_player_pieces = 0x002,
        .mask = 0x007,
        .current_player = 1
    };

    // Test
    invert_board(&b);
    assert(b.current_player_pieces == 0x005);
    assert(b.mask == 0x007);
    assert(b.current_player == 0);

    invert_board(&b);
    assert(b.current_player_pieces == 0x002);
    assert(b.mask == 0x007);
    assert(b.current_player == 1);

    puts("PASSED");
}

void test_check_win()
{
    fputs("\ttest_check_win...", stdout);

    board b;
    
    // Horizontal win
    b.current_player_pieces = 0x038;
    b.mask = 0x13b;
    assert(check_win(&b));

    // Vertical win
    b.current_player_pieces = 0x049;
    b.mask = 0x05f;
    assert(check_win(&b));

    // a-i diagonal win
    b.current_player_pieces = 0x111;
    b.mask = 0x11f;
    assert(check_win(&b));

    // c-g diagonal win
    b.current_player_pieces = 0x054;
    b.mask = 0x05f;
    assert(check_win(&b));
    
    // No win on these boards
    b.current_player_pieces = 0x002;
    b.mask = 0x007;
    assert(!check_win(&b));

    b.current_player_pieces = 0x00b;
    b.mask = 0x05f;
    assert(!check_win(&b));

    b.current_player_pieces = 0x08c;
    b.mask = 0x09f;
    assert(!check_win(&b));

    b.current_player_pieces = 0x00e;
    b.mask = 0x03f;
    assert(!check_win(&b));

    puts("PASSED");
}

void test_board_full()
{
    fputs("\ttest_board_full...", stdout);

    board b;

    // Test full board
    b.current_player_pieces = 0x0b5;
    b.mask = 0x1ff;
    assert(board_full(&b));

    // Test non-full boards
    b.mask = 0x0ff;
    assert(!board_full(&b));

    b.current_player_pieces = 0x013;
    b.mask = 0x03f;
    assert(!board_full(&b));

    puts("PASSED");
}