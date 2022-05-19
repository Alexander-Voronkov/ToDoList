#pragma once
#include "DateOfCompletion.h"
class Task :public Prototype
{
	std::string task = "";
	std::string tag = "";
	Priority p = Priority::LOW;
	DateOfCompletion doc = { 1,1,1999 };
public:
	Task() {}
	Task(Task* obj)
	{
		this->task = obj->task;
		this->tag = obj->tag;
		this->p = obj->p;
		this->doc = obj->doc;
	}
	void clear() 
	{
		task.clear();
		tag.clear();
		p = LOW;
		doc = {1,1,1999};
	}
	Prototype* clone()const override
	{
		return new Task(*this);
	}
	bool operator<(const Task& obj)
	{
		if (this->p < obj.p)
			return 1;
		return 0;
	}
	bool operator>(const Task& obj)
	{
		if (this->p > obj.p)
			return 1;
		return 0;
	}
	bool operator>=(const Task& obj)
	{
		if (this->p >= obj.p)
			return 1;
		return 0;
	}
	bool operator<=(const Task& obj)
	{
		if (this->p <= obj.p)
			return 1;
		return 0;
	}
	bool operator==(const Task& obj)
	{
		if (this->p == obj.p)
			return 1;
		return 0;
	}
	bool operator!=(const Task& obj)
	{
		if (this->p != obj.p)
			return 1;
		return 0;
	}
	void setTag(std::string tag)
	{
		this->tag = tag;
	}
	int length() { return task.length(); }
	Task(std::string t, int q, std::string tag, int d, int m, int y) :task(t), tag(tag), doc(d, m, y) { switch (q) { case 0:p = Priority::LOW; break; case 1:p = Priority::MEDIUM; break; case 2:p = Priority::HIGH; break; } }
	friend std::ofstream& operator<<(std::ofstream& out, Task& obj)
	{
		out << obj.task << std::endl << obj.p << std::endl << obj.tag << std::endl << obj.doc.day << std::endl << obj.doc.month << std::endl << obj.doc.year << std::endl;
		return out;
	}
	friend std::ifstream& operator>>(std::ifstream& in, Task& obj)
	{
		in >> obj.task;
		in >> obj.p;
		in >> obj.tag;
		in >> obj.doc.day;
		in >> obj.doc.month;
		in >> obj.doc.year;
		return in;
	}
	void setPriority(int a)
	{
		switch (a)
		{
		case 0:this->p = Priority::LOW; break;
		case 1:this->p = Priority::MEDIUM; break;
		case 2:this->p = Priority::HIGH; break;
		}
	}
	void changeTask(std::string t)
	{
		this->task = t;
	}
	DateOfCompletion& getDate() { return doc; }
	std::string& getTag() { return tag; }
	std::string& getTask() { return task; }
	int getPriority() { return p; }
	friend std::ostream& operator<<(std::ostream& out, Task& obj)
	{
		std::setlocale(0, "UKR");
		out << "         " << obj.task << "         " << obj.tag << "         " << obj.doc.day << " / " << obj.doc.month << " / " << obj.doc.year << "         ";
		switch (obj.p)
		{
		case 0:out << "LOW" << std::endl; break;
		case 1:out << "MEDIUM" << std::endl; break;
		case 2:out << "HIGH" << std::endl; break;
		}
		return out;
	}
	void changeDate(int d, int m, int y)
	{
		this->doc = DateOfCompletion(d, m, y);
	}
};
