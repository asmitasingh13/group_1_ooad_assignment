/*
 * number_swapper_game.c
 *
 * This program implements a simple game where the user enters a 3x3 grid
 * of numbers from 0 to 8, and the compute should arrange them from 1 to 9
 * by swapping a number with 0 in each move.
 *
 * (c) 2008, Nagesh Rao, CyberPlus Infotech Pvt. Ltd.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ok(int grid[3][3]);
int solve(int grid[3][3]);
int convert_to_position(int i, int j);
int get_position(int number, int grid[3][3]);
void swap(int position1, int position2, int grid[3][3]);
void display_grid(int grid[3][3]);

int main()
{
	int grid[3][3];
	int swaps;
	int i,j;

	do
	{
		printf("Enter the numbers (0-8) in the grid rowwise:");
		for (i=0; i<3; i++)
		{
			for (j=0; j<3; j++)
			{
				scanf("%d",&grid[i][j]);
			}
		}
		if (!ok(grid)) printf("Invalid input!\n");
	} while (!ok(grid));

	swaps = solve(grid);
	printf("Solution obtained after %d swaps!\n",swaps);
	exit(0);
}

/*
 * This function checks whether the given grid contains all digits from 0-8
 * and returns true if ok and false otherwise.
 *
 * The logic here is to put a "1" in a string at the slot belonging to a
 * digit and finally verifying that all the string contains 9 "1"s.
 *
 */
int ok(int grid[3][3])
{
	char pattern[10] = {0};
	int i,j;

	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			if (grid[i][j]>=0 && grid[i][j]<=8) pattern[convert_to_position(i,j)] = '1';
		}
	}

	return strncmp(pattern,"111111111",9) == 0;
}

/*
 * This function solves the problem and arranges the numbers in the right order
 *
 * The logic is as follows:
 * 1. For each number from 1 to 8, check whether it is in the right position
 * 2. If not, find out the number in the right place and swap that with 0
 *    This ensures that the number at the right place is now 0.
 * 3. Swap the current number with the 0.
 *    This ensures that the current number has gone to its right place.
 *
 * The function displays the grid after every swap and returns the number
 * of swaps.
 */
int solve(int grid[3][3])
{
	int pos;
	int number;
	int swaps=0;

	for (pos=0; pos<8; pos++)
	{
		number = pos+1; /* This is the number we are analyzing */

		if (get_position(number,grid) != pos)
		{
			/* Number is not in the correct position */

			/* Swap number in correct position with 0 */
			swap(pos, get_position(0,grid), grid);
			display_grid(grid);
			swaps++;

			/* Swap correct number with the 0 in the correct position */
			swap(get_position(number,grid), pos, grid);
			display_grid(grid);
			swaps++;
		}
	}

	return swaps;
}

/*
 * This function accepts the row number (i) and column number (j)
 * and returns the corresponding position from 0 to 8.
 */
int convert_to_position(int i, int j)
{
	return 3*i+j;
}

/*
 * This function returns a 0-based position of the given number within the
 * grid.
 *
 * Since validation has already taken place earlier, we do not have to
 * consider the case of the number not being present.
 */
int get_position(int number, int grid[3][3])
{
	int i,j;

	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			if (grid[i][j] == number) return convert_to_position(i,j);
		}
	}

	return 0; /* Will never happen, given here to eliminate warning! */
}

/*
 * This function swaps two cells within the grid.
 * The inputs are the sequential positions of the cell.
 */
void swap(int position1, int position2, int grid[3][3])
{
	int row1, col1, row2, col2;
	int temp;

	row1 = position1/3;
	col1 = position1%3;
	row2 = position2/3;
	col2 = position2%3;

	temp = grid[row1][col1];
	grid[row1][col1] = grid[row2][col2];
	grid[row2][col2] = temp;
}

/*
 * This function displays the grid contents
 */
void display_grid(int grid[3][3])
{
	int i,j;

	for (i=0; i<3; i++)
	{
		for (j=0; j<3; j++)
		{
			printf("%3d",grid[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}