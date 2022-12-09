#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>

#define MARKER_LENGTH 14

int main(void)
{
	std::ifstream ifs("../input");
	std::string line, msg;
	size_t	i = 1, pos = 0;
	bool notamessage = false;
	
	std::getline(ifs, line);
	for (std::string::iterator it = line.begin(); it + MARKER_LENGTH - 1 != line.end(); it++, pos = 0) {
		msg = line.substr(std::distance(line.begin(), it), MARKER_LENGTH);
		for (std::string::iterator it2 = msg.begin(); it2 != msg.end(); it2++, pos++) {
			for (std::string::iterator it3 = msg.begin() + pos; it3 != msg.end(); it3++) {
				if (it3 != it2 && *it3 == *it2)
					notamessage = true;
			}
			if (notamessage == true)
				break ;
			if (pos == MARKER_LENGTH - 1)
			{
				std::cout << "found: " << std::distance(line.begin(), it) + MARKER_LENGTH << std::endl;
				return 0;
			}
		}
		notamessage = false;
	}
	return 0;
}
