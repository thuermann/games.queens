/*
 * $Id: queens.c,v 1.2 2015/07/22 20:57:33 urs Exp $
 *
 * Try to place n queens on a n by n chess board so that
 * no two queens attack each other.
 */

#include <stdio.h>
#include <stdlib.h>

static void solve(int x);
static int  unattacked(int x, int y);

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

static void solve(int x)
{
	int y, px;

	for (y = 0; y < dim; y++)
		if (unattacked(x, y)) {
			pos[x] = y;
			if (x < dim - 1)
				solve(x + 1);
			else {
				if (!quiet) {
					for (px = 0; px < dim; px++) {
						printf("%c%d ",
						       px + 'a', pos[px] + 1);
					}
					printf("\n");
				}
				count++;
			}
		}
}

static int unattacked(int x, int y)
{
	int i;

	for (i = 0; i < x; i++)
		if (y == pos[i] || abs(y - pos[i]) == x - i)
			return 0;
	return 1;
}
