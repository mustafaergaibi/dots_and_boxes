CC     = gcc
CFLAGS = -Wall -Wextra -g -I.

OBJS = main.o game.o board.o display.o input.o

.PHONY: all test clean

all: dots

dots: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o:    main.c game.h
game.o:    game.c game.h board.h display.h input.h
board.o:   board.c board.h
display.o: display.c display.h board.h
input.o:   input.c input.h

test_board: tests/test_board.c board.c board.h
	$(CC) $(CFLAGS) tests/test_board.c board.c -o $@

test: test_board
	./test_board

clean:
	rm -f *.o dots test_board
