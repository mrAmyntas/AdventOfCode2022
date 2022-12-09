#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

int x_min = 0;
int y_min = 0;
int x_max = 0;
int y_max = 0;

void print_map(std::vector<std::pair<std::pair<int, int>, int> > & map)
{
	int row_size = x_max, i = 1;

	for (std::vector<std::pair<std::pair<int, int>, int> >::iterator it = map.begin(); it != map.end(); it++, i++) {
		std::cout << (*it).second;
		if (i % row_size == 0)
			std::cout << std::endl; 
	}
}

int	check_left(std::vector<std::pair<std::pair<int, int>, int> >::iterator cur_tree, std::vector<std::pair<std::pair<int, int>, int> >	map)
{
	int distance = 1;
	std::vector<std::pair<std::pair<int, int>, int> >::iterator next_tree = (cur_tree - 1);
	for (; (*next_tree).first.first > x_min; next_tree--){
		if ((*next_tree).second < (*cur_tree).second)
			distance++;
		else
			break ;
	}
	return distance;
}

int	check_right(std::vector<std::pair<std::pair<int, int>, int> >::iterator cur_tree, std::vector<std::pair<std::pair<int, int>, int> >	map)
{
	int distance = 1;

	std::vector<std::pair<std::pair<int, int>, int> >::iterator next_tree = (cur_tree + 1);
	for (; (*next_tree).first.first < x_max; next_tree++){
		if ((*next_tree).second < (*cur_tree).second)
			distance++;
		else
			break ;
	}
	return distance;
}

int	check_up(std::vector<std::pair<std::pair<int, int>, int> >::iterator cur_tree, std::vector<std::pair<std::pair<int, int>, int> >	map)
{
	int distance = 1;

	std::vector<std::pair<std::pair<int, int>, int> >::iterator next_tree = (cur_tree - (y_max + 1));
	for (; (*next_tree).first.second > y_min; next_tree = (next_tree - (y_max + 1))){
		if ((*next_tree).second < (*cur_tree).second)
			distance++;
		else
			break ;
	}
	return distance;
}

int	check_down(std::vector<std::pair<std::pair<int, int>, int> >::iterator cur_tree, std::vector<std::pair<std::pair<int, int>, int> >	map)
{
	int distance = 1;

	std::vector<std::pair<std::pair<int, int>, int> >::iterator next_tree = (cur_tree + (y_max + 1));
	for (; (*next_tree).first.second < y_max; next_tree = (next_tree + y_max + 1)){
		if ((*next_tree).second < (*cur_tree).second)
			distance++;
		else
			break ;
	}
	return distance;
}

int main(void)
{
	std::ifstream	ifs("input");
	std::string		line;
	int				i = 0, row_num = 0, col_num = 0;
	std::vector<std::pair<std::pair<int, int>, int> >	map;
	int				scene_score;
	int				max_score = 0;
	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line), row_num++, col_num = 0) {
		for (std::string::iterator it = line.begin(); it != line.end(); it++, col_num++) {
			int c = *it - 48;
			map.push_back(std::make_pair(std::make_pair(col_num, row_num), c));
			i++;
		}
		if (x_max == 0)
			x_max = i;
		y_max++;
	}
	print_map(map);
	y_max--;
	x_max--;
	std::vector<std::pair<std::pair<int, int>, int> >::iterator cur_tree = map.begin();
	std::vector<std::pair<std::pair<int, int>, int> >::iterator next_tree;
	for (cur_tree = map.begin(); cur_tree != map.end(); cur_tree++) {
		if ((*cur_tree).first.first == x_min || (*cur_tree).first.first == x_max || (*cur_tree).first.second == y_min || (*cur_tree).first.second == y_max)
			continue;
		scene_score = check_left(cur_tree, map) * check_right(cur_tree, map) * check_up(cur_tree, map) * check_down(cur_tree, map);
		if (scene_score > max_score)
			max_score = scene_score;	
	}
	std::cout << "score:" << max_score << std::endl;
}
