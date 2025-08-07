/*
ID: ncaillin
TASK: ride
PROG: ride
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <string>

int to_magic_number(const std::string& str)
{
	int magic_number { 1 };

	for (const char& c: str)
	{
		magic_number *= (int)(c - 'A' + 1); // maps A-Z to 1-26
		magic_number %= 47;
	}
	return magic_number;
}

int main()
{
	std::ifstream in { "ride.in" };
	std::ofstream out { "ride.out" };
	
	std::string group_name {};
	std::string comet_name {};

	in >> group_name >> comet_name;

	if (to_magic_number(group_name) == to_magic_number(comet_name))
	{
		out << "GO" << std::endl;
	} else 
	{
		out << "STAY" << std::endl;
	}
	
	return 0;
}
