/**
 * Runtime loop to play a simple tic-tac-toe game with two players.
 * (c) Yuta Nagano
 */
#include <stdio.h>
#include <string.h>
#include "board.h"

void play_game();
void clear_stdin();
int get_coordinate_from_stdin();

int main()
{
    char input[3];
    int playing = 1;

    puts(
        "\
┏━━━━┓━━━━━━━━━━┏━━━━┓━━━━━━━━━━━━━┏━━━━┓━━━━━━━━\n\
┃┏┓┏┓┃━━━━━━━━━━┃┏┓┏┓┃━━━━━━━━━━━━━┃┏┓┏┓┃━━━━━━━━\n\
┗┛┃┃┗┛┏┓┏━━┓━━━━┗┛┃┃┗┛┏━━┓━┏━━┓━━━━┗┛┃┃┗┛┏━━┓┏━━┓\n\
━━┃┃━━┣┫┃┏━┛━━━━━━┃┃━━┗━┓┃━┃┏━┛━━━━━━┃┃━━┃┏┓┃┃┏┓┃\n\
━┏┛┗┓━┃┃┃┗━┓━━━━━┏┛┗┓━┃┗┛┗┓┃┗━┓━━━━━┏┛┗┓━┃┗┛┃┃┃━┫\n\
━┗━━┛━┗┛┗━━┛━━━━━┗━━┛━┗━━━┛┗━━┛━━━━━┗━━┛━┗━━┛┗━━┛\n\
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\
(c) Yuta Nagano\n"
    );

    while (playing) {
        printf("Play game? [Y/n]: ");
        fgets(input, 3, stdin);
        if (strlen(input) == 2 && input[1] != '\n')
            clear_stdin();

        switch (input[0]) {
        case 'y':
        case 'Y':
        case '\n':
            play_game();
            break;
        case 'n':
        case 'N':
            playing = 0;
            break;
        default:
            puts("Unrecognised input, please enter y/Y/n/N.");
        }
    }

    return 0;
}

void play_game()
{
    board b = {0, 0, 0};
    char player_symbols[2] = {'o', 'x'};
    char buffer[100];
    int row_input, col_input;

    while (1) {
        print_board(&b);
        printf("Current player: %c\n", player_symbols[b.current_player]);

        while (1) {
            puts("Enter coordinates to play.");
            printf("row: ");
            row_input = get_coordinate_from_stdin();
            printf("col: ");
            col_input = get_coordinate_from_stdin();

            if (place_piece(&b, row_input, col_input)) {
                printf(
                    "You can't play (%i,%i) as it is already occupied. ",
                    row_input,
                    col_input
                );
                puts("Try again.");
                continue;
            }

            break;
        }

        if (check_win(&b)) {
            print_board(&b);
            printf("%c is victorious!\n", player_symbols[b.current_player]);
            break;
        }

        if (board_full(&b)) {
            print_board(&b);
            puts("The game is tied.");
            break;
        }
        
        invert_board(&b);
    }
}

void clear_stdin()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF)
        /* discard */ ;
}

int get_coordinate_from_stdin()
{
    char buffer[6];
    int result;

    while (1) {
        // Read from stdin
        fgets(buffer, 6, stdin);
        // Clear stdin for any remaining characters if necessary
        if (strlen(buffer) == 5 && buffer[4] != '\n')
            clear_stdin();
        
        // Parse result, and return value if valid
        if (
            sscanf(buffer, "%d", &result) == 1 &&
            result >= 0 && result <= 2
        ) return result;
        
        // Otherwise ask user to try again
        printf(
            "Unrecognised coordinate- please enter number between 0 and 2: "
        );
    }
}