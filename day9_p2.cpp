#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <vector>
#include <unordered_set>
#include <set>

class Coord {
	public:
		Coord(int x, int y) { this->x = x; this->y = y; };
		Coord() { this->x = 0; this->y = 0; };
		int x;
		int y;
		bool operator== (const Coord &rhs) const
		{
			if (this->x == rhs.x && this->y == rhs.y)
				return true;
			return false;
		}
		bool operator< (const Coord &rhs) const
		{
			if (this->x == rhs.x && this->y == rhs.y)
				return false;
			return true ;
		}
		friend std::ostream &operator<<( std::ostream &os, const Coord &src )
		{
			os << "(" << src.x << "," << src.y << ")";
			return os;
		}
		Coord(const Coord &rhs) {
			*this = rhs;
		}
		Coord & operator=(const Coord &rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			return *this;
		}
};

struct pointHash {
public:
	size_t operator()(const Coord p) const 
    {
		return std::hash<uint32_t>()(p.x) ^ std::hash<uint32_t>()(p.y);
	}
};

void	go_left_down(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set);
void	go_left_up(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set);
void	go_right_up(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set);
void	go_right_down(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set);

void print_set(std::unordered_set<Coord, pointHash> & set)
{

	std::unordered_set<Coord, pointHash>::iterator it = set.begin();
	while (it != set.end())
	{
		set.insert(*it);
		std::cout << *it << std::endl;
		it++;
	}
}

void	go_left(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set)
{
	if (n == 10)
		return ;
	if (Knots[n] == Knots[n + 1] || (Knots[n].y == Knots[n + 1].y && Knots[n].x > Knots[n + 1].x))
		Knots[n].x--;
	else if (Knots[n].y == Knots[n + 1].y)
	{
		Knots[n].x--;
		go_left(n + 1, Knots, set);
	}
	else if (Knots[n].x == Knots[n + 1].x)
		Knots[n].x--;
	else if (Knots[n].x < Knots[n + 1].x)
	{
		if (Knots[n].y > Knots[n + 1].y)
			go_left_up(n + 1, Knots, set);
		else
			go_left_down(n + 1, Knots, set);
		Knots[n].x--;
	}
	else
		Knots[n].x--;
	if (n == 9)
		set.insert(Knots[9]);
}

void	go_right(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set)
{
	if (n == 10)
		return ;
	if (Knots[n] == Knots[n+1] || (Knots[n].y == Knots[n+1].y && Knots[n].x < Knots[n+1].x)) 
		Knots[n].x++;
	else if (Knots[n].y == Knots[n+1].y) 
	{
		Knots[n].x++;
		go_right(n + 1, Knots, set);
	}
	else if (Knots[n].x == Knots[n+1].x) 
		Knots[n].x++;
	else if (Knots[n].x > Knots[n+1].x) 
	{
		if (Knots[n].y > Knots[n+1].y)
			go_right_up(n + 1, Knots, set);
		else
			go_right_down(n + 1, Knots, set);
		Knots[n].x++;
	}
	else
		Knots[n].x++;
	if (n == 9)
		set.insert(Knots[9]);

}

void	go_up(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set)
{
	if (n == 10)
		return ;
	if (Knots[n] == Knots[n+1] || (Knots[n].x == Knots[n+1].x && Knots[n].y < Knots[n+1].y)) 
		Knots[n].y++;
	else if (Knots[n].x == Knots[n+1].x) 
	{
		Knots[n].y++;
		go_up(n + 1, Knots, set);
	}
	else if (Knots[n].y == Knots[n+1].y) 
		Knots[n].y++;
	else if (Knots[n].y > Knots[n+1].y)
	{
		if (Knots[n].x > Knots[n+1].x)
			go_right_up(n + 1, Knots, set);
		else
			go_left_up(n + 1, Knots, set);
		Knots[n].y++;
	}
	else
		Knots[n].y++;
	if (n == 9)
		set.insert(Knots[9]);
}

void	go_down(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set)
{
	if (n == 10)
		return ;
	if (Knots[n] == Knots[n+1] || (Knots[n].x == Knots[n+1].x && Knots[n].y > Knots[n+1].y))
		Knots[n].y--;
	else if (Knots[n].x == Knots[n+1].x)
	{
		Knots[n].y--;
		go_down(n + 1, Knots, set);
	}
	else if (Knots[n].y == Knots[n+1].y) 
		Knots[n].y--;
	else if (Knots[n].y < Knots[n+1].y) 
	{
		if (Knots[n].x > Knots[n+1].x)
			go_right_down(n + 1, Knots, set);
		else 
			go_left_down(n + 1, Knots, set);
		Knots[n].y--;
	}
	else
		Knots[n].y--;
	if (n == 9)
		set.insert(Knots[9]);
}

void	go_left_down(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set)
{
	if (n == 10)
		return ;
	int store = Knots[n].x;
	if (Knots[n] == Knots[n+1] || (Knots[n].x - 1 == Knots[n+1].x && Knots[n].y == Knots[n+1].y) ||  (Knots[n].y - 1 == Knots[n+1].y && Knots[n].x == Knots[n+1].x) || (Knots[n].y - 1 == Knots[n+1].y && Knots[n].x - 1 == Knots[n+1].x) )
	{
		Knots[n].x--;
		Knots[n].y--;
	}
	else if (Knots[n].x + 1 == Knots[n+1].x && Knots[n].y - 1 == Knots[n+1].y)
	{
		Knots[n].x--;
		Knots[n].y--;
		go_left(n + 1, Knots, set);
	}
	else if (Knots[n].x - 1 == Knots[n+1].x && Knots[n].y + 1 == Knots[n+1].y)
	{
		Knots[n].x--;
		Knots[n].y--;
		go_down(n + 1, Knots, set);
	}
	else
	{
		Knots[n].x--;
		Knots[n].y--;
		go_left_down(n + 1, Knots, set);
	}
	if (store == Knots[n].x)
		std::cout <<  "OEPS\n";
	if (n == 9)
		set.insert(Knots[9]);

}

void	go_left_up(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set)
{
	if (n == 10)
		return ;
	int store = Knots[n].x;
	if (Knots[n] == Knots[n+1] || (Knots[n].x - 1 == Knots[n+1].x && Knots[n].y == Knots[n+1].y) ||  (Knots[n].y + 1 == Knots[n+1].y && Knots[n].x - 1 == Knots[n+1].x) || (Knots[n].y + 1 == Knots[n+1].y && Knots[n].x == Knots[n+1].x) )
	{
		Knots[n].x--;
		Knots[n].y++;
	}
	else if (Knots[n].x + 1 == Knots[n+1].x && Knots[n].y + 1 == Knots[n+1].y)
	{
		Knots[n].x--;
		Knots[n].y++;
		go_left(n + 1, Knots, set);
	}
	else if (Knots[n].x - 1 == Knots[n+1].x && Knots[n].y - 1 == Knots[n+1].y)
	{
		Knots[n].x--;
		Knots[n].y++;
		go_up(n + 1, Knots, set);
	}
	else
	{
		Knots[n].x--;
		Knots[n].y++;
		go_left_up(n + 1, Knots, set);
	}
	if (store == Knots[n].x)
		std::cout <<  "OEPS\n";

	if (n == 9)
		set.insert(Knots[9]);

}

void	go_right_down(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set)
{
	if (n == 10)
		return ;
	int store = Knots[n].x;

	if (Knots[n] == Knots[n+1] || (Knots[n].x == Knots[n+1].x && Knots[n].y - 1 == Knots[n+1].y) ||  (Knots[n].y == Knots[n+1].y && Knots[n].x + 1 == Knots[n+1].x) || (Knots[n].y - 1 == Knots[n+1].y && Knots[n].x + 1 == Knots[n+1].x) )
	{
		Knots[n].x++;
		Knots[n].y--;
	}
	else if (Knots[n].x - 1 == Knots[n+1].x && Knots[n].y - 1 == Knots[n+1].y)
	{
		Knots[n].x++;
		Knots[n].y--;
		go_right(n + 1, Knots, set);
	}
	else if (Knots[n].x + 1 == Knots[n+1].x && Knots[n].y + 1 == Knots[n+1].y)
	{
		Knots[n].x++;
		Knots[n].y--;
		go_down(n + 1, Knots, set);
	}
	else
	{
		Knots[n].x++;
		Knots[n].y--;
		go_right_down(n + 1, Knots, set);
	}
	if (store == Knots[n].x)
		std::cout <<  "OEPS\n";
	if (n == 9)
		set.insert(Knots[9]);
}

void	go_right_up(int n, Coord Knots[10], std::unordered_set<Coord, pointHash> & set)
{
	if (n == 10)
		return ;
	int store = Knots[n].x;
	if (Knots[n] == Knots[n+1] || (Knots[n].x == Knots[n+1].x && Knots[n].y + 1 == Knots[n+1].y) ||  (Knots[n].y == Knots[n+1].y && Knots[n].x + 1 == Knots[n+1].x) || (Knots[n].y + 1 == Knots[n+1].y && Knots[n].x + 1 == Knots[n+1].x) )
	{
		Knots[n].x++;
		Knots[n].y++;
	}
	else if (Knots[n].x - 1 == Knots[n+1].x && Knots[n].y + 1 == Knots[n+1].y)
	{
		Knots[n].x++;
		Knots[n].y++;
		go_right(n + 1, Knots, set);
	}
	else if (Knots[n].x + 1 == Knots[n+1].x && Knots[n].y - 1 == Knots[n+1].y)
	{
		Knots[n].x++;
		Knots[n].y++;
		go_up(n + 1, Knots, set);
	}
	else
	{
		Knots[n].x++;
		Knots[n].y++;
		go_right_up(n + 1, Knots, set);
	}
	if (store == Knots[n].x)
		std::cout <<  "OEPS\n";
	if (n == 9)
		set.insert(Knots[9]);
}

int main(void)
{
	std::ifstream							ifs("../input");
	std::string								line;
	std::unordered_set< Coord, pointHash >	set;
	Coord									Knots[10];

	set.insert(Knots[9]);
	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line)) {
		if (line[0] == 'R')
		{
			for (int i = std::stoi(line.substr(1)); i > 0; --i) {
				go_right(0, Knots, set);
			}
		}
		else if (line[0] == 'L')
		{
			for (int i = std::stoi(line.substr(1)); i > 0; --i) {
				go_left(0, Knots, set);
			}
		}
		else if (line[0] == 'U')
		{
			for (int i = std::stoi(line.substr(1)); i > 0; --i) {
				go_up(0, Knots, set);
			}
		}
		else if (line[0] == 'D')
		{
			for (int i = std::stoi(line.substr(1)); i > 0; --i) {
				go_down(0, Knots, set);
			}
		}
	}
	// print_set(set);
	std::cout << set.size() << std::endl;
	return 0;
}
