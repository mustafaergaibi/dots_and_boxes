# Dots and Boxes (CMPS 241 Course Project)

Two-player console Dots and Boxes in C, on a 4x5 grid of boxes (5x6 dots).

Team: Mustafa Ergaibi, TEAMMATE NAME

## Build and run
    make            # builds ./dots
    ./dots          # play
    make test       # runs the board unit tests
    make clean

Enter a move as four numbers: row and column of the first dot, then of the
second dot. Example: `0 4 0 3`. Completing a box gives you another turn.

## Files
- board.h / board.c     - board data, move validation, box completion, scores
- game.h / game.c       - turn loop, extra turn on box completion, winner
- display.h / display.c - prints the board and scores
- input.h / input.c     - reads and parses a move line (fgets + sscanf)
- main.c                - entry point
- tests/test_board.c    - unit tests for board.c
- tests/full_game.txt   - every move of a full game, for testing:
      ./dots < tests/full_game.txt
      valgrind --leak-check=full ./dots < tests/full_game.txt > /dev/null
