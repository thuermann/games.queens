/*
 * $Id: queens.c,v 1.3 2015/07/22 20:57:43 urs Exp $
 *
 * Try to place n queens on a n by n chess board so that
 * no two queens attack each other.
 */

#include <stdio.h>
#include <stdlib.h>

static void solve(int col);
static int  unattacked(int col, int row);

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

	return 0;
}

static void solve(int col)
{
	int row, c;

	for (row = 0; row < dim; row++)
		if (unattacked(col, row)) {
			pos[col] = row;
			if (col < dim - 1)
				solve(col + 1);
			else {
				if (!quiet) {
					for (c = 0; c < dim; c++) {
						printf("%c%d ",
						       c + 'a', pos[c] + 1);
					}
					printf("\n");
				}
				count++;
			}
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
