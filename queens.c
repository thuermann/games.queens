/*
 * $Id: queens.c,v 1.6 2015/07/22 20:58:13 urs Exp $
 *
 * Try to place n queens on a n by n chess board so that
 * no two queens attack each other.
 */

#include <stdio.h>
#include <stdlib.h>

static void solve(int col);
static int  unattacked(int col, int row);
static void found(void);

static int *pos;
static int count = 0;
static int dim   = 8;
static int quiet = 0;

int main(int argc, char **argv)
{
	if (argc > 1 && **++argv == '-')
		--argc, ++argv, quiet = 1;
	if (argc > 1)
		dim = atoi(*argv);

	if (!(pos = malloc(dim * sizeof(int)))) {
		fputs("Insufficient memory.\n", stderr);
		exit(1);
	}

	solve(0);

	printf("\nI found %d solutions\n", count);

	free(pos);

	return 0;
}

static void solve(int col)
{
	int row;

	for (row = 0; row < dim; row++)
		if (unattacked(col, row)) {
			pos[col] = row;
			if (col < dim - 1)
				solve(col + 1);
			else
				found();
		}
}

static int unattacked(int col, int row)
{
	int c;

	for (c = 0; c < col; c++)
		if (row == pos[c] || abs(row - pos[c]) == col - c)
			return 0;
	return 1;
}

static void found(void)
{
	if (!quiet) {
		int c;

		for (c = 0; c < dim; c++)
			printf("%c%d%c", c + 'a', pos[c] + 1,
			       c < dim - 1 ? ' ' : '\n');
	}
	count++;
}
