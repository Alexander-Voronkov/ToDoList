#pragma once
#include "Strategy.h"
class ListOfTasks
{
	std::vector<Prototype*>tasks;
	FindStrategy* fs=nullptr;
public:
	ListOfTasks(std::vector<Prototype*>tasks) { this->tasks = tasks; }
	ListOfTasks() {  }
	void change_Task(int number)
	{
		system("cls");
		std::string buff;
		gotoxy((80 - 16) / 2, 5);
		std::cout << "¬ведiть завданн€:";
		while (buff.empty())
		{
			gotoxy((80 - 16) / 2, 7);
			std::cout << "                                  ";
			gotoxy((80 - 16) / 2, 7);
			getline(std::cin, buff);
		}
		(*(dynamic_cast<Task*>(this->tasks[number]))).changeTask(buff);
	}
	void changeTag(int number)
	{
		system("cls");
		gotoxy((80 - 28) / 2, 4);
		std::cout << "¬ведiть бажаний тег пошуку:" << std::endl;
		std::string tag = " ";
		while (*tag.begin() != '#')
		{
			gotoxy((80 - 29) / 2, 6);
			std::cout << "                                      ";
			gotoxy((80 - 29) / 2, 6);
			std::cin >> tag;
			std::cin.ignore();
		}
		(*(dynamic_cast<Task*>(this->getTasks()[number]))).setTag(tag);
	}
	void changePriority(int number)
	{
		system("cls");
		int p = 3;
		while (p > 2 || p < 0)
		{
			gotoxy((80 - 58) / 2 - 1, 5);
			std::cout << "                                                         ";
			gotoxy((80 - 58) / 2 - 1, 5);
			std::cout << "¬ведiть прiорiтет задачi(0-низький, 1-середнiй, 2-високий):";
			gotoxy((80 - 24) / 2 - 1, 7);
			std::cout << "                                                         ";
			gotoxy((80 - 24) / 2 - 1, 7);
			std::cin >> p;
			std::cin.ignore();
		}
		(*(dynamic_cast<Task*>(this->tasks[number]))).setPriority(p);
		std::stable_sort(this->tasks.begin(), this->tasks.end(), [&](Prototype* a, Prototype* b) {return ((*dynamic_cast<Task*>(a)) > (*dynamic_cast<Task*>(b))); });
	}
	void change_Date(int number)
	{
		system("cls");
		int d = 32, m = 13, y = 2021;
		while (d > 31 || d < 1)
		{
			gotoxy((80 - 25) / 2, 9);
			std::cout << "                        ";
			gotoxy((80 - 25) / 2, 9);
			std::cout << "¬ведiть день виконанн€:";
			gotoxy((80 - 25) / 2, 11);
			std::cout << "                         ";
			gotoxy((80 - 25) / 2, 11);
			std::cin >> d;
			std::cin.ignore();
		}
		while (m > 12 || m < 1)
		{
			gotoxy((80 - 26) / 2, 13);
			std::cout << "                         ";
			gotoxy((80 - 26) / 2, 13);
			std::cout << "¬ведiть мiс€ць виконанн€:";
			gotoxy((80 - 26) / 2, 15);
			std::cout << "                         ";
			gotoxy((80 - 26) / 2, 15);
			std::cin >> m;
			std::cin.ignore();
		}
		while (y < 2022)
		{
			gotoxy((80 - 24) / 2 - 1, 17);
			std::cout << "                       ";
			gotoxy((80 - 24) / 2 - 1, 17);
			std::cout << "¬ведiть рiк виконанн€:";
			gotoxy((80 - 24) / 2 - 1, 19);
			std::cout << "                       ";
			gotoxy((80 - 24) / 2 - 1, 19);
			std::cin >> y;
			std::cin.ignore();
		}
		(*(dynamic_cast<Task*>(this->tasks[number]))).changeDate(d, m, y);
	}
	void delTask(int number)
	{
		tasks.erase(tasks.begin() + number);
	}
	std::vector<Prototype*>& getTasks() { return tasks; }
	void addNewTask(std::string t, int p, int d = 01, int m = 01, int y = 1999)
	{
		std::string tag;
		if (t.empty())
		{
			return;
		}
		if (!t.empty())
		{
			size_t q = t.find_first_of(' ');
			if (q != std::string::npos)
			{
				int len = 0;
				tag.push_back('#');
				while (t.c_str()[len] != ' ')
					tag.push_back(t.c_str()[len++]);
			}
			else
			{
				tag.push_back('#');
				tag += t;
			}
		}
		tasks.push_back((dynamic_cast<Task*>(tasks[tasks.size()-1])->clone())); // € б≥льше не знаю €к реал≥зувати той прототип
		(dynamic_cast<Task*>(tasks[tasks.size() - 1])->setTag(tag));
		(dynamic_cast<Task*>(tasks[tasks.size() - 1])->changeTask(t));
		(dynamic_cast<Task*>(tasks[tasks.size() - 1])->changeDate(d,m,y));
		(dynamic_cast<Task*>(tasks[tasks.size() - 1])->setPriority(p));
		std::stable_sort(this->tasks.begin(), this->tasks.end(), [&](Prototype* a, Prototype* b) {return ((*dynamic_cast<Task*>(a)) > (*dynamic_cast<Task*>(b))); });
	}
	std::vector<Prototype*> searchByDate(int d, int m, int year)
	{
		delete fs;
		fs = new FindByDate;
		return dynamic_cast<FindByDate*>(fs)->find(this->tasks, d, m, year);
	}
	std::vector<Prototype*> searchByTag(std::string tag)
	{
		delete fs;
		fs = new FindByTag;
		return dynamic_cast<FindByTag*>(fs)->find(this->tasks,tag);
	}
	std::vector<Prototype*> searchByTask(std::string task)
	{
		delete fs;
		fs = new FindByTask;
		return dynamic_cast<FindByTask*>(fs)->find(this->tasks, task);
	}
	std::vector<Prototype*> searchByPriority(int p)
	{
		delete fs;
		fs = new FindByPriority;
		return dynamic_cast<FindByPriority*>(fs)->find(this->tasks, p);
	}
	friend std::ostream& operator<<(std::ostream& out, ListOfTasks& obj)
	{
		if (!obj.tasks.empty())
		{
			for (auto& task : obj.tasks)
			{
				out << (*dynamic_cast<Task*>(task));
			}
		}
		else
		{
			system("cls");
			gotoxy((80 - 29) / 2, 3);
			out << "¬и ще нiчого не планували";
			Sleep(1);
		}
		return out;
	}
	friend std::ofstream& operator<<(std::ofstream& out, ListOfTasks& obj)
	{
		for (size_t i = 0; i < obj.tasks.size(); i++)
		{
			out << (* dynamic_cast<Task*>(obj.tasks[i]));
		}
		return out;
	}
};