#pragma once
#include "Logo.h"
enum Priority {
	LOW, MEDIUM, HIGH
};

std::ifstream& operator>>(std::ifstream& in, Priority& obj)
{
	int a;
	in >> a;
	switch (a)
	{
	case 0:obj = Priority::LOW; break;
	case 1:obj = Priority::MEDIUM; break;
	case 2:obj = Priority::HIGH; break;
	}
	return in;
}