/*
 * $Id: queens.c,v 1.1 1994/03/16 15:56:39 urs Exp $
 *
 * Try to place n queens on a n by n chess board so that
 * no two queens attack each other.
 */

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE !FALSE

int unattacked(int x, int y);
void solve(int x);

int *pos;
int count = 0;
int dim   = 8;
int quiet = 0;

main(int argc, char **argv)
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

void solve(int x)
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


int unattacked(int x, int y)
{
	int i;

	for (i = 0; i < x; i++)
		if (y == pos[i] || abs(y - pos[i]) == x - i)
			return FALSE;
	return TRUE;
}
