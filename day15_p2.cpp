#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <math.h>
#include <limits.h>

#define maxim 4000000

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

void	solve( int i, std::vector<sensor> & sensors, std::vector<interval> & intervals )
{
	std::vector<sensor>::iterator 	s_it;
	std::vector<interval>::iterator it;
	int 							n = 0, dist_to_row, x_len;

	for (s_it = sensors.begin(); s_it != sensors.end(); s_it++) {
		if ( i < (*s_it).S.y - (*s_it).dist || i > (*s_it).S.y + (*s_it).dist)
			continue ;
		dist_to_row = abs((*s_it).S.y - i);
		x_len = (*s_it).dist - dist_to_row;
		int min = (*s_it).S.x - x_len;
		int max = (*s_it).S.x + x_len;
		if (min < 0)
			min = 0;
		if (min > maxim)
			continue ;
		if (max > maxim)
			max = maxim;
		if (max < 0)
			continue ;
		interval new_interval(min, max);
		n = 0;
		for ( it = intervals.begin(); it != intervals.end(); it++) {
			if ( (*it).min -1 > new_interval.max || (*it).max + 1 < new_interval.min) //no overlap or next to eachother
				continue ;
			if ( (*it).min <= new_interval.min && (*it).max >= new_interval.max )	//old interval completely covers new
			{
				n = 1;
				break ;
			}
			if ( (*it).min >= new_interval.min && (*it).max <= new_interval.max) 	//new interval completely covers old
			{
				intervals.erase(it);
				it--;
			}
			else if ( (*it).min >= new_interval.min || (*it).min - 1 == new_interval.max) 	//new interval covers left side of old or is right next to it
			{
				new_interval.max = (*it).max;
				intervals.erase(it);
				it--;
			}
			else if ((*it).max <= new_interval.max || (*it).max + 1 == new_interval.min) //right side
			{		
				new_interval.min = (*it).min;
				intervals.erase(it);
				it--;
			}
		}
		if (n == 0)
			intervals.push_back(new_interval);
	}
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
	int											i = 0;
	std::vector<std::vector<interval> >			interval_v;
	std::vector<sensor>							sensors;
	unsigned long long int						result;

	//get sensors
	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line)) {
			sensors.push_back(parse(line));
	}

	//go through all lines until a gap is found
	interval_v.resize(maxim);
	std::vector<std::vector<interval> >::iterator it = interval_v.begin();
	while (it != interval_v.end())
	{
		solve(i, sensors, *it);
		if ((*it).size() > 1)
			break ;
		it++;
		i++;
	}
	if ((*it).front().min < (*it).back().min)
	{
		result = (*it).front().max + 1;
		result = result * 4000000 + i;
	}
	else
	{
		result = (*it).back().max + 1;
		result = result * 4000000 + i;
	}
	std::cout << result << std::endl;
	return 0;
}
