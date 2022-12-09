#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

int main (void)
{
	int value = 0;
	std::ifstream ifs;
	char buff[1000];
	std::string str = " ";
	std::vector<int> calories;

	ifs.open("src.txt");
	memset(buff, '\0', 1000);
	while (!ifs.eof())
	{
		while (str.compare(""))
		{
			ifs.getline(buff, 1000, '\n');
			str = buff;
			if (!str.compare(""))
				break;
			value = value + std::stoi(str);
		}
		calories.push_back(value);
		value = 0;
		str = " ";
	}
	std::cout << "1st: " << calories[0] << std::endl;
	int max = *max_element(calories.begin(),calories.end());
	std::vector<int>::iterator begin = calories.begin();
	std::vector<int>::iterator end = calories.end();
	int top_3 = 0;
	for (int times = 0; times < 3; times++)
	{
		while (begin!=end)
		{
			if (*begin == max)
			{
				top_3 = top_3 + max;
				calories.erase(begin);
				begin = calories.begin();
				max = *max_element(calories.begin(),calories.end());
				std::cout << "top:" << top_3 << " max:" << max << std::endl;
				break;
			}
			begin++;
		}
	}
	std::cout << "top3:" << top_3<< std::endl;
	return 0;
}