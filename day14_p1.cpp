#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//ran it first with only setRocks to find the min and max values of the rocks

int y_min = 0;
int y_max = 170;
int x_min = 445;
int x_max = 517;

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
 
	for (y = y_min; y <= y_max; y++) {
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

// bool down_is_air(int x, int y, std::vector<point> & grid)
// {
// 	for (std::vector<point>::iterator it = grid.begin(); it != grid.end(); it++){
// 		if ((*it).x == x &&  (*it).y == y + 1 && (*it).type == '.')
// 			return true;
// 	}
// 	return false;
// }

// bool left_down_is_air(int x, int y, std::vector<point> & grid)
// {
// 	for (std::vector<point>::iterator it = grid.begin(); it != grid.end(); it++){
// 		if ((*it).x == x - 1 &&  (*it).y == y + 1 && (*it).type == '.')
// 			return true;
// 	}
// 	return false;
// }

// bool right_down_is_air(int x, int y, std::vector<point> & grid)
// {
// 	for (std::vector<point>::iterator it = grid.begin(); it != grid.end(); it++){
// 		if ((*it).x == x + 1 &&  (*it).y == y + 1 && (*it).type == '.')
// 			return true;
// 	}
// 	return false;
// }

void sand_rests(int x, int y, std::vector<point> & grid)
{
	for (std::vector<point>::iterator it = grid.begin(); it != grid.end(); it++){
		if ((*it).x == x  &&  (*it).y == y)
			(*it).type = 'o';
	}
}

int where_next(int x, int y, std::vector<point> & grid)
{
	int ret[2] = {0, 0};

	for (std::vector<point>::iterator it = grid.begin(); it != grid.end(); it++){
		if ((*it).x == x &&  (*it).y == y + 1 && (*it).type == '.')
			return 0; //down
		if ((*it).x == x - 1 &&  (*it).y == y + 1 && (*it).type == '.')
			ret[0] = 1;
		if ((*it).x == x + 1 &&  (*it).y == y + 1 && (*it).type == '.')
			ret[1] = 1;
	}
	if (ret[0] == 1)
		return 1; //down left
	if (ret[1] == 1)
		return 2; //down right
	return -1; //stuck
}


int dropSand(std::vector<point> & grid)
{
	std::vector<point>::iterator it = grid.begin(); //start is first!
	int x, y, i = 0;

	x = (*it).x;
	y = (*it).y;
	//try loop
	while (y < y_max)
	{
		int next = where_next(x, y, grid);
		if (next == -1)
		{
			sand_rests(x, y, grid);
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
	return i;

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
	printGrid(grid);
	sand_count = dropSand(grid);
	std::cout << sand_count << std::endl;
	return 0;
}

// ......+...
// ..........
// ..........
// ..........
// ....#...##
// ....#...#.
// ..###.o.#.
// .....ooo#.
// ....oooo#.
// #########.