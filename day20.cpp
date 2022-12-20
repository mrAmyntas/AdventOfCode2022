#include <iostream>
#include <fstream>
#include <list>
#include <array>

enum {
	PART_1 = 1,
	PART_2 = 811589153
};

#define SIZE 5000

typedef struct s_list
{
	long			content;
	int				index;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

t_list	*ft_lstnew(int val)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	tmp->content = val;
	tmp->next = NULL;
	return (tmp);
}

void mix(t_list *current, int index, int part)
{
	t_list	*tmp;
	long	val, x;

	while (current->index != index)
		current = current->next;
	val = current->content * part;
	x = val / (SIZE - 1);
	if (x != 0)
		val = val - (x * (SIZE - 1));
	if (val == 0)
		return;
	current->prev->next = current->next;
	current->next->prev = current->prev;
	tmp = current;
	if (val > 0)
	{
		while (val > 0)
		{
			current = current->next;
			val--;
		}
		tmp->next = current->next;
		tmp->prev = current;
		current->next->prev = tmp;
		current->next = tmp;
	}
	else
	{
		while (val < 0)
		{
			current = current->prev;
			val++;
		}
		tmp->prev = current->prev;
		tmp->next = current;
		current->prev->next = tmp;
		current->prev = tmp;
	}
}

t_list *make_list(void)
{
	std::ifstream	ifs("input");
	std::string		line;

	std::getline(ifs, line);
	int val = std::stoi(line);
	t_list *head =  ft_lstnew(val);
	head->index = 0;

	std::getline(ifs, line);
	val = std::stoi(line);
	t_list *next =  ft_lstnew(val);
	next->prev = head;
	next->index = 1;
	head->next = next;

	int index = 2;
	for (std::getline(ifs, line); !ifs.eof(); std::getline(ifs, line), index++) {
		val = std::stoi(line);
		t_list *tmp =  ft_lstnew(val);
		tmp->index = index;
		tmp->prev = next;
		next->next = tmp;
		next = tmp;
	}
	next->next = head;
	head->prev = next;
	ifs.close();
	return head;
}

int main(void)
{
	long	result1 = 0, result2 = 0, index = 0;
	t_list	*head1 = make_list();
	t_list	*head2 = make_list();

	for (index = 0; index < SIZE; index++) {
		mix(head1, index, PART_1);
		mix(head2, index, PART_2);
	}
	for (int i = 0; i < (SIZE * 9); i++, index++) {
		if (index == SIZE)
			index = 0;
		mix(head2, index, PART_2);
	}
	while (head1->content != 0)
		head1 = head1->next;
	while (head2->content != 0)
		head2 = head2->next;
	for (int i = 0; i <= 3000; i++) {
		if (i % 1000 == 0)
		{
			result1 += head1->content * PART_1;
			result2 += head2->content * PART_2;
		}
		head1 = head1->next;
		head2 = head2->next;
	}
	std::cout << "p1:" << result1 << std::endl;
	std::cout << "p2:" << result2 << std::endl;
	return 0;
}
