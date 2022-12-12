#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
#include <limits> 

class Monkey {

	public:
		Monkey(std::string c)
		{ 
			this->monkeyConfig = c;
			this->n_inspections = 0;
			setItems(c);
		};
		std::vector<int>	items;
		std::string			monkeyConfig;
		int					n_inspections;
		void				monkey_do(std::vector<Monkey*> &);
		void				setItems(std::string &);
};

void	Monkey::setItems(std::string & config)
{
	size_t pos, pos2;

	pos = config.find("Starting items:") + 16;
	while (1)
	{
		pos2 = config.find(",", pos);
		if (pos2 == std::string::npos)
		{
			pos2 = config.find("\n", pos); 
			this->items.push_back(std::stoi(config.substr(pos, pos2 - pos)));
			break ;
		}
		this->items.push_back(std::stoi(config.substr(pos, pos2 - pos)));
		pos = config.find(" ", pos) + 1;
	}
}

void	Monkey::monkey_do(std::vector<Monkey*> & Monkeys)
{
	size_t						pos, pos2;
	std::vector<int>::iterator	it;
	int							throw_to = 0;
	int							div;
	double						test_d;

	for (it = this->items.begin(); it != this->items.end(); it++) {
		pos = this->monkeyConfig.find("old") + 4;
		pos2 = this->monkeyConfig.find('\n', pos);
		//operation
		if (this->monkeyConfig[pos] == '+')
			*it = *it + std::stoi(this->monkeyConfig.substr(pos + 2, pos2 - pos - 2));
		else
		{
			if (isdigit(monkeyConfig[pos + 2]))
				*it = *it * (std::stoi(this->monkeyConfig.substr(pos + 2, pos2 - pos - 2)));
			else
				*it = (*it) * (*it);
		}
		this->n_inspections++;
		//test
		*it = *it / 3;
		pos = this->monkeyConfig.find("divisible by ") + 13;
		pos2 = this->monkeyConfig.find('\n', pos);
		div = std::stoi(this->monkeyConfig.substr(pos, pos2 - pos));
		test_d = *it;
		if (*it / div == test_d / div )
		{
			pos = this->monkeyConfig.find("true: throw to monkey ") + 22;
			pos2 = this->monkeyConfig.find('\n', pos);
			throw_to = std::stoi(this->monkeyConfig.substr(pos, pos2 - pos));
		}
		else
		{
			pos = this->monkeyConfig.find("false: throw to monkey ") + 23;
			pos2 = this->monkeyConfig.find('\n', pos);
			throw_to = std::stoi(this->monkeyConfig.substr(pos, pos2 - pos));
		}
		Monkeys[throw_to]->items.push_back(*it);
	}
	items.clear();
}

int main(void)
{
	std::ifstream			ifs("input");
	std::stringstream		buffer;
	std::string				MonkeyConfigs;
	size_t				 	pos, pos2;
	std::vector<Monkey*>	Monkeys;
	int						rounds;
	int						largest = 0, second_largest = 0, monkey_business;

	MonkeyConfigs = std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	for (pos = 0; pos != std::string::npos;) {
		pos = MonkeyConfigs.find("Monkey ", pos);
		pos2 = MonkeyConfigs.find("Monkey ", pos + 1);
		if (pos2 == std::string::npos)
			Monkeys.push_back(new Monkey(MonkeyConfigs.substr(pos)));
		else
			Monkeys.push_back(new Monkey(MonkeyConfigs.substr(pos, pos2 - pos)));
		pos = pos2;
	}
	for(rounds = 20; rounds > 0; rounds--) {
		for (auto number : Monkeys) {
			number->monkey_do(Monkeys);
		}
	}
	for (auto number : Monkeys) {
		if (number->n_inspections > largest)
		{
			second_largest = largest;
			largest = number->n_inspections;
		}
		else if (number->n_inspections < largest && number->n_inspections > second_largest)
			second_largest = number->n_inspections;
	}
	monkey_business = largest * second_largest;
	std::cout << monkey_business << std::endl;
	return 0;
}
