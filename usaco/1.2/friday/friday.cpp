/*
ID: ncaillin
TASK: friday 
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

int days_in_month(int month, int year)
{
	switch(month)
	{
		// 30 days: september, april, june, november
		case 9:
		case 4:
		case 6:
		case 11:
			return 30;
			break;
		// feburary
		case 2:
			if (year % 400 == 0) return 29;
			if (year % 100 == 0) return 28;
			if (year % 4 == 0) return 29;
			return 28;
			break;
		// rest have 31
		default:
			return 31;
			break;
	}
}

int main()
{
	std::ifstream in { "friday.in" };
	std::ofstream out { "friday.out" };
	std::vector<int> weekday_count(7, 0); // sat, sun, ...
	
	// the 13th of jan, 1900 is a saturday
	int month { 1 };
	int year { 1900 };
	int current_weekday { 0 };
	int num_years {};

	in >> num_years;
	int num_months { num_years * 12 };

	for (int i { 0 }; i < num_months; ++i)
	{
		// to get to the next 13th, we add the number of days in current month
		// next weekday is curr weekday + number of days mod 7
		weekday_count.at(current_weekday) += 1;

		current_weekday += days_in_month(month, year);
		current_weekday %= 7;
		month++;
		if (month == 13)
		{
			month = 1;
			year++;
		}
	}
	
	for (int i { 0 }; i < 7; ++i)
	{
		out << weekday_count.at(i);
		if (i < 6) out << " ";
		else out << "\n";
	}
	
	return 0;
}
