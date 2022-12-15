#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <math.h>
#include <limits.h>

#define row 2000000

struct point {
	point(int x, int y) : x(x), y(y) {} ;
	int x;
	int y;
};

struct sensor {
	sensor(point S, point B) : S(S), B(B) {
		dist = abs(S.x - B.x) + abs(S.y - B.y);
	}
	point 	S;
	point 	B;
	int		dist;
};

struct interval {
	interval(int min, int max) : min(min), max(max) {}
	int min;
	int max;
	bool operator==(interval & r)
	{
		if (this->max == r.max && this->min == r.min)
			return true;
		return false;
	}
};

int	solve( sensor S, std::vector<interval> & intervals )
{

	int dist_to_row, x_len, to_add = 0;

	if ( row < S.S.y - S.dist || row > S.S.y + S.dist)
		return 0;

	dist_to_row = abs(S.S.y - row);
	x_len = S.dist - dist_to_row;
	interval new_interval(S.S.x - x_len, S.S.x + x_len);
	to_add = new_interval.max - new_interval.min + 1;
	for (std::vector<interval>::iterator it = intervals.begin(); it != intervals.end(); it++) {
		if ( (*it).min > new_interval.max || (*it).max < new_interval.min) 	//no overlap
			continue ;
		if ( (*it).min <= new_interval.min && (*it).max >= new_interval.max )	//old interval completely covers new
			return 0;
		if ( (*it).min >= new_interval.min && (*it).max <= new_interval.max) 	//new interval completely covers old
		{
			to_add = to_add - ((*it).max - (*it).min + 1);
			intervals.erase(it);
			it--;
		}
		else if ( (*it).min >= new_interval.min ) 							//new interval covers left side of old
		{
			to_add = to_add - (new_interval.max - (*it).min + 1);
			new_interval.max = (*it).min;
		}
		else 															//right side
		{
			to_add = to_add - ((*it).max - new_interval.min + 1);
			new_interval.min = (*it).max;
		}
	}
	intervals.push_back(new_interval);
	return to_add;
}

sensor parse(std::string & line)
{
	size_t	start, end;
	int		x_s, y_s, x_b, y_b;
	
	start = line.find('=') + 1;
	end = line.find(',');
	x_s = std::stoi(line.substr(start, end - start));
	start = line.find('y') + 2;
	end = line.find(':');
	y_s = std::stoi(line.substr(start, end - start));
	start = line.find('x', start) + 2;
	end = line.find(',', start);
	x_b = std::stoi(line.substr(start, end - start));
	start = line.find('y', end) + 2;
	y_b = std::stoi(line.substr(start));
	return	sensor(point(x_s, y_s), point(x_b, y_b));
}

int main(void)
{
	std::ifstream								ifs("input");
	std::string									line;
	int											total = 0;
	std::vector<interval>							intervals;

	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line)) {
		sensor s = parse(line);
		total += solve(s, intervals);
	}
	std::cout << total << std::endl;
	return 0;
}
