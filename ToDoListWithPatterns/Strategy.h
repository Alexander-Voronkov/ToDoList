#pragma once
#include "Task.h"
class FindStrategy
{
public:
	virtual ~FindStrategy() = 0 {}
};

class FindByDate :public FindStrategy
{
public:
	virtual std::vector<Prototype*> find(std::vector<Prototype*>tasks,int d,int m,int year)
	{
		std::vector<Prototype*> arr;
		for (auto& i : tasks)
		{
			if ((*dynamic_cast<Task*>(i)).getDate().day == d && (*dynamic_cast<Task*>(i)).getDate().month == m && (*dynamic_cast<Task*>(i)).getDate().year == year)
				arr.push_back(new Task(dynamic_cast<Task*>(i)));
		}
		return arr;
	}
};

class FindByTag :public FindStrategy
{
public:
	virtual std::vector<Prototype*>find(std::vector<Prototype*>tasks, std::string tag)
	{
		std::vector<Prototype*> arr;
		for (auto& i : tasks)
		{
			if ((*dynamic_cast<Task*>(i)).getTag() == tag)
				arr.push_back(new Task(dynamic_cast<Task*>(i)));
		}
		return arr;
	}
};

class FindByTask :public FindStrategy
{
public:
	virtual std::vector<Prototype*>find(std::vector<Prototype*>tasks, std::string task)
	{
		std::vector<Prototype*> arr;
		for (auto& i : tasks)
		{
			if ((*dynamic_cast<Task*>(i)).getTask() == task)
				arr.push_back(new Task(dynamic_cast<Task*>(i)));
		}
		return arr;
	}
};

class FindByPriority :public FindStrategy
{
public:
	virtual std::vector<Prototype*>find(std::vector<Prototype*>tasks, int p)
	{
		std::vector<Prototype*> arr;
		for (auto& i : tasks)
		{
			if ((*dynamic_cast<Task*>(i)).getPriority() == p)
				arr.push_back(new Task(dynamic_cast<Task*>(i)));
		}
		return arr;
	}
};