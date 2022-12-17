#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <math.h>
#include <limits.h>
#include <algorithm>

class valve {
	public:
		std::vector<std::string>	neighbors;
		int 		flowrate;
		std::string	name;
		int			dist;
		bool		open = false;
		bool		visited = false;
		int			index;
};


int	parse(std::string & line, std::vector<valve> & valves, int index)
{
	size_t	start, end;
	valve 	new_valve;

	start = line.find(" ") + 1;
	end = line.find(" ", start);
	new_valve.name = line.substr(start, end - start);
	start = line.find("=") + 1;
	end = line.find(";");
	new_valve.flowrate = std::stoi(line.substr(start, end - start));
	if (new_valve.flowrate != 0 || new_valve.name == "AA")
		new_valve.index = index;
	if ( line.find("valves") == std::string::npos )
		start = line.find("valve") + 6;
	else
		start = line.find("valves") + 7;
	while ( line.find(",", start) != std::string::npos )
	{
			end = line.find(",", start);
			new_valve.neighbors.push_back(line.substr(start, end - start));
			start = end + 2;
	}
	new_valve.neighbors.push_back(line.substr(start));
	valves.push_back(new_valve);
	if (new_valve.flowrate != 0 || new_valve.name == "AA")
		return 1;
	return 0;
}


void	considerNeighbors(valve & cur_valve, std::vector<valve> & valves)
{
	std::vector<std::string>::iterator		s_it;
	std::vector<valve>::iterator			v_it;
	int dist;

	for (s_it = cur_valve.neighbors.begin(); s_it != cur_valve.neighbors.end(); s_it++ ) {
		for (v_it = valves.begin();  v_it != valves.end(); v_it++) {
			if ((*v_it).name == *s_it && (*v_it).visited == false)
			{
				dist = cur_valve.dist + 1;
				if (dist < (*v_it).dist)
				{
					(*v_it).dist = dist;
					break ;
				}
			}
		}
	}
}

void	findDistances(std::vector<valve> & valves, std::map<std::pair<int, int>, int> & distances )
{
	std::vector<valve>::iterator	current, from, to, it;
	
	for (current = valves.begin(); current != valves.end(); current++) {
		for (to = valves.begin(); to != valves.end(); to++) {
			if ((*current).name == (*to).name || ((*to).flowrate == 0) || ((*current).flowrate == 0 && (*current).name != "AA") )
				continue ;
			for (it = valves.begin(); it != valves.end(); it++) {
				if ((*current).name == (*it).name)
				{
					(*it).dist = 0;
					from = it;
				}
				else
					(*it).dist = 9999999;
				(*it).visited = false;
			}
			while (1)
			{
				int smallest = 0;
				if ((*from).name == (*to).name)
					break ;
				considerNeighbors(*from, valves);
				(*from).visited = true;
				for (it = valves.begin(); it != valves.end(); ++it) {
					if ((*it).visited == false)
					{
						if (smallest > (*it).dist || smallest == 0)
						{
							smallest = (*it).dist;
							from = it;
						}
					}
				}
			}
			distances.insert(std::make_pair(std::pair<int, int>((*current).index, (*to).index ), (*to).dist));
		}
	}
}

int	rabbithole(int my_pos, int ele_pos, int my_time, int ele_time, std::vector<valve> & valves, std::map<std::pair<int, int>, int> & distances)
{
	std::vector<valve>::iterator 					v_it;
	std::map<std::pair<int, int>, int>::iterator	d_it;
	int max_pressure = 0, pressure = 0, remainder = 0;

	//no time no gains
	if (my_time <= 1 && ele_time <= 1)
		return 0;
	
	//go through all valves
	int i = 0;
	for (v_it = valves.begin(); v_it != valves.end(); v_it++, i++) {
		if ((*v_it).open == true)
			continue ;
		if (my_time >= ele_time)
		{
			d_it = distances.find(std::make_pair(my_pos, i));
			remainder = my_time - (*d_it).second - 1;
			(*v_it).open = true ;
			pressure = (*v_it).flowrate * remainder + rabbithole((*v_it).index, ele_pos, remainder, ele_time, valves, distances);
			if (pressure > max_pressure)
				max_pressure = pressure;
			(*v_it).open = false ;
		}
		else
		{
			d_it = distances.find(std::make_pair(ele_pos, i));
			remainder = ele_time - (*d_it).second - 1;
			(*v_it).open = true ;
			pressure = (*v_it).flowrate * remainder + rabbithole(my_pos, (*v_it).index, my_time, remainder, valves, distances);
			if (pressure > max_pressure)
				max_pressure = pressure;
			(*v_it).open = false ;
		}
	}
	return max_pressure;
}

void	deleteUseless(std::vector<valve> & valves)
{
	std::vector<valve>::iterator 							it;
	std::map<std::string, std::pair<int, int> >::iterator	m_it;

	for (it = valves.begin(); it != valves.end(); it++) {
		if ((*it).flowrate == 0 && (*it).index != 0)
		{
			valves.erase(it);
			it--;
		}
	}
}

int main(void)
{
	std::ifstream											ifs("input");
	std::string												line;
	std::vector<valve>										valves;
	std::map<std::pair<int, int>, int> 						distances;
	int 													index = 0;

	for (std::getline(ifs, line); !ifs.eof(); std::getline(ifs, line)) {
		index += parse(line, valves, index);
	}
	findDistances(valves, distances);
	deleteUseless(valves);
	std::cout << "p1:" << rabbithole(0, 0, 30, 0, valves, distances) << std::endl;
	std::cout << "p2:" << rabbithole(0, 0, 26, 26, valves, distances) << std::endl;
	return 0;
}
