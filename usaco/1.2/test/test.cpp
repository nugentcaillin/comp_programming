/*
ID: ncaillin
TASK: test 
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::ifstream input { "test.in" };
	std::ofstream output { "test.out" };

	int a {};
	int b {};
	input >> a >> b;
	output << a + b << std::endl;
	return 0;
}
