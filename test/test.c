/**
 * Test suite entry point
 * (c) Yuta Nagano
 */
#include <stdio.h>
#include "test_board.h"

int main()
{
    puts("Running tests...");

    // Run unit tests
    test_board();

    puts("Tests finished. No errors found.");
}