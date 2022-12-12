#include <iostream>
#include <fstream>
#include <map>

int main(void)
{
	std::ifstream			ifs;
	std::string				line, comp_1, comp_2;
	std::string::iterator 	it, it2;
	int 					value, sum = 0;

	/* part 1 */
	ifs.open("input"); /* added extra newline */
	int score = 0;
	std::getline(ifs, line);
	for (; !ifs.eof() ; std::getline(ifs, line)) {
		comp_1 = line.substr(0, (line.size() / 2));
		comp_2 = line.substr(line.size() / 2, line.size() / 2);
		for( it = comp_1.begin(); it != comp_1.end(); it++) {
			for ( it2 = comp_2.begin(); it2 != comp_2.end(); it2++) {
				if (*it == *it2)
					break ;
			}
			if (*it == *it2)
				break ;
		}
		if (*it >= 'a')
			value = *it - 'a' + 1;
		else
			value = *it - 'A' + 27;
		sum = sum + value;
	}
	std::cout << sum << std::endl;
	/* part 2 */
	std::string groupmember_1, groupmember_2, groupmember_3;
	std::string::iterator 	it3;
	ifs.clear();
	ifs.seekg(0);
	sum = 0;
	std::getline(ifs, line);
	for (int i = 1; !ifs.eof() ; i++, std::getline(ifs, line)) {
		if (i % 3 == 0)
		{
			groupmember_3 = line;
			for( it = groupmember_1.begin(); it != groupmember_1.end(); it++) {
				for ( it2 = groupmember_2.begin(); it2 != groupmember_2.end(); it2++) {
					if (*it == *it2)
					{
						for ( it3 = groupmember_3.begin(); it3 != groupmember_3.end(); it3++) {
							if (*it3 == *it)
								break ;
						}
					}
					if (*it2 == *it && *it3 == *it)
						break ;
				}
				if (*it2 == *it && *it3 == *it)
					break ;
			}
			if (*it >= 'a')
				value = *it - 'a' + 1;
			else
				value = *it - 'A' + 27;
			sum = sum + value;

		}
		else if (i % 2 == 0)
			groupmember_2 = line;
		else
			groupmember_1 = line;
	}
	std::cout << sum << std::endl;
	return 0;
}