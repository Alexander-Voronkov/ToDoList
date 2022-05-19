#pragma once
#include "Menu.h"
namespace ToDoList
{
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
						gotoxy((80 - dynamic_cast<Task*>(this->lot.getTasks()[c])->length()) / 2, 6);
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
					this->lot.getTasks().push_back(dynamic_cast<Prototype*>(new Task(t)));
					t.clear();
				}
				std::stable_sort(this->lot.getTasks().begin(), this->lot.getTasks().end(), [&](Prototype* a, Prototype* b) {return (( * dynamic_cast<Task*>(a)) > (*dynamic_cast<Task*>(b))); });
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
