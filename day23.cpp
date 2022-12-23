#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <string.h>

#define SIZE 200
#define ROUNDS 10
#define MIDDLEISH 60

enum {
	NORTH,
	SOUTH,
	WEST,
	EAST,
	ELF = '#',
	EMPTY = '.',
	GO_NORTH = 1,
	GO_SOUTH = 10,
	GO_WEST = 25,
	GO_EAST = 100
};

void print_grid(int grid[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			std::cout << (char)grid[j][i];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void fill_grids( int positions[SIZE][SIZE], int proposals[SIZE][SIZE] )
{
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			positions[col][row] = EMPTY;
			proposals[col][row] = 0;
		}
	}
}

void parse_map(std::string line, int grid[SIZE][SIZE], int row)
{
	std::string::iterator	it;
	int	col = MIDDLEISH;

	for ( it = line.begin(); it != line.end(); it++, col++) {
		grid[col][row] = *it;
	}
}

int validDirection(int direction, int col, int row, int positions[SIZE][SIZE], int proposals[SIZE][SIZE] )
{
	if (positions[col - 1][row] != ELF && positions[col - 1][row - 1] != ELF && positions[col - 1][row + 1] != ELF && positions[col + 1][row - 1] != ELF && positions[col + 1][row] != ELF && positions[col + 1][row + 1] != ELF && positions[col][row - 1] != ELF && positions[col][row + 1] != ELF)
		return 0;
	if (direction == NORTH && positions[col - 1][row - 1] != ELF && positions[col][row - 1] != ELF && positions[col + 1][row - 1] != ELF) 
		proposals[col][row - 1] += GO_NORTH;
	else if (direction == SOUTH && positions[col - 1][row + 1] != ELF && positions[col][row + 1] != ELF && positions[col + 1][row + 1] != ELF) 
		proposals[col][row + 1] += GO_SOUTH;
	else if (direction == WEST && positions[col - 1][row - 1] != ELF && positions[col - 1][row] != ELF && positions[col - 1][row + 1] != ELF) 
		proposals[col - 1][row] += GO_WEST;
	else if (direction == EAST && positions[col + 1][row - 1] != ELF && positions[col + 1][row] != ELF && positions[col + 1][row + 1] != ELF) 
		proposals[col + 1][row] += GO_EAST;
	else
		return 0;
	return 1;
}

void considerMoving(int direction, int positions[SIZE][SIZE], int proposals[SIZE][SIZE])
{
	int new_direction;

	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			if ( positions[col][row] == ELF )
			{
				for (int i = 0; i < 4; i++) {
					new_direction = (direction + i) % 4;
					if (validDirection(new_direction, col, row, positions, proposals))
						break ;
				}
			}
		}
	}
}

int	move( int positions[SIZE][SIZE], int proposals[SIZE][SIZE])
{
	int	moved = 0, proposal;

	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			proposal = proposals[col][row];
			if ( proposal == GO_NORTH || proposal == GO_SOUTH || proposal == GO_EAST || proposal == GO_WEST)
			{
				moved = 1;
				positions[col][row] = ELF;
				if (proposals[col][row] == GO_NORTH)
					positions[col][row + 1] = EMPTY;
				else if (proposals[col][row] == GO_SOUTH)
					positions[col][row - 1] = EMPTY;
				else if (proposals[col][row] == GO_WEST)
					positions[col + 1][row] = EMPTY;
				else if (proposals[col][row] == GO_EAST)
					positions[col - 1][row] = EMPTY;
			}
		}
	}
	memset(proposals, 0, sizeof(int) * SIZE * SIZE);
	if (moved == 0)
		return 0;
	return 1;
}

void	solve_p1(int positions[SIZE][SIZE])
{
	int	col_min = -1, col_max = -1;
	int	row_min = -1, row_max = -1;
	int empty_ground = 0;

	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			if (positions[col][row] == ELF)
			{
				if (col_min > col || col_min == -1)
					col_min = col;
				if (col_max < col || col_max == -1)
					col_max = col;
				if (row_min > row || row_min == -1)
					row_min = row;
				if (row_max < row || row_max == -1)
					row_max = row;
			}
		}
	}
	for (int row = row_min; row <= row_max; row++) {
		for (int col = col_min; col <= col_max; col++) {
			if (positions[col][row] == EMPTY)
				empty_ground++;
		}
	}
	std::cout << "p1:" << empty_ground << std::endl;
}


int main(void)
{
	std::ifstream	ifs("input");
	std::string		line;
	int				positions[SIZE][SIZE], proposals[SIZE][SIZE];
	int				row = MIDDLEISH;
	int				p2, order[4] = {NORTH, SOUTH, WEST, EAST};

	fill_grids(positions, proposals);
	for (std::getline(ifs, line); !ifs.eof(); std::getline(ifs, line), row++ ) {
		parse_map(line, positions, row);
	}
	for (int i = 0;; i++) {
		considerMoving( order[i % 4], positions, proposals );
		if (!move( positions, proposals))
		{
			std::cout << "p2:" << i + 1 << std::endl;
			break;
		}
		if (i == ROUNDS - 1)
			solve_p1(positions);
	}
}
