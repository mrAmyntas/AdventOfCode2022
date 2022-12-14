#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//ran it first to find the min and max values of the rocks
//then to make my grid i take x_min one smaller and x_max one higher
//then i calculate the sand that is dropped there, it then
//misses the sides of the sand piramyd, but these can then
//be calculated afterwards much faster by using info when row is 
//completely filled with sand -> every extra row under that will
//have 1 extra sand to side (+1, +2, +3, until floor)

int full_left = 0;
int full_right = 0;

//real input

int y_min = 0;
int y_max = 168;
int x_min = 446;
int x_max = 516;

//test input

// int y_min = 0;
// int y_max = 9;
// int x_min = 493;
// int x_max = 504;

struct point {
	int x;
	int y;
	int type;
} ;


void	setRocks(std::string & line, std::vector<point> & grid)
{
	std::string::iterator	it;
	size_t					pos = 0, pos2 = 0, pos3 = 0;
	int						x1, y1, x2, y2, i = 0;
	point					new_point;

	for (pos2 = line.find("->", pos); pos2 != std::string::npos; i++) {
		//get x and y of the two end points of rock line
		pos3 = line.find(",", pos); 	
		x1 = std::stoi ( line.substr ( pos, (pos3 - pos) ) );
		y1 = std::stoi ( line.substr( pos3 + 1, pos2 - 1 ) );
		//set first point
		if (i == 0)
		{
			new_point.x = x1;
			new_point.y = y1;
			new_point.type = '#';
			grid.push_back(new_point);
		}
		//set point 2 -> point 1 
		pos3 = line.find(",", pos2);
		x2 = std::stoi ( line.substr( pos2 + 3, pos3 - ( pos2 + 3 ) ) );
		pos2 = line.find(" ", pos3);
		y2 = std::stoi ( line.substr( pos3 + 1, pos2 - ( pos3 + 1 ) ) );
		// find lowest values
		// if (y1 > y_min)
		// 	y_min = y1;
		// if (y2 > y_min)
		// 	y_min = y2;
		// if (x1 < x_min)
		// 	x_min = x1;
		// if (x2 < x_min)
		// 	x_min = x2;
		// if (x1 > x_max)
		// 	x_max = x1;
		// if (x2 > x_max)
		// 	x_max = x2;

		if (x1 == x2)
		{
			if (y1 > y2)
			{
				for (; y1 > y2; y2++) {
					new_point.x = x2;
					new_point.y = y2;
					new_point.type = '#';
					grid.push_back(new_point);
				}

			}
			else
			{
				for (; y2 > y1; y2--) {
					new_point.x = x2;
					new_point.y = y2;
					new_point.type = '#';
					grid.push_back(new_point);
				}
			}
		}
		else
		{
			if (x1 > x2)
			{
				for (; x1 > x2; x2++) {
					new_point.x = x2;
					new_point.y = y1;
					new_point.type = '#';
					grid.push_back(new_point);
				}

			}
			else
			{
				for (; x2 > x1; x2--) {
					new_point.x = x2;
					new_point.y = y1;
					new_point.type = '#';
					grid.push_back(new_point);
				}
			}
		}
		//go to next pair
		pos = line.find("->", pos) + 3;
		pos2 = line.find("->", pos);
	}
}

bool isRock(int x, int y, std::vector<point> & grid)
{
	std::vector<point>::iterator it;

	for (it = grid.begin(); it != grid.end(); it++) {
		if ((*it).x == x &&  (*it).y == y && (*it).type == '#')
			return true ;
	}
	return false ;
}

void printType(int x, int y, std::vector<point> & grid)
{
	std::vector<point>::iterator it;

	for (it = grid.begin(); it != grid.end(); it++) {
		if ((*it).x == x &&  (*it).y == y)
		{
			std::cout << (char)(*it).type;
			break ; //dupes
		}
	}
}
void printGrid( std::vector<point> & grid )
{
	int x, y;
 
	for (y = y_min; y <= (y_max + 2); y++) {
		for (x = x_min; x <= x_max; x++) {
			printType(x, y, grid);
		}
		std::cout << std::endl;
	}

}

void	fillAir( std::vector<point>	& grid )
{
	int x, y;
 
	for (y = y_min; y <= y_max; y++) {
		for (x = x_min; x<= x_max; x++) {
			if (!isRock(x, y, grid))
			{
				point new_point;
				new_point.x = x;
				new_point.y = y;
				new_point.type = '.';
				grid.push_back(new_point);
			}
		}
	}
}

int where_next(int x, int y, std::vector<point> & grid)
{
	std::vector<point>::iterator it, it2;
	int ret[2] = {-1, -1};


	for ( it = grid.begin(); it != grid.end(); it++){
		if ((*it).x == x &&  (*it).y == y)
			it2 = it;
		if ((*it).x == x &&  (*it).y == y + 1 && (*it).type == '.')
			return 0; //down
		if ((*it).x == x - 1 && (*it).y == y + 1)
		{
			ret[0] = 0;
			if ((*it).type == '.')
				ret[0] = 1;
		}
		if ((*it).x == x + 1 &&  (*it).y == y + 1)
		{
			ret[1] = 0;
			if ((*it).type == '.')
				ret[1] = 1;
		}
	}
	if (ret[0] == -1)
		full_left = y;
	if (ret[1] == -1)
		full_right = y;
	if (ret[0] == 1)
		return 1; //down left
	if (ret[1] == 1)
		return 2; //down right
	(*it2).type = 'o';
	if ((*it2).x == 500 && (*it2).y == 0) //reached top
		return -2;
	return -1; //landed
}

int dropSand(std::vector<point> & grid)
{
	std::vector<point>::iterator it = grid.begin(); //start is first!
	int x, y, i = 0, next;

	x = (*it).x;
	y = (*it).y;
	//try loop
	while (1)
	{
		next = where_next(x, y, grid);
		if (next == -2)
			break ;
		if (next == -1)
		{
			x = (*it).x;
			y = (*it).y;
			i++;
			continue ;
		}
		if (next == 1)
			x--;
		else if (next == 2)
			x++;
		y++;
	}
	return i + 1; //+1 to count the start '+'

}

void setFloor(std::vector<point> & grid, int floor)
{
	point new_point;
	new_point.y = floor;
	new_point.type = '#';
	for (int x = x_min; x <= x_max; x++) {
		new_point.x = x;
		grid.push_back(new_point);
	}
	new_point.y = floor - 1;
	new_point.type = '.';
	for (int x = x_min; x <= x_max; x++) {
		new_point.x = x;
		grid.push_back(new_point);
	}
}
int main (void)	
{
	std::ifstream			ifs("tinput");
	std::string				line;
	std::vector<point>		grid;
	int						sand_count = 0;
	point start;
	start.x = 500;
	start.y = 0;
	start.type = '+';
	grid.push_back(start);

	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line)) {
		setRocks(line, grid);
	}
	fillAir(grid);
	int floor = y_max + 2;
	setFloor(grid, floor);
	sand_count = dropSand(grid);
	printGrid(grid);

	int i = (floor - 1) - (full_left + 1) + 1;
	for (int n = 0; n < i; n++) {
		sand_count = sand_count + n + 1;
	}
	i = (floor - 1) - (full_right + 1) + 1;
	for (int n = 0; n < i; n++) {
		sand_count = sand_count + n + 1;
	}
	std::cout << sand_count << std::endl;
	return 0;
}
