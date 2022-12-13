#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>	

struct s_list {
	std::vector<std::pair<s_list, int > >	list_values;
	std::vector<std::pair<int, int> >		int_values;
	std::string								str;
};


void print_list(s_list A)
{	
	std::cout << "list:" << A.str << std::endl;
}

void print_set(std::vector<s_list> set)
{
	std::vector<s_list>::iterator it;

	for (it = set.begin(); it != set.end(); ++it){
		print_list(*it);
	}
}

void	setList(s_list & list)
{
	std::string::iterator	it, it2, it3;
	int						digit, open, i = 0;
	std::string				dig_str;

	for (it = list.str.begin(); it != list.str.end(); it++) {
		//find [
		if (*it == '[' && it != list.str.begin() )
		{
			s_list newlist;
			open = 1;
			//find corresponding ]
			for (it2 = it + 1; it2 != list.str.end(); it2++) {
				if (*it2 == '[')
					open++;
				if (*it2 == ']')
					open--;
				if (open == 0)
					break ;
			}
			//add list to its set of lists
			newlist.str = std::string(it, it2 + 1);
			setList(newlist);
			list.list_values.push_back(std::make_pair(newlist, i));
			i++;
			it = it2 + 1;
		}
		if (isdigit(*it))
		{
			if (isdigit(*(it + 1)))
				dig_str = std::string(it, it + 2);
			else
				dig_str = std::string(it, it + 1);
			digit = std::stoi(dig_str);
			list.int_values.push_back(std::make_pair(digit, i));
			i++;
		}
	}
}

bool	is_list(int index, s_list & list)
{
	std::vector<std::pair<s_list, int> >::iterator	l_it;
	std::vector<std::pair<int, int> >::iterator		i_it;

	for (i_it = list.int_values.begin(); i_it != list.int_values.end(); i_it++)
	{
		if ((*i_it).second == index)
			return false ;
	}
	for (l_it = list.list_values.begin(); l_it != list.list_values.end(); l_it++)
	{
		if ((*l_it).second == index)
			return true ;
	}
	if (i_it == list.int_values.end() && l_it == list.list_values.end())
		std::cout << "neither a list nor an int, error!\n";
	return false ;

}

int find_next_value_index(s_list & list, int nth)
{
	std::vector<std::pair<s_list, int> >::iterator	l_it;
	std::vector<std::pair<int, int> >::iterator		i_it;

	for (int i = nth; ; i++)
	{
		for (i_it = list.int_values.begin(); i_it != list.int_values.end(); i_it++)
		{
			if ((*i_it).second == i)
				return i;
		}
		for (l_it = list.list_values.begin(); l_it != list.list_values.end(); l_it++)
		{
			if ((*l_it).second == i)
				return i;
		}
		if (i_it == list.int_values.end() && l_it == list.list_values.end())
			break ;
	}
	return -1;
}

void	make_int_into_list( int index, s_list & list )
{
	std::vector<std::pair<int, int> >::iterator		i_it;
	std::vector<std::pair<s_list, int> >::iterator	l_it;

	for (i_it = list.int_values.begin(); i_it != list.int_values.end(); i_it++)
	{
		if ((*i_it).second == index)
		{
			s_list newlist;
			newlist.int_values.push_back(std::make_pair((*i_it).first, 0));
			l_it = list.list_values.begin();
			list.list_values.insert(l_it, std::make_pair(newlist, index));
			list.int_values.erase(i_it);
			break ;
		}
	}	
}

int	compare_lists(s_list & A, s_list & B)
{
	std::vector<std::pair<int, int> >::iterator		left_int, right_int;
	std::vector<std::pair<s_list, int> >::iterator	left_list, right_list;
	int i, j, k, result;

	for (k = 0;;k++)
	{
		i = find_next_value_index(A, k);
		j = find_next_value_index(B, k);
		if (i == -1 && j == -1) //no more values
			return 0;
		if (i == -1)
			return 1;
		if (j == -1)
			return -1;
		// if one is a list and the other isnt, make int into a list!
		if ( (is_list(i, A) && !is_list(j, B)) || (!is_list(i, A) && is_list(j, B)))
		{
			if (is_list(i, A) && !is_list(j, B))
				make_int_into_list(j, B);
			else
				make_int_into_list(i, A);
		}
		if (is_list(i, A) && is_list(j, B))
		{
			for (left_list = A.list_values.begin(); left_list != A.list_values.end(); left_list++) {
				if ((*left_list).second == i)
					break ;
			}
			for (right_list = B.list_values.begin(); right_list != B.list_values.end(); right_list++) {
				if ((*right_list).second == j)
					break ;
			}
			result = compare_lists((*left_list).first, (*right_list).first);
			if (result == 1)
				return 1;
			if (result == -1)
				return -1;
		}
		else	//two ints
		{
			for (left_int = A.int_values.begin(); left_int != A.int_values.end(); left_int++) {
				if ((*left_int).second == i)
					break ;
			}
			for (right_int = B.int_values.begin(); right_int != B.int_values.end(); right_int++) {
				if ((*right_int).second == j)
					break ;
			}
			if ((*left_int).first < (*right_int).first)
				return 1 ;
			else if ((*left_int).first > (*right_int).first)
				return -1 ;
		}
	}
	return 0;
}

void sort_lists(std::vector<s_list> & set)
{
	std::vector<s_list>::iterator	it, it2;
	int result = -1;

	while (result == -1)
	{
		result = 0;
		for (it = set.begin(); it + 1 != set.end(); it++) {
			if (compare_lists((*it), (*(it + 1))) == -1)
			{
				std::iter_swap(it, it+1);
				result = -1;
			}
		}
	}
}

int main (void)	
{
	std::vector<s_list>::iterator	it;
	std::vector<s_list>				set;
	std::ifstream	ifs("input");
	std::string		packet;
	int				i = 1, decoder = 1;

	std::getline(ifs, packet);
	for (; !ifs.eof(); std::getline(ifs, packet)) {
		if (packet.empty())
			continue ;
		s_list newlist;
		newlist.str = packet;
		setList(newlist);
		set.push_back(newlist);
	}
	sort_lists(set);
	// print_set(set);
	// std::cout <<set.size()<<std::endl;
	for (it = set.begin(); it != set.end(); it++, i++) {
		if ((*it).str == "[[2]]")
			decoder = decoder * i;
		if ((*it).str == "[[6]]")
			decoder = decoder * i;
	}
	std::cout << decoder << std::endl;
	return 0;
}

