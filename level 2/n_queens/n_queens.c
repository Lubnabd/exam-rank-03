#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	valid(int *board, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if (col == board[i] || (board[i] - col == i - row) || (board[i] - col == row - i))
			return 0;
	}
	return 1;
}

void	solve(int size, int *board, int row)
{
	int col = 0;

	if (row == size) // found case last row
	{
		for (int i = 0; i < size; i++)
		{
			fprintf(stdout, "%d", board[i]);
			if (i < size - 1)
				fprintf(stdout , " ");
		}
		fprintf(stdout, "\n");
		return ;
	}
	while (col < size)
	{
		if (valid(board, row, col))
		{
			board[row] = col;
			solve(size, board, row + 1);
		}
		col++;
	}
}

int main (int argc , char **argv)
{
    if (argc != 2) /////
        return 1;

    int *board;
    int size =  atoi (argv[1]);

    if (size <= 0)
        return 1;

        board = calloc (size , sizeof(int)); /// 
        if (!board)
            return 1;
        solve(size, board, 0);
        free(board);
}

