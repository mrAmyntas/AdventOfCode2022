#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

int main(void)
{
	std::ifstream	ifs("../input");
	std::map<int, int> directories;
	std::map<int, int>::iterator it;
	std::vector<int> current_dirs;
	int index = 0;
	std::string line, ls = "$ ls", cd = "$ cd", cd_back = "$ cd ..", dir = "dir";
	int value, total = 0;

	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line)) {
		if (!line.compare(0, 4, "$ cd") && line.compare("$ cd ..")) // if it is cd "x"
		{
			directories.insert(std::map<int, int>::value_type(index, 0));
			current_dirs.push_back(index);
			index++;
		}
		else if (!line.compare("$ cd ..")) // if it is cd ..
		{
			it = directories.find(current_dirs.back());
			if (it != directories.end())
			{
				value = it->second;
				current_dirs.pop_back();
				it = directories.find(current_dirs.back());
				if (it != directories.end())
					it->second = it->second + value;
			}
		}
		else if (line.compare(0, 3, dir) && line.compare(ls)) //if it is a size
		{
			//add size to most current dir
			value = std::stoi( line.substr(0, line.find(" ")));
			it = directories.find(current_dirs.back());
			if (it != directories.end())
				it->second = it->second + value;
		}
	}
	for (;!current_dirs.empty();) {
		it = directories.find(current_dirs.back());
		value = it->second;
		current_dirs.pop_back();
		it = directories.find(current_dirs.back());
		if (it != directories.end())
			it->second = it->second + value;
	}

	for (it = directories.begin(); it != directories.end(); it++) {
		if (it->second <= 100000)
		{
			total = total + it->second;
		}
	}
	std::cout << total << std::endl;

	/* p2 */
	int		total_space = 70000000;
	int		required_space = 30000000;
	it = directories.begin();
	int		total_used = it->second / 2;
	int		available = total_space - total_used;
	int		amount_to_delete = required_space - available;
	std::cout << "aailable:" << available << std::endl;
	int 	biggest = total_used;

	std::cout << "total used:" << total_used << " total space required for update:" << required_space << " amount to delete:" << amount_to_delete << std::endl;
	for (it = directories.begin(); it != directories.end(); it++) {
		if (it->second < biggest && it->second >= amount_to_delete)
			biggest = it->second;
	}
	std::cout << biggest << std::endl;

}
// 70000000 total
// 50216456 used
// 19783544 available
// 30000000 required

// 6043291