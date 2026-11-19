#include <stdio.h>
#include <string.h>
#include "input.h"

#define LINE_MAX_LEN 256

/* Discards the rest of a line that did not fit in the buffer, so an
 * over-long line is not read as several moves. */
static void discard_rest_of_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

int read_move(int *r1, int *c1, int *r2, int *c2) {
    char line[LINE_MAX_LEN];

    if (fgets(line, sizeof line, stdin) == NULL)
        return INPUT_EOF;

    /* buffer full and no newline -> the line was longer than the buffer */
    size_t len = strlen(line);
    if (len == sizeof line - 1 && line[len - 1] != '\n') {
        discard_rest_of_line();
        return INPUT_BAD;
    }

    if (sscanf(line, "%d %d %d %d", r1, c1, r2, c2) == 4)
        return INPUT_OK;
    return INPUT_BAD;
}
