#include <iostream>
#include <fstream>
#include <vector>

int row = 0, col = 0;

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
	if (current.y != row)
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
	if (current.x != col)
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
	int	smallest;

	while ((*current).h != 'a' - 1)
		current++;
	for (;;smallest = 0) {
		if ((*current).h == 'z' + 1)
			break ;
		// if ((*current).h == 'a')	/* uncomment for p2 */ 	
		// 	(*current).distance_from_S = 0; /* uncomment for p2 */ 	
		consider_neighbours(*current, grid);
		(*current).visited = true ;
		grid.erase(current);
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
	std::cout << "smallest path: " << (*current).distance_from_S << std::endl;
}

int main(void)
{
	std::ifstream					ifs("input");
	std::string						line;
	std::vector<Coord>				grid;

	//create nodes (coords)
	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line)) {
		col = 0;
		for (std::string::iterator s_it = line.begin(); s_it != line.end(); ++s_it, ++col) {
			if (*s_it == 'E')
				grid.push_back(Coord(col, row, 'z' + 1)); //ending one higher than z
			else if (*s_it == 'S')
			{
				grid.push_back(Coord(col, row, 'a' - 1)); //starting one lower than a
				grid.back().distance_from_S = 0;
			}
			else
				grid.push_back(Coord(col, row, *s_it));
		}
		row++;
	}
	downtherabbithole(grid);
	return 0;
}
