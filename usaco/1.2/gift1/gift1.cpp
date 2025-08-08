/*
ID: ncaillin
TASK: gift1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

int main()
{
	std::ifstream in { "gift1.in" };
	std::ofstream out { "gift1.out" };

	std::map<std::string, int> balances {};
	std::vector<std::string> names_in_order {};
	int name_count {};
	std::string curr_name {};
	std::string curr_giver {};
	int total_amount {};
	int num_people {};
	int amount_per_person {};
	int remainder {};


	in >> name_count;

	for (int i { 0 }; i < name_count; ++i)
	{
		in >> curr_name;
		balances.insert({ curr_name, 0 });
		names_in_order.push_back(curr_name);
	}

	
	while (name_count --> 0)
	{
		in >> curr_giver >> total_amount >> num_people;
		amount_per_person = (total_amount > 0) ? total_amount / num_people : 0;
		remainder = (num_people > 0) ? total_amount % num_people : total_amount;

		balances.at(curr_giver) += remainder - total_amount;

		for (int i { 0 }; i < num_people; i++)
		{
			in >> curr_name;
			balances.at(curr_name) += amount_per_person;
		}
	}

	for (auto it = names_in_order.begin(); it != names_in_order.end(); ++it)
	{
		out << *it << " " << balances.at(*it) << std::endl;
	}
	

	return 0;
}
