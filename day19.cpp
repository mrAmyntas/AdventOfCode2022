#include <iostream>
#include <fstream>
#include <map>
#include <array>

enum {
	NONE,
	ORE,
	CLAY,
	OBS,
	GEO
} ;
class Blueprint {
	public:
		//costs to make robots in ore
		int	c_ore;
		int c_clay;
		int c_obsidian[2]; //+ clay cost
		int c_geode[2]; //+ obsidian cost

		int max_ore;
		int max_clay;
		int max_obs;
};

void parse(std::string line, std::array<Blueprint, 30> & bprints, int i)
{
	size_t		start = 6, end;
	Blueprint	bprint;

	bprint.c_ore = line[0] - '0';
	bprint.max_ore = bprint.c_ore;
	bprint.c_clay = line[2] - '0';
	if (bprint.c_clay > bprint.max_ore)
		bprint.max_ore = bprint.c_clay;
	bprint.c_obsidian[0] = line[4] - '0';
	if (bprint.c_obsidian[0] > bprint.max_ore)
		bprint.max_ore =bprint.c_obsidian[0];
	end = line.find(" ", start);
	bprint.c_obsidian[1] = std::stoi(line.substr(start, end - start));
	bprint.max_clay = bprint.c_obsidian[1];
	start = end + 1;
	end = line.find(" ", start);
	bprint.c_geode[0] = std::stoi(line.substr(start, end - start));
	if (bprint.c_geode[0] > bprint.max_ore)
		bprint.max_ore = bprint.c_geode[0];
	start = end + 1;
	bprint.c_geode[1] = std::stoi(line.substr(start));
	bprint.max_obs = bprint.c_geode[1];
	bprints[i] = bprint;
}

int	solve(Blueprint bprint, int start_ore, int start_clay, int start_obsidian, int start_geode, int time, int n_ore_robots, int n_clay_robots, int n_obs_robots, int n_geo_robots, int make_robot)
{
	//recursively check all posibilities with some pruning
	//if I can make a geode bot I do that and nothing else.
	//if I can make a obsidian bot I either make it or wait, not try a clay or ore robot,
	//because in the input it is clear that the obsidian requirement for making a geode bot
	//is much higher than the ore requirement, it seems unlikely for it to be better to make a clay/ore bot
	//when you can make an obsidian one.
	//I never make more robots of a kind that would overproduce resources.
	//if I can make ore/clay robots without overproducing, I don't wait.
	int new_ore = start_ore + n_ore_robots;
	int new_clay = start_clay + n_clay_robots;
	int new_obsidian = start_obsidian + n_obs_robots;
	int new_geode = start_geode + n_geo_robots;
	int max_geode = new_geode;
	int new_time = time - 1;
	if (new_time == 0)
		return max_geode;
	if (make_robot == ORE)
		n_ore_robots++;
	if (make_robot == CLAY)
		n_clay_robots++;
	if (make_robot == OBS)
		n_obs_robots++;
	if (make_robot == GEO)
		n_geo_robots++;
	int check = 0;
	int ret;
	
	if (new_ore >= bprint.c_geode[0] && new_obsidian >= bprint.c_geode[1])
	{
		int next_ore = new_ore - bprint.c_geode[0];
		int next_obsidian = new_obsidian - bprint.c_geode[1];
		ret = solve(bprint, next_ore, new_clay, next_obsidian, new_geode, new_time, n_ore_robots, n_clay_robots, n_obs_robots, n_geo_robots, GEO);
		if (ret > max_geode)
			return ret;
		return max_geode;
	}
	if (new_ore >= bprint.c_obsidian[0] && new_clay >= bprint.c_obsidian[1] && n_obs_robots < bprint.max_obs)
	{
		check = 2;
		int next_ore = new_ore - bprint.c_obsidian[0];
		int next_clay = new_clay - bprint.c_obsidian[1];
		ret = solve(bprint, next_ore, next_clay, new_obsidian, new_geode, new_time, n_ore_robots, n_clay_robots, n_obs_robots, n_geo_robots, OBS);
		if (ret > max_geode)
			max_geode = ret;
	}
	if (new_ore >= bprint.c_clay && n_clay_robots < bprint.max_clay && check == 0)
	{
		check++;
		int next_ore = new_ore - bprint.c_clay;
		ret = solve(bprint, next_ore, new_clay, new_obsidian, new_geode, new_time, n_ore_robots, n_clay_robots, n_obs_robots, n_geo_robots, CLAY);
		if (ret > max_geode)
			max_geode = ret;
	}
	if (new_ore >= bprint.c_ore && n_ore_robots < bprint.max_ore && check < 2)
	{
		check += 2;
		int next_ore = new_ore - bprint.c_ore;
		ret = solve(bprint, next_ore, new_clay, new_obsidian, new_geode, new_time, n_ore_robots, n_clay_robots, n_obs_robots, n_geo_robots, ORE);
		if (ret > max_geode)
			max_geode = ret;
	}
	if (check > 2)
		return max_geode;
	ret = solve(bprint, new_ore, new_clay, new_obsidian, new_geode, new_time, n_ore_robots, n_clay_robots, n_obs_robots, n_geo_robots, NONE);
	if (ret > max_geode)
		max_geode = ret;
	return max_geode;
}

int main(void)
{
	std::ifstream					ifs("input"); //pruned all the text from input, is just digits seperated by spaces now
	std::string						line;
	std::array<Blueprint, 30>		bprints;
	int								quality = 0, geodes, result = 1, n_bprint;

	int i = 0;
	for (std::getline(ifs, line); !ifs.eof(); std::getline(ifs, line), ++i) {
		parse(line, bprints, i);
	}
	for (i = 0; i < 30; i++) {
		geodes = solve(bprints[i], 0, 0, 0, 0, 24, 1, 0, 0, 0, 0);
		quality = quality + geodes * (i + 1);
	}
	std::cout << "p1:" << quality << std::endl;

	for (i = 0; i < 3; i++) {
		geodes = solve(bprints[i], 0, 0, 0, 0, 32, 1, 0, 0, 0, 0);
		result = result * geodes;
	}
	std::cout << "p2:" << result << std::endl;
	return 0;
}
