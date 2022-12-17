#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <math.h>
#include <limits.h>
#include <algorithm>
#include <set>
#include <array>
#include <string_view>

long int g_floor = 0;

struct mymap {
	mymap()
	{
		for (int i = 0; i < 7; i++) {
			grid.insert(std::make_pair( std::array<long int, 2>{ i, 0 }, 1 ) );
		}
	}
	std::map<std::array<long int, 2>, int> grid;
	void	drawMap(long int);
};

class Rock {
	public:
		Rock(int start_y) : start_y(start_y)
		{ 
		};

		long int pos[5][2];
		long int start_y;
		char shape;
		void setShape(long int shape_num);
		bool landed = false;
};

void	mymap::drawMap(long int height)
{
	int 				y, x;
	std::array<long int, 2>	array;

	for (y = height; y >= 0; y--) {
		for (x = 0; x < 7; x++) {
			array[0] = x;
			array[1] = y;
			if (this->grid.find(array) == this->grid.end())
				std::cout << ".";
			else
				std::cout << "#";
		}
		std::cout << std::endl;
	}
	std::cout << "-------------------------------\n";
}

void	Rock::setShape(long int shape_num)
{
	if (shape_num == 0)
	{
		shape = 'A';
		this->pos[0][0] = 2;
		this->pos[0][1] = start_y;
		this->pos[1][0] = 3;
		this->pos[1][1] = start_y;
		this->pos[2][0] = 4;
		this->pos[2][1] = start_y;
		this->pos[3][0] = 5;
		this->pos[3][1] = start_y;
		this->pos[4][0] = -1;
		this->pos[4][1] = -1;
	}
	if (shape_num == 1)
	{
		shape = 'B';
		this->pos[0][0] = 3;
		this->pos[0][1] = start_y;
		this->pos[1][0] = 2;
		this->pos[1][1] = start_y + 1;
		this->pos[2][0] = 3;
		this->pos[2][1] = start_y + 1;
		this->pos[3][0] = 4;
		this->pos[3][1] = start_y + 1;
		this->pos[4][0] = 3;
		this->pos[4][1] = start_y + 2;
	}
	if (shape_num == 2)
	{
		shape = 'C';
		this->pos[0][0] = 2;
		this->pos[0][1] = start_y;
		this->pos[1][0] = 3;
		this->pos[1][1] = start_y;
		this->pos[2][0] = 4;
		this->pos[2][1] = start_y;
		this->pos[3][0] = 4;
		this->pos[3][1] = start_y + 1;
		this->pos[4][0] = 4;
		this->pos[4][1] = start_y + 2;
	}
	if (shape_num == 3)
	{
		shape = 'D';
		this->pos[0][0] = 2;
		this->pos[0][1] = start_y;
		this->pos[1][0] = 2;
		this->pos[1][1] = start_y + 1;
		this->pos[2][0] = 2;
		this->pos[2][1] = start_y + 2;
		this->pos[3][0] = 2;
		this->pos[3][1] = start_y + 3;
		this->pos[4][0] = -1;
		this->pos[4][1] = -1;
	}
	if (shape_num == 4)
	{
		shape = 'E';
		this->pos[0][0] = 2;
		this->pos[0][1] = start_y;
		this->pos[1][0] = 3;
		this->pos[1][1] = start_y;
		this->pos[2][0] = 2;
		this->pos[2][1] = start_y + 1;
		this->pos[3][0] = 3;
		this->pos[3][1] = start_y + 1;
		this->pos[4][0] = -1;
		this->pos[4][1] = -1;
	}
}

void	jetPush(Rock & Rock, std::string::iterator & it, mymap & map)
{
	// std::cout << Rock.pos[0][0] << std::endl;
	std::array<long int, 2> array;
	int i, n = 0, edge = 6, plus = 1;
	
	if (*it == '<')
	{ 
		edge = 0;
		plus = -1;
	}
	for (i = 0; i < 5; i++) {
		array[0] = Rock.pos[i][0] + plus;
		array[1] = Rock.pos[i][1];
		if (Rock.pos[i][0] == edge || map.grid.find(array) != map.grid.end())
			n = 1;
	}
	if (n == 0)
	{
		for (i = 0; i < 5; i++) {
			if (Rock.pos[i][0] != -1)
				Rock.pos[i][0] += plus;
		}
	}
	// std::cout << Rock.pos[0][0] << std::endl;
	it++;
}

void	dropRock(Rock & Rock, long int & height, mymap & map)
{

	std::map<std::array<long int, 2>, int>::iterator	it, it2;

	// std::cout << Rock.pos[0][0] << std::endl;
	std::array<long int, 2> array;
	int i, n = 0, y, x;
	
	for (i = 0; i < 5; i++) {
		array[0] = Rock.pos[i][0];
		array[1] = Rock.pos[i][1] - 1;
		if (map.grid.find(array) != map.grid.end())
			n = 1;
	}
	if (n == 0)
	{
		for (i = 0; i < 5; i++) {
			if (Rock.pos[i][0] != -1)
				Rock.pos[i][1] -= 1;
		}
	}
	else
	{
		Rock.landed = true;
		for (int i = 0; i < 5; i++) {
			if (Rock.pos[i][0] != -1)
			{
				if (height < Rock.pos[i][1])
					height = Rock.pos[i][1];
				map.grid.insert(std::make_pair( std::array<long int, 2>{ Rock.pos[i][0], Rock.pos[i][1] }, 1 ) );
			}
		}
		for (y = height; y >= g_floor; y--) {
			n = 0;
			for (x = 0; x < 7; x++) {
				array[0] = x;
				array[1] = y;
				if (map.grid.find(array) == map.grid.end())
				{
					n = 1;
					break ;
				}
			}
			if (n == 0)
				break ;
		}
		// std::cout << "height:" << height << std::endl;
		// std::cout << "y:" << y << std::endl;
		if (n == 0 && y > g_floor)
		{
			for (it = map.grid.begin(); it != map.grid.end();){
				it2 = it;
				it2++;
				if ((*it).first[1] < y)
				{
					// std::cout << (*it).first[0] << " " << (*it).first[1] << std::endl;
					map.grid.erase(it);
					it = it2;
					// std::cout << (*it).first[0] << " " << (*it).first[1] << std::endl;
				}
				else
					it++;
			}
			g_floor = y;

		}
	}
	// std::cout << Rock.pos[0][0] << std::endl;
}


int main(void)
{
	std::ifstream			ifs("input");
	std::string				input;
	std::string::iterator	it;
	mymap					map;
	long int height = 0, n_rocks = 1000000000000;
	long int i = 0, j = 0;

	std::getline(ifs, input);
	it = input.begin();
	while (i < n_rocks)
	{
		Rock newRock(height + 4);
		newRock.setShape(i % 5);
		while (!newRock.landed)
		{
			jetPush(newRock, it, map);
			if (it == input.end())
				it = input.begin();
			dropRock(newRock, height, map);
		}
		i++;
	}
	// map.drawMap(height);
	std::cout << "h:" << height << std::endl;
	return 0;
}

// The tall, vertical chamber is exactly seven units wide. 
// Each rock appears so that its left edge is two units away from the left wall 
// and its bottom edge is three units above the highest rock in the room 
// (or the floor, if there isn't one).

