# Tic Tac Toe implemented in C

This is a simple C implementation of a [tic tac toe](https://en.wikipedia.org/wiki/Tic-tac-toe)
game. It is played on the command line between two players on the same machine.
The project does not currently provide any AI players to play against.

The game is played by entering the coordinates you wish to play on the command
line. The board is zero-indexed on both the row and column axis, as shown in
the example game output below.

    ┏━━━━┓━━━━━━━━━━┏━━━━┓━━━━━━━━━━━━━┏━━━━┓━━━━━━━━
    ┃┏┓┏┓┃━━━━━━━━━━┃┏┓┏┓┃━━━━━━━━━━━━━┃┏┓┏┓┃━━━━━━━━
    ┗┛┃┃┗┛┏┓┏━━┓━━━━┗┛┃┃┗┛┏━━┓━┏━━┓━━━━┗┛┃┃┗┛┏━━┓┏━━┓
    ━━┃┃━━┣┫┃┏━┛━━━━━━┃┃━━┗━┓┃━┃┏━┛━━━━━━┃┃━━┃┏┓┃┃┏┓┃
    ━┏┛┗┓━┃┃┃┗━┓━━━━━┏┛┗┓━┃┗┛┗┓┃┗━┓━━━━━┏┛┗┓━┃┗┛┃┃┃━┫
    ━┗━━┛━┗┛┗━━┛━━━━━┗━━┛━┗━━━┛┗━━┛━━━━━┗━━┛━┗━━┛┗━━┛
    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    (c) Yuta Nagano

    Play game? [Y/n]: y
      0   1   2
    0   |   |  
     ---+---+---
    1   |   |  
     ---+---+---
    2   |   |  
    Current player: o
    Enter coordinates to play.
    row: 0
    col: 0
      0   1   2
    0 o |   |  
     ---+---+---
    1   |   |  
     ---+---+---
    2   |   |  
    Current player: x
    Enter coordinates to play.
    row: 1
    col: 1
      0   1   2
    0 o |   |  
     ---+---+---
    1   | x |  
     ---+---+---
    2   |   |  
    Current player: o
    Enter coordinates to play.
    row: 2
    col: 2
      0   1   2
    0 o |   |  
     ---+---+---
    1   | x |  
     ---+---+---
    2   |   | o
    Current player: x
    Enter coordinates to play.
    row: 0
    col: 2

    ...

      0   1   2
    0 o |   | x
     ---+---+---
    1 x | x |  
     ---+---+---
    2 o | o | o
    o is victorious!
    Play game? [Y/n]:

## Building

### Using make

If you have [gcc](https://en.wikipedia.org/wiki/GNU_Compiler_Collection) and
[make](https://en.wikipedia.org/wiki/Make_(software)) installed on your system,
you can just clone this repo, go into the project root directory on a terminal
and type:

    make

This will compile both an executable game program (called `tictactoe`) as well
as a test suite (called `test_bin`) which will automatically be run on the
command line.

> NOTE: As long as the last line of the output of the above command is `Tests
> finished. No errors found.`, then all the tests are passing. The program
> should work with no problems.

Then, the game program can be executed with the following command:

    ./tictactoe

### Manual build

Using any modern C compiler such as
[gcc](https://en.wikipedia.org/wiki/GNU_Compiler_Collection), compile together
the following c source files:

    gcc src/main.c src/board.c -o tictactoe