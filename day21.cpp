#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <vector>
#include <iterator>
#include <algorithm>

struct operation {

	std::string	name;
	std::string left;
	std::string right;
	char		operation;

};

void parse( std::string line, std::map<std::string, long> & monkeys, std::vector<operation> & operations )
{
	size_t 		start = 0, end;
	operation 	operation;
	end = line.find(":");
	if (isdigit(line[end + 2]))
		monkeys.insert(std::make_pair(line.substr(start, end - start), std::stoi(line.substr(end + 2))));
	else
	{
		operation.name = line.substr(start, end - start);
		start = end + 2;
		end = line.find(" ", start);
		operation.left = line.substr(start, end - start);
		operation.right = line.substr(end + 3);
		operation.operation = line[11];
		operations.push_back(operation);
	}
}

void solve(std::map<std::string, long> & monkeys, std::vector<operation> & operations )
{
	std::vector<operation>::iterator		it;
	std::map<std::string, long>::iterator	left, right;
	std::string	name;
	long	n;

	for ( it = operations.begin(); it != operations.end(); ) {
		left = monkeys.find((*it).left);
		right = monkeys.find((*it).right);
		if (left != monkeys.end() && right != monkeys.end())
		{
			if ((*it).operation == '+')
				n = (*left).second + (*right).second;
			else if ((*it).operation == '-')
				n = (*left).second - (*right).second;
			else if ((*it).operation == '/')
				n = (*left).second / (*right).second;
			else if ((*it).operation == '*')
				n = (*left).second * (*right).second;
			monkeys.insert(std::make_pair((*it).name, n));
			it = operations.erase(it);
		}
		else
			it++;
	}
}

int main(void)
{
	std::map<std::string, long>				monkeys;
	std::map<std::string, long>::iterator 	it;
	std::vector<operation> 					operations;
	std::ifstream							ifs("input");
	std::string								line, root = "root";

	for (std::getline(ifs, line); !ifs.eof(); std::getline(ifs, line)) {
		parse(line, monkeys, operations);
	}
	while (1)
	{
		it = monkeys.find("root");
		if (it == monkeys.end())
			solve(monkeys, operations);
		else
			break ;
	}
	std::cout << "p1:" << (*it).second << std::endl;
}
