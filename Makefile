all: main test

main: main.o board.o
	gcc main.o board.o -o tictactoe

main.o: src/main.c src/board.h
	gcc -c src/main.c -o main.o

test: test.o test_board.o board.o
	gcc test.o test_board.o board.o -o test_bin && ./test_bin

test.o: test/test.c test/test_board.h
	gcc -c test/test.c -o test.o

test_board.o: test/test_board.c test/test_board.h
	gcc -c test/test_board.c -o test_board.o

board.o: src/board.c src/board.h
	gcc -c src/board.c -o board.o