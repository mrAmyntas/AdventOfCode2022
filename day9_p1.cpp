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

void	go_left(Coord & H, Coord & T, std::unordered_set<Coord, pointHash> & set)
{
	if (H == T || (H.y == T.y && H.x > T.x))
		H.x--;
	else if (H.y == T.y)
	{
		H.x--;
		T.x--;
	}
	else if (H.x == T.x)
		H.x--;
	else if (H.x < T.x)
	{
		if (H.y > T.y)
			T.y++;
		else
			T.y--;
		T.x--;
		H.x--;
	}
	else
		H.x--;
	set.insert(T);
}

void	go_right(Coord & H, Coord & T, std::unordered_set<Coord, pointHash> & set)
{
	if (H == T || (H.y == T.y && H.x < T.x)) //on same coords, or on same row and H left of T
		H.x++;
	else if (H.y == T.y) //same row, H right of T
	{
		H.x++;
		T.x++;
	}
	else if (H.x == T.x) //same column
		H.x++;
	else if (H.x > T.x) //H right of T..
	{
		if (H.y > T.y) //and above T -> 
			T.y++;
		else // and below T ->
			T.y--;
		T.x++;
		H.x++;
	}
	else
		H.x++;
	// std::cout << T << std::endl;
	set.insert(T);
}

void	go_up(Coord & H, Coord & T, std::unordered_set<Coord, pointHash> & set)
{
	if (H == T || (H.x == T.x && H.y < T.y)) //on same coords, or on same col and H below T
	{
		H.y++;
	}
	else if (H.x == T.x) //same row, H above of T
	{
		H.y++;
		T.y++;
	}
	else if (H.y == T.y) //same row
		H.y++;
	else if (H.y > T.y) //H above of T..
	{
		if (H.x > T.x) //and to right T -> 
			T.x++;
		else // and to left T ->
			T.x--;
		T.y++;
		H.y++;
	}
	else
		H.y++;
	set.insert(T);
}

void	go_down(Coord & H, Coord & T, std::unordered_set<Coord, pointHash> & set)
{
	if (H == T || (H.x == T.x && H.y > T.y)) //on same coords, or on same col and H below T
		H.y--;
	else if (H.x == T.x) //same row, H above of T
	{
		H.y--;
		T.y--;
	}
	else if (H.y == T.y) //same row
		H.y--;
	else if (H.y < T.y) //H below of T..
	{
		if (H.x > T.x) //and to right T -> 
			T.x++;
		else // and to left T ->
			T.x--;
		T.y--;
		H.y--;
	}
	else
		H.y--;
	// std::cout << T << std::endl;
	set.insert(T);
}


int main(void)
{
	std::ifstream							ifs("../input");
	std::string								line;
	std::unordered_set< Coord, pointHash >	set;
	Coord									H(0,0);
	Coord									T(0,0);
	Coord									Knots[10];

	set.insert(T);
	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line)) {
		if (line[0] == 'R')
		{
			for (int i = std::stoi(line.substr(1)); i > 0; --i) {
				go_right(H, T, set);
			}
		}
		else if (line[0] == 'L')
		{
			for (int i = std::stoi(line.substr(1)); i > 0; --i) {
				go_left(H, T, set);
			}
		}
		else if (line[0] == 'U')
		{
			for (int i = std::stoi(line.substr(1)); i > 0; --i) {
				go_up(H, T, set);
			}
		}
		else if (line[0] == 'D')
		{
			for (int i = std::stoi(line.substr(1)); i > 0; --i) {
				go_down(H, T, set);
			}
		}
	}
	// print_set(set);
	std::cout << set.size() << std::endl;
	return 0;
}
