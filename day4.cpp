#include <iostream>
#include <fstream>
#include <map>

int main(void)
{
	std::ifstream	ifs("../input"); /* added newline */
	std::string		line;
	int				overlap = 0, contain = 0, val[4];
	size_t			pos = 0, plus[1];
	
	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line), pos = 0) {
		for (size_t i = 0; i < 4; ++i, pos += *plus + 1) {
			val[i] = std::stoi( line.substr(pos, (line.find_first_of("-,", pos) - pos)), plus, 10 );
		}
		if ((val[0] <= val[2] && val[1] >= val[3]) | (val[0] >= val[2] && val[1] <= val[3]))
			contain++;
		if ( val[1] >= val[2] && val[0] <= val[3] )
			overlap++;

	}
    std::cout << "p1:" << contain << " p2:" << overlap << std::endl;
	return 0;
}
