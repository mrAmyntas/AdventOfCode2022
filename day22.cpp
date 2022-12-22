#include <iostream>
#include <fstream>
#include <array>
#include <string.h>
#include <string>
#include <vector>

#define SIZE 205

enum {
	LEFT = 'L',
	RIGHT = 'R',
	UP = 'U',
	DOWN = 'D',
	WALL = '#',
	STEPS = 0,
	TURN = 1,
	EDGE = 0,
	A_TO_B = 0,
	A_TO_C = 1,
	A_TO_E = 2,
	A_TO_F = 3,
	B_TO_A = 4,
	B_TO_C = 5,
	B_TO_D = 6,
	B_TO_F = 7,
	C_TO_A = 8,
	C_TO_B = 9,
	C_TO_D = 10,
	C_TO_E = 11,
	D_TO_B = 12,
	D_TO_C = 13,
	D_TO_E = 14,
	D_TO_F = 15,
	E_TO_A = 16,
	E_TO_C = 17,
	E_TO_D = 18,
	E_TO_F = 19,
	F_TO_A = 20,
	F_TO_B = 21,
	F_TO_D = 22,
	F_TO_E = 23
};


/*
zones:
A (back):	col: 51 - 100  	row: 1 - 50
B (right):	col: 101 - 150	row: 1 - 50
C (top):	col: 51 - 100   row: 51 - 100
D (front):	col: 51 - 100	row: 101 - 150
E (left):	col: 1 - 50		row: 101 - 150
F (bottom):	col: 1 - 50		row: 151 - 200
*/

void parse_map(std::string line, int map[SIZE][SIZE], int row)
{
	std::string::iterator	it;
	int	col = 1;

	for ( it = line.begin(); it != line.end(); it++, col++) {
		if (*it == ' ')
			continue ;
		map[col][row] = *it;
	}
}

void parse_route(std::string line, std::vector<std::array<int, 2> > & route)
{
	std::string::iterator	it;
	size_t pos = 0, start = 0;

	for ( it = line.begin(); it != line.end(); it++, pos++) {
		if (isdigit(*it))
			continue;
		else
		{
			route.push_back(std::array<int, 2>({std::stoi(line.substr(start, pos - start)), *it}));
			start = pos + 1;
		}
	}
	route.push_back(std::array<int, 2>({std::stoi(line.substr(start, pos - start)), *it}));
}

int	find_border(int map[SIZE][SIZE], int x, int y, int x2, int y2)
{
	if (x >= 51 && x <= 100 && y <= 50) //in zone A
	{
		if (x2 == 50) 		//left to left side E
			return A_TO_E;
		else if (x2 == 101) //right to right side B
			return A_TO_B;
		else if (y2 == 0) 	//'up' to bottom F
			return A_TO_F;
		else if (y2 == 51) 	//'down' to top C
			return A_TO_C;
	}
	else if (x >= 101 && x <= 150 && y <= 50) //in zone B
	{
		if (x2 == 100) 		//left to back side A
			return B_TO_A;
		else if (x2 == 151) //right to front side D
			return B_TO_D;
		else if (y2 == 0) 	//'up' to bottom F
			return B_TO_F;
		else if (y2 == 51) 	//'down' to top C
			return B_TO_C;
	}
	else if (x >= 51 && x <= 100 && y >= 51 && y <= 100) //in zone C
	{
		if (x2 == 50) 		//left to left side E
			return C_TO_E;
		else if (x2 == 101) //right to right side B
			return C_TO_B;
		else if (y2 == 50) 	//'up' to back A
			return C_TO_A;
		else if (y2 == 101) //'down'  to front D
			return C_TO_D;
	}
	else if (x >= 51 && x <= 100 && y >= 101 && y <= 150) //in zone D
	{
		if (x2 == 50) 		//left to left side E
			return D_TO_E;
		else if (x2 == 101) //right to right side B
			return D_TO_B;
		else if (y2 == 100) //up to top C
			return D_TO_C;
		else if (y2 == 151) //down to bottom F
			return D_TO_F;
	}
	else if (x >= 1 && x <= 50 && y >= 101 && y <= 150) //in zone E
	{
		if (x2 == 0) 		//left to back side A
			return E_TO_A;
		else if (x2 == 51) 	//right to front side D
			return E_TO_D;
		else if (y2 == 100) ///up to top C
			return E_TO_C;
		else if (y2 == 151) //down to bottom F
			return E_TO_F;
	}
	else if (x >= 1 && x <= 50 && y >= 151 && y <= 200) //in zone F
	{
		if (x2 == 0) 		//left to back side A
			return F_TO_A;
		else if (x2 == 51) 	//right to front side D
			return F_TO_D;
		else if (y2 == 150) //'up' to left E
			return F_TO_E;
		else if (y2 == 201) //'down'  to right B
			return F_TO_B;
	}
	return -1;
}

int cross_border(int map[SIZE][SIZE], int border, int & row, int & col)
{
	if (border == A_TO_B)
	{
		col++;
		return RIGHT;
	}
	if (border == A_TO_C)
	{
		row++;
		return DOWN;
	}
	if (border == A_TO_E)
	{
		col = 1;
		row = 151 - row;
		return RIGHT;
	}
	if (border == A_TO_F)
	{
		row = col + 100;
		col = 1;
		return RIGHT;
	}
	if (border == B_TO_A)
	{
		col--;
		return LEFT;
	}
	if (border == B_TO_C)
	{
		row = col - 50;
		col = 100;
		return LEFT;
	}
	if (border == B_TO_D)
	{
		col = 100;
		row = 151 - row;
		return LEFT;
	}
	if (border == B_TO_F)
	{
		col = col - 100;
		row = 200;
		return UP;
	}
	if (border == C_TO_A)
	{
		row--;
		return UP;
	}
	if (border == C_TO_B)
	{
		col = row + 50;
		row = 50;
		return UP;
	}
	if (border == C_TO_D)
	{
		row++;
		return DOWN;
	}
	if (border == C_TO_E)
	{
		col = row - 50;
		row = 101;
		return DOWN;
	}
	if (border == D_TO_B)
	{
		col = 150;
		row = 151 - row;
		return LEFT;
	}
	if (border == D_TO_C)
	{
		row--;
		return UP;
	}
	if (border == D_TO_E)
	{
		col--;
		return LEFT;
	}
	if (border == D_TO_F)
	{
		row = col + 100;
		col = 50;
		return LEFT;
	}
	if (border == E_TO_A)
	{
		col = 51;
		row = 151 - row;
		return RIGHT;
	}
	if (border == E_TO_C)
	{
		row = col + 50;
		col = 51;
		return RIGHT;
	}
	if (border == E_TO_D)
	{
		col++;
		return RIGHT;
	}
	if (border == E_TO_F)
	{
		row++;
		return DOWN;
	}
	if (border == F_TO_A)
	{
		col = row - 100;
		row = 1;
		return DOWN;
	}
	if (border == F_TO_B)
	{
		col = col + 100;
		row = 1;
		return DOWN;
	}
	if (border == F_TO_D)
	{
		col = row - 100;
		row = 150;
		return UP;
	}
	if (border == F_TO_E)
	{
		row--;
		return UP;
	}
	return -1;
}

void solve_p1(int map[SIZE][SIZE], std::vector<std::array<int, 2> > route)
{
	std::vector<std::array<int, 2> >::iterator	r_it;
	std::string::iterator						it;
	int	pos, row = 1, col = 1, direction = RIGHT, password;

	for (; col < SIZE; col++) {
		if (map[col][row] != EDGE && map[col][row] != WALL)
			break;
	}

	for (r_it = route.begin(); r_it != route.end(); r_it++) {
		for ( int steps = (*r_it)[STEPS]; steps > 0; steps--) {
			if (direction == RIGHT && map[col + 1][row] != WALL)
			{
				if (map[col + 1][row] == EDGE)
				{
					pos = col;
					for (col = 0; col < SIZE; col++) {
						if (map[col][row] != EDGE)
							break;
					}
					if (map[col][row] == WALL)
						col = pos;
				}
				else
					col++;
			}
			else if (direction == LEFT && map[col - 1][row] != WALL)
			{
				if (map[col - 1][row] == EDGE)
				{
					pos = col;
					for (col = SIZE - 1; col >= 0; col--) {
						if (map[col][row] != EDGE)
							break;
					}
					if (map[col][row] == WALL)
						col = pos;
				}
				else
					col--;
			}
			else if (direction == UP && map[col][row - 1] != WALL)
			{
				if (map[col][row - 1] == EDGE)
				{
					pos = row;
					for (row = SIZE - 1; row >= 0; row--) {
						if (map[col][row] != EDGE)
							break;
					}
					if (map[col][row] == WALL)
						row = pos;
				}
				else
					row--;
			}
			else if (direction == DOWN && map[col][row + 1] != WALL)
			{
				if (map[col][row + 1] == EDGE)
				{
					pos = row;
					for (row = 0; row < SIZE; row++) {
						if (map[col][row] != EDGE)
							break;
					}
					if (map[col][row] == WALL)
						row = pos;
				}
				else
					row++;
			}
			else
				break ;
		}
		if ((direction == UP && (*r_it)[TURN] == LEFT) || (direction == DOWN && (*r_it)[TURN] == RIGHT))
			direction = LEFT;
		else if ((direction == UP && (*r_it)[TURN] == RIGHT) || (direction == DOWN && (*r_it)[TURN] == LEFT) )
			direction = RIGHT;
		else if ((direction == LEFT && (*r_it)[TURN] == LEFT) || (direction == RIGHT && (*r_it)[TURN] == RIGHT))
			direction = DOWN;
		else if ((direction == LEFT && (*r_it)[TURN] == RIGHT) || (direction == RIGHT && (*r_it)[TURN] == LEFT))
			direction = UP;
	}
	password = 1000 * row  + 4 * col;
	if (direction == DOWN)
		password++;
	if (direction == LEFT)
		password += 2;
	if (direction == UP)
		password += 3;
	std::cout << "p1:" << password << std::endl;
}

void solve_p2(int map[SIZE][SIZE], std::vector<std::array<int, 2> > route)
{
	std::vector<std::array<int, 2> >::iterator	r_it;
	std::string::iterator						it;
	int	row = 1, col = 1, direction = RIGHT, password, border, tmp_col, tmp_row, tmp_direction;

	for (; col < SIZE - 1; col++) {
		if (map[col][row] != EDGE && map[col][row] != WALL)
			break;
	}

	for (r_it = route.begin(); r_it != route.end(); r_it++) {
		for ( int steps = (*r_it)[STEPS]; steps > 0; steps--) {
			if (direction == RIGHT && map[col + 1][row] != WALL)
			{
				border = find_border(map, col, row, col + 1, row);
				if (border != -1)
				{
					tmp_col = col;
					tmp_row = row;
					tmp_direction = direction;
					direction = cross_border(map, border, row, col);
					if (map[col][row] == WALL)
					{
						col = tmp_col;
						row = tmp_row;
						direction = tmp_direction;
						break ;
					}
				}
				else
					col++;
			}
			else if (direction == LEFT && map[col - 1][row] != WALL)
			{
				border = find_border(map, col, row, col - 1, row);
				if (border != -1)
				{
					tmp_col = col;
					tmp_row = row;
					tmp_direction = direction;
					direction = cross_border(map, border, row, col);
					if (map[col][row] == WALL)
					{
						col = tmp_col;
						row = tmp_row;
						direction = tmp_direction;
						break ;
					}
				}
				else
					col--;
			}
			else if (direction == UP && map[col][row - 1] != WALL)
			{
				border = find_border(map, col, row, col, row - 1);
				if (border != -1)
				{
					tmp_col = col;
					tmp_row = row;
					tmp_direction = direction;
					direction = cross_border(map, border, row, col);
					if (map[col][row] == WALL)
					{
						col = tmp_col;
						row = tmp_row;
						direction = tmp_direction;
						break ;
					}
				}
				else
					row--;
			}
			else if (direction == DOWN && map[col][row + 1] != WALL)
			{
				border = find_border(map, col, row, col, row + 1);
				if (border != -1)
				{
					tmp_col = col;
					tmp_row = row;
					tmp_direction = direction;
					direction = cross_border(map, border, row, col);
					if (map[col][row] == WALL)
					{
						col = tmp_col;
						row = tmp_row;
						direction = tmp_direction;
						break ;
					}
				}
				else
					row++;
			}
			else
				break ;
		}
		if ((direction == UP && (*r_it)[TURN] == LEFT) || (direction == DOWN && (*r_it)[TURN] == RIGHT))
			direction = LEFT;
		else if ((direction == UP && (*r_it)[TURN] == RIGHT) || (direction == DOWN && (*r_it)[TURN] == LEFT) )
			direction = RIGHT;
		else if ((direction == LEFT && (*r_it)[TURN] == LEFT) || (direction == RIGHT && (*r_it)[TURN] == RIGHT))
			direction = DOWN;
		else if ((direction == LEFT && (*r_it)[TURN] == RIGHT) || (direction == RIGHT && (*r_it)[TURN] == LEFT))
			direction = UP;
	}
	password = 1000 * row + 4 * col;
	if (direction == DOWN)
		password++;
	if (direction == LEFT)
		password += 2;
	if (direction == UP)
		password += 3;
	std::cout << "p2:" << password << std::endl;
}

int main(void)
{
	std::ifstream						ifs("input");
	std::string							line = "line";
	int 								map[SIZE][SIZE], row = 1;
	std::vector<std::array<int, 2> >	route;

	memset(map, 0, sizeof(map));
	for (std::getline(ifs, line); line != ""; std::getline(ifs, line), row++) {
		parse_map(line, map, row);
	}
	std::getline(ifs, line);
	parse_route(line, route);
	solve_p1(map, route);
	solve_p2(map, route);
	return 0;
}
