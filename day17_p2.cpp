#include <iostream>
#include <fstream>

//ran p1 it for a bit, stored height diff after every rock in output
//in ouput i did (ctrl-F) search and started putting in sequence until i found the 
//full one that was repeating. some leading start rocks are not part of the sequence, those are 
// in 'start', the pattern is in 'pattern'

int main(void)
{
	std::ifstream			ifs("start");
	std::string				line;
	std::string::iterator 	it;

	std::getline(ifs, line);
	int start_height = 0;
	for (it = line.begin(); it != line.end(); it++) {
		start_height = start_height + (*it) - '0';
	}
	int start_len = line.size();

	ifs.close();
	ifs.open("pattern");
	std::getline(ifs, line);
	int pattern_height = 0;
	for (it = line.begin(); it != line.end(); it++) {
		pattern_height = pattern_height + (*it) - '0';
	}
	int pattern_len = line.size();
	long int pattern_repeats = 1000000000000 / pattern_len;
	long int rocks_left = 1000000000000 - pattern_repeats * pattern_len - start_len;
	
	it = line.begin();
	int last_rocks = 0;
	for (int i = 0; i < rocks_left; it++, i++) {
		last_rocks = last_rocks + (*it) - '0';
	}
	long int total = pattern_repeats * pattern_height + start_height + last_rocks;
	std::cout << "total:" << total << std::endl;
	return 0;
}
