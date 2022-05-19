#pragma once
#include "Prototype.h"
struct DateOfCompletion
{
public:
	int day;
	int month;
	int year;
	DateOfCompletion(int d, int m, int y) :day(d), month(m), year(y) {}
	DateOfCompletion& operator()(int d, int m, int y)
	{
		this->day = d;
		this->month = m;
		this->year = y;
	}
	friend std::ofstream& operator<<(std::ofstream& out, DateOfCompletion& obj)
	{
		out << obj.day << std::endl << obj.month << std::endl << obj.year << std::endl;
		return out;
	}
	friend std::ifstream& operator>>(std::ifstream& in, DateOfCompletion& obj)
	{
		in >> obj.day >> obj.month >> obj.year;
		return in;
	}
	bool operator<(const DateOfCompletion& doc)
	{
		if (this->day < doc.day && this->month <= doc.month && this->year <= doc.year)
			return 1;
		return 0;
	}
	bool operator>(const DateOfCompletion& doc)
	{
		if (this->day > doc.day && this->month >= doc.month && this->year >= doc.year)
			return 1;
		return 0;
	}
};