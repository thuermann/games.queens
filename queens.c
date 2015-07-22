/*
 * $Id: queens.c,v 1.9 2015/07/22 20:58:43 urs Exp $
 *
 * Try to place n queens on a n by n chess board so that
 * no two queens attack each other.
 */

#include <stdio.h>
#include <stdlib.h>

static void solve(int *pos, int dim, int col);
static int  attacked(const int *pos, int col, int row);
static void found(const int *pos, int dim);

int main(int argc, char **argv)
{
	int dim = 8;
	int *pos;

	if (argc > 1)
		dim = atoi(*++argv);

	if (!(pos = malloc(dim * sizeof(int)))) {
		fputs("Insufficient memory.\n", stderr);
		exit(1);
	}

	solve(pos, dim, 0);

	free(pos);

	return 0;
}

static void solve(int *pos, int dim, int col)
{
	int row;

	for (row = 0; row < dim; row++) {
		if (attacked(pos, col, row))
			continue;

		pos[col] = row;
		if (col < dim - 1)
			solve(pos, dim, col + 1);
		else
			found(pos, dim);
	}
}

static int attacked(const int *pos, int col, int row)
{
	int c;

	for (c = 0; c < col; c++)
		if (row == pos[c] || abs(row - pos[c]) == col - c)
			return 1;
	return 0;
}

static void found(const int *pos, int dim)
{
	int c;

	for (c = 0; c < dim; c++)
		printf("%c%d%c", c + 'a', pos[c] + 1,
		       c < dim - 1 ? ' ' : '\n');
}
