#include <iostream>
#include <fstream>
#include <vector>
#include "ft_itoa.c"

struct monkey {

	std::string	operation = "";
	std::string	name;
	int 		yells;
};

void parse( std::string line, std::vector<monkey> & monkeys)
{
	size_t	start = 0, end;
	monkey	new_monkey;

	end = line.find(":");
	new_monkey.name = line.substr(start, end - start);
	if (isdigit(line[end + 2]))
	{
		new_monkey.yells = std::stoi(line.substr(end + 2));
		monkeys.push_back(new_monkey);
	}
	else
	{
		start = end + 2;
		new_monkey.operation = line.substr(start);
		if (new_monkey.name == "root")
			new_monkey.operation[5] = '=';
		monkeys.push_back(new_monkey);
	}
}

int	build_final_operation(std::vector<monkey> & monkeys)
{
	std::vector<monkey>::iterator it, it2;
	size_t	start = 0, end, check = 0;
	std::string new_operation;

	for (it = monkeys.begin(); it != monkeys.end(); it++)
	{
		if (!(*it).operation.empty())
		{
			for (it2 = monkeys.begin(); it2 != monkeys.end(); it2++)
			{
				start = (*it).operation.find((*it2).name);
				if (start != std::string::npos && (*it2).operation.empty() == false)
				{
					check = 1;
					end = start + 4;
					new_operation = "(" + (*it2).operation + ")";
					(*it).operation.replace(start, end - start, new_operation);
				}
				else if (start != std::string::npos && (*it2).name != "humn")
				{
					check = 1;
					end = start + 4;
					char *c = ft_itoa((*it2).yells);
					new_operation = c;
					(*it).operation.replace(start, end - start, new_operation);
				}
			}
		}
	}
	if (check == 0)
		return 0;
	return 1;
}

int main(void)
{
	std::ifstream					ifs("input");
	std::string						line;
	std::vector<monkey>				monkeys;
	std::vector<monkey>::iterator	it;

	for (std::getline(ifs, line); !ifs.eof(); std::getline(ifs, line)) {
		parse(line, monkeys);
	}
	while (build_final_operation(monkeys));

	for (it = monkeys.begin(); it != monkeys.end(); it++) {
		if ((*it).name == "root")
			break ;
	}
	size_t pos = (*it).operation.find("humn");
	(*it).operation.replace(pos, 4, "x");
	std::cout << (*it).operation << std::endl;
	//paste output in https://www.mathpapa.com/algebra-calculator.html  :)
	//it found 24697909688081686528 /  6417873 which rounds to 3848301405790 which was correct answer
}
