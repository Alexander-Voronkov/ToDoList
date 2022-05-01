#pragma once
#include "Menu.h"
namespace ToDoList
{
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

	class Task
	{
		std::string task = "";
		std::string tag = "";
		Priority p = Priority::LOW;
		DateOfCompletion doc = { 1,1,1999 };
	public:
		Task() {}
		bool operator<(const Task& obj)
		{
			if (this->p < obj.p)
				return 1;
			return 0;
		}
		bool operator>(const Task& obj)
		{
			if (this->p < obj.p)
				return 0;
			return 1;
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
		Task(std::string t, int q,std::string tag, int d, int m, int y) :task(t),tag(tag), doc(d, m, y){ switch (q) { case 0:p = Priority::LOW; break; case 1:p = Priority::MEDIUM; break; case 2:p = Priority::HIGH; break; } }
		friend std::ofstream& operator<<(std::ofstream& out, Task& obj)
		{
			out << obj.task << std::endl << obj.p << std::endl<<obj.tag<<std::endl<<obj.doc.day << std::endl<<obj.doc.month << std::endl << obj.doc.year << std::endl;
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
			std::setlocale(0,"UKR");
			out << "         " << obj.task << "         " << obj.tag << "         " << obj.doc.day<<" / "<<obj.doc.month<<" / "<<obj.doc.year << "         ";
			switch (obj.p)
			{
			case 0:out << "LOW" << std::endl; break;
			case 1:out << "MEDIUM" << std::endl; break;
			case 2:out << "HIGH" << std::endl; break;
			}
			return out;
		}
		void changeDate(int d,int m,int y)
		{
			this->doc = DateOfCompletion(d, m, y);
		}
	};

	class ListOfTasks
	{
		std::vector<Task>tasks;
	public:
		ListOfTasks(std::vector<Task>tasks) { this->tasks = tasks; }
		ListOfTasks() {  }
		void change_Task(int number)
		{
			system("cls");
			std::string buff;
			gotoxy((80 - 16) / 2, 5);
			std::cout << "Введiть завдання:";
			while (buff.empty())
			{
				gotoxy((80 - 16) / 2, 7);
				std::cout << "                                  ";
				gotoxy((80 - 16) / 2, 7);
				getline(std::cin, buff);
			}
			this->tasks[number].changeTask(buff);
		}
		void changeTag(int number)
		{
			system("cls");
			gotoxy((80-28)/2,4);
			std::cout << "Введiть бажаний тег пошуку:" << std::endl;
			std::string tag=" ";
			while (*tag.begin() != '#')
			{
				gotoxy((80 - 29) / 2, 6);
				std::cout << "                                      ";
				gotoxy((80 - 29) / 2, 6);
				std::cin >> tag;
				std::cin.ignore();
			}
			this->getTasks()[number].setTag(tag);
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
				std::cout << "Введiть прiорiтет задачi(0-низький, 1-середнiй, 2-високий):";
				gotoxy((80 - 24) / 2 - 1, 7);
				std::cout << "                                                         ";
				gotoxy((80 - 24) / 2 - 1, 7);
				std::cin >> p;
				std::cin.ignore();
			}
			this->tasks[number].setPriority(p);
			std::sort(this->tasks.begin(), this->tasks.end(), [&](Task a, Task b) {return a > b; });
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
				std::cout << "Введiть день виконання:";
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
				std::cout << "Введiть мiсяць виконання:";
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
				std::cout << "Введiть рiк виконання:";
				gotoxy((80 - 24) / 2 - 1, 19);
				std::cout << "                       ";
				gotoxy((80 - 24) / 2 - 1, 19);
				std::cin >> y;
				std::cin.ignore();
			}
			this->tasks[number].changeDate(d,m,y);
		}
		void delTask(int number)
		{
			tasks.erase(tasks.begin()+number);
		}
		std::vector<Task>& getTasks() { return tasks; }
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
			tasks.push_back(Task(t, p,tag,d, m, y));
			std::sort(this->tasks.begin(), this->tasks.end(), [&](Task a, Task b) {return a > b; });
		}
		std::vector<Task> searchByDate(int d,int m,int year)
		{
			std::vector<Task> arr;
			for (auto& i : tasks)
			{
				if (i.getDate().day == d && i.getDate().month == m && i.getDate().year == year)
					arr.push_back(i);
			}
			return arr;
		}
		std::vector<Task> searchByTag(std::string tag)
		{
			std::vector<Task> arr;
			for (auto& i : tasks)
			{
				if (i.getTag()==tag)
					arr.push_back(i);
			}
			return arr;
		}
		std::vector<Task> searchByTask(std::string task)
		{
			std::vector<Task> arr;
			for (auto& i : tasks)
			{
				if (i.getTask() == task)
					arr.push_back(i);
			}
			return arr;
		}
		std::vector<Task> searchByPriority(int p)
		{
			std::vector<Task> arr;
			for (auto& i : tasks)
			{
				if (i.getPriority() == p)
					arr.push_back(i);
			}
			return arr;
		}
		friend std::ostream& operator<<(std::ostream& out, ListOfTasks& obj)
		{
			if (!obj.tasks.empty())
			{
				for (auto& task : obj.tasks)
				{
					out << task;
				}
			}
			else
			{
				system("cls");
				gotoxy((80-29)/2,3);
				out << "Ви ще нiчого не планували";
				Sleep(1);
			}
			return out;
		}
		friend std::ofstream& operator<<(std::ofstream& out, ListOfTasks& obj)
		{
			for (size_t i = 0; i < obj.tasks.size(); i++)
			{
				out << obj.tasks[i];
			}
			return out;
		}
		friend std::ifstream& operator>>(std::ifstream& in, ListOfTasks& obj)
		{
			for (size_t i = 0; i < obj.tasks.size(); i++)
			{
				in >> obj.tasks[i];
			}
			return in;
		}
	};

	class Application
	{
		ListOfTasks lot;
		void addNewTask()
		{
			    system("cls");
				std::string buff;
				gotoxy((80 - 16) / 2, 5);
				std::cout << "Введiть завдання:";
				while (buff.empty())
				{					
					gotoxy((80 - 16) / 2, 7);
					std::cout << "                                     ";
					gotoxy((80 - 16) / 2, 7);
					getline(std::cin, buff);
				}
				int d=32,m=13,y=2021,p=3;
				while (d > 31||d<1)
				{
					gotoxy((80 - 24) / 2, 9);
					std::cout << "                        ";
					gotoxy((80 - 24) / 2, 9);
					std::cout << "Введiть день виконання:";
					gotoxy((80 - 16) / 2, 11);
					std::cout << "                         ";
					gotoxy((80 - 16) / 2, 11);
					std::cin >> d;
					std::cin.ignore();
				}
				while (m > 12||m<1)
				{
					gotoxy((80 - 26) / 2, 13);
					std::cout << "                         ";
					gotoxy((80 - 26) / 2, 13);
					std::cout << "Введiть мiсяць виконання:";
					gotoxy((80 - 16) / 2, 15);
					std::cout << "                         ";
					gotoxy((80 - 16) / 2, 15);
					std::cin >> m;
					std::cin.ignore();
				}
				while (y < 2022)
				{
					gotoxy((80 - 23) / 2 - 1, 17);
					std::cout << "                       ";
					gotoxy((80 - 23) / 2 - 1, 17);
					std::cout << "Введiть рiк виконання:";
					gotoxy((80 - 16) / 2 , 19);
					std::cout << "                       ";
					gotoxy((80 - 16) / 2, 19);
					std::cin >> y;
					std::cin.ignore();
				}
				while (p > 2 || p < 0)
				{
					gotoxy((80 - 62) / 2 - 1, 21);
					std::cout << "                                                         ";
					gotoxy((80 - 62) / 2 - 1, 21);
					std::cout << "Введiть прiорiтет завдання(0-низький, 1-середнiй, 2-високий):";
					gotoxy((80 - 16) / 2 , 23);
					std::cout << "                                                         ";
					gotoxy((80 - 16) / 2 , 23);
					std::cin >> p;
					std::cin.ignore();
				}
				lot.addNewTask(buff,p,d,m,y);
		}
		void changeTask()
		{
			if (!this->lot.getTasks().empty())
			{
				while (true)
				{
					system("cls");
					gotoxy((80-18)/2,6);
					std::cout << "Оберiть завдання:";
					int c = Menu::select_vertical(this->lot.getTasks(), HorizontalAlignment::Left);
					switch (c)
					{
					case -1:return; break;
					default:
						system("cls");
						gotoxy((80 - 39) / 2, 4);
						std::cout << "Що ви хочете зробити з цим завданням?" << std::endl;
						gotoxy((80 - this->lot.getTasks()[c].length()) / 2, 6);
						int b = Menu::select_vertical({ "Видалити","Змiнити дату","Змiнити завдання","Змiнити прiорiтет","Змiнити тег пошуку" }, HorizontalAlignment::Center);
						switch (b)
						{
						case 27:return;
						case 0:this->lot.delTask(c); return;
						case 1:this->lot.change_Date(c);  break;
						case 2:this->lot.change_Task(c); break;
						case 3:this->lot.changePriority(c); break;
						case 4:this->lot.changeTag(c); break;
						}
					}
				}
			}
			else
			{
				system("cls");
				gotoxy((80-27)/2,4);
				std::cout << "Спочатку додайте завдання.";
				system("pause>0");
			}
		}
		void showTasks()
		{
			system("cls");
			std::cout<< "         " << "Завдання:" << "         " << "Тег пошуку:" << "         " << "Дата:" << "         " << "Прiорiтет:" << std::endl << std::endl;
			for (size_t i = 0; i < 80; i++)
				std::cout << "_";
			std::cout << lot;
			system("pause>0");
		}
		void findByDate()
		{
			system("cls");
			int d = 32, m = 13, y = 2021;
			while (d > 31 || d < 1)
			{
				gotoxy((80 - 25) / 2, 9);
				std::cout << "                        ";
				gotoxy((80 - 25) / 2, 9);
				std::cout << "Введiть день виконання:";
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
				std::cout << "Введiть мiсяць виконання:";
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
				std::cout << "Введiть рiк виконання:";
				gotoxy((80 - 24) / 2 - 1, 19);
				std::cout << "                       ";
				gotoxy((80 - 24) / 2 - 1, 19);
				std::cin >> y;
				std::cin.ignore();
			}
			if (!this->lot.searchByDate(d, m, y).empty())
			{
				system("cls");
				int c = Menu::select_vertical(this->lot.searchByDate(d, m, y), HorizontalAlignment::Left);
				if (c == -1)
					return;
			}
			else
			{
				system("cls");
				gotoxy((80-37)/2,5);
				std::cout << "За вашим запитом нiчого не знайдено.";
				system("pause>0");
			}
		}
		void findByPriority()
		{
			system("cls");
			int p = 3;
			while (p > 2 || p < 0)
			{
				gotoxy((80 - 28) / 2 - 1, 5);
				std::cout << "                                                         ";
				gotoxy((80 - 28) / 2 - 1, 5);
				std::cout << "Введiть прiорiтет завдання:";
				gotoxy((80 - 16) / 2, 7);
				std::cout << "                                                         ";
				gotoxy((80 - 16) / 2, 7);
				std::cin >> p;
				std::cin.ignore();
			}
			if (!this->lot.searchByPriority(p).empty())
			{
				system("cls");
				int c = Menu::select_vertical(this->lot.searchByPriority(p), HorizontalAlignment::Left);
				if (c == -1)
					return;
			}
			else
			{
				system("cls");
				gotoxy((80 - 37) / 2, 5);
				std::cout << "За вашим запитом нiчого не знайдено.";
				system("pause>0");
			}
		}
		void findByTag()
		{
			system("cls");
			gotoxy((80 - 28) / 2, 5);
			std::cout << "Введiть тег пошуку:" << std::endl;
			std::string tag = " ";
			while (*tag.begin() != '#')
			{
				gotoxy((80 - 29) / 2, 7);
				std::cout << "                                      ";
				gotoxy((80 - 29) / 2, 7);
				std::cin >> tag;
				std::cin.ignore();
			}
			if (!this->lot.searchByTag(tag).empty())
			{
				system("cls");
				int c = Menu::select_vertical(this->lot.searchByTag(tag), HorizontalAlignment::Left);
				if (c == -1)
					return;
			}
			else
			{
				system("cls");
				gotoxy((80 - 37) / 2, 5);
				std::cout << "За вашим запитом нiчого не знайдено.";
				system("pause>0");
			}
		}
		void findByTask()
		{
			system("cls");
			std::string buff;
			gotoxy((80 - 16) / 2, 5);
			std::cout << "Введiть завдання:";
			while (buff.empty())
			{
				gotoxy((80 - 16) / 2, 7);
				std::cout << "                                  ";
				gotoxy((80 - 16) / 2, 7);
				getline(std::cin, buff);
			}
			if (!this->lot.searchByTask(buff).empty())
			{
				system("cls");
				int c = Menu::select_vertical(this->lot.searchByTask(buff), HorizontalAlignment::Left);
				if (c == -1)
					return;
			}
			else
			{
				system("cls");
				gotoxy((80 - 37) / 2, 5);
				std::cout << "За вашим запитом нiчого не знайдено.";
				system("pause>0");
			}
		}
		void find()
		{
			if (!this->lot.getTasks().empty())
			{
				while (true)
				{
					system("cls");
					int c = Menu::select_vertical({ "Знайти за датою","Знайти за прiорiтетом","Знайти за тегом","Знайти за завданням" }, HorizontalAlignment::Center);
					switch (c)
					{
					case 0:findByDate(); break;
					case 1:findByPriority(); break;
					case 2:findByTag(); break;
					case 3:findByTask(); break;
					case -1:return; break;
					}
				}
			}
			else
			{
				system("cls");
				gotoxy((80-34)/2, 5);
				std::cout << "Ви ще не додали жодного завдання.";
				system("pause>0");
			}
		}
		void load()
		{
			std::ifstream in("Tasks.txt");
			if (in.is_open())
			{
				Task t;
				while (in>>t)
				{
					this->lot.getTasks().push_back(t);
					t = Task();
				}
				std::sort(this->lot.getTasks().begin(), this->lot.getTasks().end(), [&](Task a, Task b) {return a > b; });
			}
			in.close();

		}
		void save()
		{
			std::ofstream out("Tasks.txt");			
			out << lot;
			out.close();
		}
	public:
		void menu()
		{
			load();
			while (true)
			{
				system("cls");
				Logo::print("ToDoList",HorizontalAlignment::Center,4,ConsoleColor::Yellow);
				int c = Menu::select_vertical({ "Переглянути список","Додати нове завдання","Змiнити iснуюче завдання","Вихiд","Знайти завдання","Зберегти данi"}, HorizontalAlignment::Center);
				switch (c)
				{
				case 0:showTasks(); break;
				case 1:addNewTask(); break;
				case 2:changeTask(); break;
				case -1:case 3:save(); exit(0); break;
				case 4:find(); break;
				case 5:save(); break;
				}
			}
		}
	};
}
