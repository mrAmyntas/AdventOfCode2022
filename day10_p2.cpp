#include <iostream>
#include <fstream>

int main(void)
{
	std::ifstream	ifs("../input");
	std::string		line;
	int				pixel = 0, cycle = 1, X = 1;

	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line), cycle++, pixel++) {
		if ((cycle - 1) % 40 == 0 && cycle != 1)
		{
			std::cout << std::endl;
			pixel = 0;
		}
		if (pixel == X || pixel == X + 1 || pixel == X - 1)
			std::cout << "#";
		else
			std::cout << ".";
		if (line[0] == 'a')
		{
			pixel++;
			cycle++;
			if ((cycle - 1) % 40 == 0)
			{
				std::cout << std::endl;
				pixel = 0;
			}
			if (pixel == X || pixel == X + 1 || pixel == X - 1)
				std::cout << "#";
			else
				std::cout << ".";
			X = X + std::stoi(line.substr(5));
		}
	}
	return 0;
}

