#include <iostream>
#include <fstream>
#include <map>

int main(void)
{
	std::ifstream	ifs;
	std::string		str;
	ifs.open("input"); /* added a '-' */
	int score = 0;
	std::map<std::string, int> mymap;
	mymap.insert({std::string ("A X"), 4});
	mymap.insert({std::string ("A Y"), 8});
	mymap.insert({std::string ("A Z"), 3});
	mymap.insert({std::string ("B X"), 1});
	mymap.insert({std::string ("B Y"), 5});
	mymap.insert({std::string ("B Z"), 9});
	mymap.insert({std::string ("C X"), 7});
	mymap.insert({std::string ("C Y"), 2});
	mymap.insert({std::string ("C Z"), 6});
	std::getline(ifs, str);
	for (; str[0] != '-'; std::getline(ifs, str)) {
		std::map<std::string,int>::iterator it = mymap.find(str);
		score = score + it->second;
	}
	std::cout << "p1:" << score << std::endl;
	/* part 2 */
	score = 0;
	ifs.seekg(0);
	std::map<std::string, int> mymap2;
	mymap2.insert({std::string ("A X"), 3});
	mymap2.insert({std::string ("A Y"), 4});
	mymap2.insert({std::string ("A Z"), 8});
	mymap2.insert({std::string ("B X"), 1});
	mymap2.insert({std::string ("B Y"), 5});
	mymap2.insert({std::string ("B Z"), 9});
	mymap2.insert({std::string ("C X"), 2});
	mymap2.insert({std::string ("C Y"), 6});
	mymap2.insert({std::string ("C Z"), 7});
	std::getline(ifs, str);
	for (; str[0] != '-'; std::getline(ifs, str)) {
		std::map<std::string,int>::iterator it = mymap2.find(str);
		score = score + it->second;
	}
	std::cout << "p2:" << score << std::endl;
	return 0;
}