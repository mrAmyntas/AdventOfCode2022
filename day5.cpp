#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <vector>

#define AMOUNT 0
#define STACK1 1
#define STACK2 2

void	set_stacks(std::vector<std::stack<char>> & stacks)
{
	std::stack<char> s1;
	std::stack<char> s2;
	std::stack<char> s3;
	std::stack<char> s4;
	std::stack<char> s5;
	std::stack<char> s6;
	std::stack<char> s7;
	std::stack<char> s8;
	std::stack<char> s9;
	stacks.push_back(s1);
	stacks.push_back(s2);
	stacks.push_back(s3);
	stacks.push_back(s4);
	stacks.push_back(s5);
	stacks.push_back(s6);
	stacks.push_back(s7);
	stacks.push_back(s8);
	stacks.push_back(s9);
	stacks[0].push('Q');
	stacks[0].push('M');
	stacks[0].push('G');
	stacks[0].push('C');
	stacks[0].push('L');
	stacks[1].push('R');
	stacks[1].push('D');
	stacks[1].push('L');
	stacks[1].push('C');
	stacks[1].push('T');
	stacks[1].push('F');
	stacks[1].push('H');
	stacks[1].push('G');
	stacks[2].push('V');
	stacks[2].push('J');
	stacks[2].push('F');
	stacks[2].push('N');
	stacks[2].push('M');
	stacks[2].push('T');
	stacks[2].push('W');
	stacks[2].push('R');
	stacks[3].push('J');
	stacks[3].push('F');
	stacks[3].push('D');
	stacks[3].push('V');
	stacks[3].push('Q');
	stacks[3].push('P');
	stacks[4].push('N');
	stacks[4].push('F');
	stacks[4].push('M');
	stacks[4].push('S');
	stacks[4].push('L');
	stacks[4].push('B');
	stacks[4].push('T');
	stacks[5].push('R');
	stacks[5].push('N');
	stacks[5].push('V');
	stacks[5].push('H');
	stacks[5].push('C');
	stacks[5].push('D');
	stacks[5].push('P');
	stacks[6].push('H');
	stacks[6].push('C');
	stacks[6].push('T');
	stacks[7].push('G');
	stacks[7].push('S');
	stacks[7].push('J');
	stacks[7].push('V');
	stacks[7].push('Z');
	stacks[7].push('N');
	stacks[7].push('H');
	stacks[7].push('P');
	stacks[8].push('Z');
	stacks[8].push('F');
	stacks[8].push('H');
	stacks[8].push('G');

}

int main(void)
{
	std::vector<std::stack<char>>	stacks_p1, stacks_p2;
	std::ifstream					ifs("../input"); /* added newline, removed stacks */
	std::string						line;
	int								val[3];

	set_stacks(stacks_p1);
	stacks_p2 = stacks_p1;
	std::getline(ifs, line);
	for (; !ifs.eof(); std::getline(ifs, line)) {
		val[AMOUNT] = std::stoi( line.substr( line.find(" ") + 1, ( line.find("from") - 1 - line.find(" ") + 1 ) ) );
		val[STACK1] = std::stoi( line.substr( line.find("from") + 5, ( line.find("to") - 1 - line.find(" ") + 1 ) ) ) - 1;
		val[STACK2] = std::stoi( line.substr( line.find("to") + 3) ) - 1;
		/* part 2 */
		char crates[val[AMOUNT]];
		for (int i = 0; i < val[AMOUNT]; ++i) {
			crates[i] = stacks_p2[val[STACK1]].top();
			stacks_p2[val[STACK1]].pop();
		}
		for (int i = val[AMOUNT] - 1; i >= 0 ; --i) {
			stacks_p2[val[STACK2]].push(crates[i]);
		}
		/* part 1 */
		for (; val[AMOUNT] > 0; val[AMOUNT]--) {
			stacks_p1[val[STACK2]].push(stacks_p1[val[STACK1]].top());
			stacks_p1[val[STACK1]].pop();
		}
	}
	std::cout << "p1:";
	for (int i = 0; i < 9; i++) {
		std::cout << stacks_p1[i].top();
	}
	std::cout << std::endl << "p2:";
	for (int i = 0; i < 9; i++) {
		std::cout << stacks_p2[i].top();
	}
	std::cout << std::endl;
	return 0;
}
