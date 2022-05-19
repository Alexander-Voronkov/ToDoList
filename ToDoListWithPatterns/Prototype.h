#pragma once
#include "Priority.h"
class Prototype
{
public:
	virtual Prototype* clone()const = 0;
};