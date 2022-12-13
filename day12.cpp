#include <iostream>
#include <fstream>
#include <vector>

int rows = 0, cols = 0;

class Coord {
	public:
		Coord(int x, int y, int h) : x(x), y(y), h(h){ };
		int 	x;
		int 	y;
		int		h;
		bool	visited = false;
		int		distance_from_S = 999999999;
};

void	consider_neighbours(Coord current, std::vector<Coord> & grid)
{
	std::vector<Coord>::iterator	v_it;
	//check if up is on grid
	if (current.y != 0)
	{
		//find the up neighbour
		for (v_it = grid.begin(); v_it != grid.end(); ++v_it ) {
			if ( current.x == (*v_it).x && current.y - 1 == (*v_it).y )
				break ;
		}
		//check if it isss not too high or already visited
		if ((*v_it).h <= current.h + 1 && (*v_it).visited == false)
		{
			//asssign new distance if shorter
			int distance_through_current = current.distance_from_S + 1;
			if ((*v_it).distance_from_S > distance_through_current )
				(*v_it).distance_from_S = distance_through_current;
		}
	}
	//check down
	if (current.y != rows)
	{
		for (v_it = grid.begin(); v_it != grid.end(); ++v_it ) {
			if ( current.x == (*v_it).x && current.y + 1 == (*v_it).y )
				break ;
		}
		if ((*v_it).h <= current.h + 1 && (*v_it).visited == false)
		{
			int distance_through_current = current.distance_from_S + 1;
			if ((*v_it).distance_from_S > distance_through_current )
				(*v_it).distance_from_S = distance_through_current;
		}
	}
	//check left
	if (current.x != 0)
	{
		for (v_it = grid.begin(); v_it != grid.end(); ++v_it ) {
			if ( current.x - 1 == (*v_it).x && current.y == (*v_it).y )
				break ;
		}
		if ((*v_it).h <= current.h + 1 && (*v_it).visited == false)
		{
			int distance_through_current = current.distance_from_S + 1;
			if ((*v_it).distance_from_S > distance_through_current )
				(*v_it).distance_from_S = distance_through_current;
		}
	}
	//check right
	if (current.x != cols)
	{
		for (v_it = grid.begin(); v_it != grid.end(); ++v_it ) {
			if ( current.x + 1 == (*v_it).x && current.y == (*v_it).y )
				break ;
		}
		if ((*v_it).h <= current.h + 1 && (*v_it).visited == false)
		{
			int distance_through_current = current.distance_from_S + 1;
			if ((*v_it).distance_from_S > distance_through_current )
				(*v_it).distance_from_S = distance_through_current;
		}
	}
}

void	downtherabbithole(std::vector<Coord> & grid)
{
	std::vector<Coord>::iterator next, current = grid.begin();
	int							 smallest;

	while ((*current).h != 'a' - 1)
		current++;
	while (1)
	{
		smallest = 0;
		if ((*current).h == 'z' + 1)
		{
			std::cout << "found it!: " << (*current).distance_from_S << std::endl;
			break ;
		}
		/* uncomment next 2 lines for p2 */
		// if ((*current).h == 'a')
		// 	(*current).distance_from_S = 0;
		consider_neighbours(*current, grid);
		(*current).visited = true ;
		for (next = grid.begin(); next != grid.end(); ++next) {
			if ((*next).visited == false)
			{
				if (smallest > (*next).distance_from_S || smallest == 0)
				{
					smallest = (*next).distance_from_S;
					current = next;
				}
			}
		}
	}
}

int main(void)
{
	std::ifstream					ifs("input");
	std::string						line;
	std::vector<Coord>				grid;
	int								x, y;
	std::string::iterator 			s_it;
	std::vector<Coord>::iterator 	v_it;

	//create nodes (coords)
	std::getline(ifs, line);
	for (y = 0; !ifs.eof(); std::getline(ifs, line)) {
		x = 0;
		for (s_it = line.begin(); s_it != line.end(); ++s_it) {
			if (*s_it == 'E')
				grid.push_back(Coord(x, y, 'z' + 1));
			else if (*s_it == 'S')
			{
				grid.push_back(Coord(x, y, 'a' - 1));
				grid.back().distance_from_S = 0;
			}
			else
				grid.push_back(Coord(x, y, *s_it));
			if (x > cols)
				cols = x;
			x++;
		}
		rows = y;
		y++;
	}
	downtherabbithole(grid);
	return 0;
}
