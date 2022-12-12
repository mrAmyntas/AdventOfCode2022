#include <iostream>
#include <fstream>

int main(void)
{
	std::ifstream	ifs("../input");
	std::string		line;
	int				cycle = 1, X = 1, sig_str = 0;

	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line), cycle++) {
		if (cycle == 20 || (cycle - 20) % 40 == 0)
			sig_str = sig_str + cycle * X;
		if (line[0] == 'a')
		{
			cycle++;
			if (cycle == 20 || (cycle - 20) % 40 == 0)
				sig_str = sig_str + cycle * X;
			X = X + std::stoi(line.substr(5));
		}
	}
	std::cout << sig_str << std::endl;
	return 0;
}
