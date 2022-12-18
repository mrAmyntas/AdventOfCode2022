#include <iostream>
#include <fstream>
#include <map>
#include <array>

int x_max = 0;
int z_max = 0;
int y_max = 0;

void parse(std::string line, std::map<std::array<int, 3>, char> & m3dgrid)
{
	size_t pos, pos2;
	std::array<int, 3> array;

	pos = line.find(",");
	array[0] = std::stoi(line.substr(0, pos));
	if (array[0] + 1 > x_max)
		x_max = array[0] + 1;
	pos += 1;
	pos2 = line.find(",", pos);
	array[1] = std::stoi(line.substr(pos, pos2 - pos));
	if (array[1] + 1 > y_max)
		y_max = array[1] + 1;
	pos2 += 1;
	array[2] = std::stoi(line.substr(pos2));
	if (array[2] + 1 > z_max)
		z_max = array[2] + 1;
	m3dgrid.insert(std::make_pair(array, 'l'));
}

int amount_sides_touch_steam(std::map<std::array<int, 3>, char> & m3dgrid, std::array<int, 3> start)
{
	std::map<std::array<int, 3>, char>::iterator it;
	std::array<int, 3> up({start[0], start[1] + 1, start[2]});
	std::array<int, 3> down({start[0], start[1] - 1, start[2]});
	std::array<int, 3> left({start[0] - 1, start[1], start[2]});
	std::array<int, 3> right({start[0] + 1, start[1], start[2]});
	std::array<int, 3> forward({start[0], start[1], start[2] + 1});
	std::array<int, 3> back({start[0], start[1], start[2] - 1});
	int amount = 0;

	if (up[1] <= y_max)
	{
		it = m3dgrid.find(up);
		if ((*it).second == 's')
			amount++;
	}
	if (down[1] >= -1)
	{
		it = m3dgrid.find(down);
		if ((*it).second == 's')
			amount++;
	}
	if (left[0] >= -1)
	{
		it = m3dgrid.find(left);
		if ((*it).second == 's')
			amount++;
	}
	if (right[0] <= x_max)
	{
		it = m3dgrid.find(right);
		if ((*it).second == 's')
			amount++;
	}
	if (forward[2] <= z_max)
	{
		it = m3dgrid.find(forward);
		if ((*it).second == 's')
			amount++;
	}
	if (back[2] >= -1)
	{
		it = m3dgrid.find(back);
		if ((*it).second == 's')
			amount++;
	}
	return amount;
}


void	fill_grid_with_air(std::map<std::array<int, 3>, char> & m3dgrid)
{
	for (int i = -1; i <= x_max; i++) {
		for (int j = -1; j <= y_max; j++) {
			for (int k = -1; k <= z_max; k++) {
				m3dgrid.insert(std::make_pair(std::array<int, 3>({i,j,k}), 'a'));
			}
		}
	}
}


void	let_there_be_steam(std::map<std::array<int, 3>, char> & m3dgrid, std::array<int, 3> start)
{
	std::map<std::array<int, 3>, char>::iterator	it;
	int x, y, z;
	std::array<int, 3> up({start[0], start[1] + 1, start[2]});
	std::array<int, 3> down({start[0], start[1] - 1, start[2]});
	std::array<int, 3> left({start[0] - 1, start[1], start[2]});
	std::array<int, 3> right({start[0] + 1, start[1], start[2]});
	std::array<int, 3> forward({start[0], start[1], start[2] + 1});
	std::array<int, 3> back({start[0], start[1], start[2] - 1});

	if (up[1] <= y_max)
	{
		it = m3dgrid.find(up);
		if ((*it).second == 'a')
		{
			(*it).second = 's';
			let_there_be_steam(m3dgrid, up);
		}
	}
	if (down[1] >= -1)
	{
		it = m3dgrid.find(down);
		if ((*it).second == 'a')
		{
			(*it).second = 's';
			let_there_be_steam(m3dgrid, down);
		}
	}
	if (left[0] >= -1)
	{
		it = m3dgrid.find(left);
		if ((*it).second == 'a')
		{
			(*it).second = 's';
			let_there_be_steam(m3dgrid, left);
		}
	}
	if (right[0] <= x_max)
	{
		it = m3dgrid.find(right);
		if ((*it).second == 'a')
		{
			(*it).second = 's';
			let_there_be_steam(m3dgrid, right);
		}
	}
	if (forward[2] <= z_max)
	{
		it = m3dgrid.find(forward);
		if ((*it).second == 'a')
		{
			(*it).second = 's';
			let_there_be_steam(m3dgrid, forward);
		}
	}
	if (back[2] >= -1)
	{
		it = m3dgrid.find(back);
		if ((*it).second == 'a')
		{
			(*it).second = 's';
			let_there_be_steam(m3dgrid, back);
		}
	}
}

void solve_p1(std::map<std::array<int, 3>, char> m3dgrid)
{
	std::map<std::array<int, 3>, char>::iterator it, it2;
	int n_connections = 0;

	for (it = m3dgrid.begin(); it != m3dgrid.end(); it++) {
		it2 = it;
		for (it2++; it2 != m3dgrid.end(); it2++) {
			if ( abs((*it).first[0] - (*it2).first[0]) + abs((*it).first[1] - (*it2).first[1]) + abs((*it).first[2] - (*it2).first[2]) == 1)
				n_connections += 1;
		}
	}
	std::cout << "p1:" << m3dgrid.size() * 6 - n_connections * 2 << std::endl;
}

void solve_p2(std::map<std::array<int, 3>, char> m3dgrid)
{
	std::map<std::array<int, 3>, char>::iterator it;
	int total = 0;

	for (it = m3dgrid.begin(); it != m3dgrid.end(); it++) {
		if ((*it).second == 'l')
			total += amount_sides_touch_steam(m3dgrid, (*it).first);
	}
	std::cout << "p2:" << total << std::endl;
}

int main(void)
{
	std::ifstream					ifs("input");
	std::string						line;
	std::map<std::array<int, 3>, char>	m3dgrid;

	for (std::getline(ifs, line); !ifs.eof(); std::getline(ifs, line)) {
		parse(line, m3dgrid);
	}
	solve_p1(m3dgrid);
	fill_grid_with_air(m3dgrid);
	m3dgrid.begin()->second = 's';
	let_there_be_steam(m3dgrid, m3dgrid.begin()->first);
	solve_p2(m3dgrid);
	return 0;
}
