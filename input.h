#ifndef INPUT_H
#define INPUT_H

/* ---- Implemented by teammate in input.c ---- */

#define INPUT_OK   1   /* four integers were read */
#define INPUT_BAD  0   /* line was not four integers (letters, too few numbers...) */
#define INPUT_EOF -1   /* end of input (Ctrl+D or end of a piped file) */

/* Reads one line (use fgets + sscanf, not bare scanf) and parses "r1 c1 r2 c2".
 * Range/adjacency checks are NOT done here; board_is_valid_move does those. */
int read_move(int *r1, int *c1, int *r2, int *c2);

#endif
