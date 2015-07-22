/*
 * $Id: queens.c,v 1.10 2015/07/22 21:02:24 urs Exp $
 *
 * Try to place n queens on a n by n chess board so that
 * no two queens attack each other.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void solve(int *pos, int dim, int col, int uniq);
static int  attacked(const int *pos, int col, int row);
static int  checkdup(int *pos, int dim);
static void mirror(int *pos, int dim);
static void rotate(int *pos, int dim);
static int  cmp(const int *a, const int *b, int dim);
static void found(const int *pos, int dim);

int main(int argc, char **argv)
{
	int dim  = 8;
	int uniq = 0;
	int *pos;

	if (argc > 1 && strcmp(*++argv, "-u") == 0)
		--argc, ++argv, uniq = 1;
	if (argc > 1)
		dim = atoi(*argv);

	if (!(pos = malloc(dim * sizeof(int)))) {
		fputs("Insufficient memory.\n", stderr);
		exit(1);
	}

	solve(pos, dim, 0, uniq);

	free(pos);

	return 0;
}

static void solve(int *pos, int dim, int col, int uniq)
{
	int row;

	for (row = 0; row < dim; row++) {
		if (attacked(pos, col, row))
			continue;

		pos[col] = row;
		if (col < dim - 1)
			solve(pos, dim, col + 1, uniq);
		else if (uniq && checkdup(pos, dim))
			putchar('\n');
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

static int checkdup(int *pos, int dim)
{
	int min[dim], tmp[dim];
	int flag = 0;
	int i;

	memcpy(min, pos, sizeof(min));
	memcpy(tmp, min, sizeof(tmp));
	for (i = 0; i < 4; i++) {
		if (cmp(tmp, min, dim) < 0) {
			memcpy(min, tmp, dim * sizeof(int));
			flag = 1;
		}
		rotate(tmp, dim);
	}
	mirror(tmp, dim);
	for (i = 0; i < 4; i++) {
		if (cmp(tmp, min, dim) < 0) {
			memcpy(min, tmp, dim * sizeof(int));
			flag = 1;
		}
		rotate(tmp, dim);
	}
	return flag;
}

static void mirror(int *pos, int dim)
{
	int c;

	for (c = 0; c < dim; c++)
		pos[c] = dim - 1 - pos[c];
}

static void rotate(int *pos, int dim)
{
	int tmp[dim];
	int c, cc;

	for (c = 0; c < dim; c++) {
		for (cc = 0; cc < dim; cc++)
			if (pos[cc] == dim - 1 - c) {
				tmp[c] = cc;
				break;
			}
	}
	memcpy(pos, tmp, sizeof(tmp));
}

static int cmp(const int *a, const int *b, int dim)
{
	int c;
	int res;

	for (c = 0; c < dim; c++)
		if ((res = a[c] - b[c]) != 0)
			break;

	printf("cmp:");
	for (c = 0; c < dim; c++)
		printf(" %c%d", c + 'a', a[c] + 1);
	putchar(',');
	for (c = 0; c < dim; c++)
		printf(" %c%d", c + 'a', b[c] + 1);
	printf(": %d\n", res);

	return res;
}

static void found(const int *pos, int dim)
{
	int c;

	for (c = 0; c < dim; c++)
		printf("%c%d%c", c + 'a', pos[c] + 1,
		       c < dim - 1 ? ' ' : '\n');
}
