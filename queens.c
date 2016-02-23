/*
 * $Id: queens.c,v 1.11 2016/02/23 23:26:12 urs Exp $
 *
 * Try to place n queens on a n by n chess board so that
 * no two queens attack each other.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void usage(const char *name)
{
	fprintf(stderr, "Usage: %s [-uv] [num]\n", name);
}

static void solve(int *pos, int dim, int col, int uniq);
static int  attacked(const int *pos, int col, int row);
static int  checkdup(int *pos, int dim);
static void mirror(int *pos, int dim);
static void rotate(int *pos, int dim);
static int  cmp(const int *a, const int *b, int dim);
static void print_board(const int *pos, int dim);

static int verbose = 0;

int main(int argc, char **argv)
{
	int dim  = 8;
	int uniq = 0;
	int *pos;
	int opt, errflag = 0;

	while ((opt = getopt(argc, argv, "uv")) != -1) {
		switch (opt) {
		case 'u':
			uniq = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			errflag = 1;
			break;
		}
	}
	if (errflag || argc - optind > 1) {
		usage(argv[0]);
		exit(1);
	}

	if (optind < argc)
		dim = atoi(argv[optind]);

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
		else if (!uniq || !checkdup(pos, dim)) {
			print_board(pos, dim);
			putchar('\n');
		}
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
	int res, i;

	memcpy(min, pos, sizeof(min));
	memcpy(tmp, min, sizeof(tmp));
	for (i = 0; i < 8; i++) {
		if (i == 4)
			mirror(tmp, dim);
		res = cmp(tmp, min, dim);
		if (verbose) {
			printf("cmp: ");
			print_board(tmp, dim);
			printf(", ");
			print_board(min, dim);
			printf(": %d\n", res);
		}
		if (res < 0) {
			memcpy(min, tmp, sizeof(min));
			flag = 1;
		}
		rotate(tmp, dim);
	}
	if (flag && verbose)
		putchar('\n');

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

	return res;
}

static void print_board(const int *pos, int dim)
{
	int c;

	for (c = 0; c < dim; c++)
		printf(c == 0 ? "%c%d" : " %c%d", c + 'a', pos[c] + 1);
}
