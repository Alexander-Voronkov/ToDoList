#pragma once
#include "Logo.h"



class Menu
{
public:
	static int select_vertical(std::vector <std::string> menu, HorizontalAlignment ha, int y = 12)
	{
		std::setlocale(0, "UKR");
		int maxLen = 0;
		for (size_t i = 0; i < menu.size(); i++)
		{
			if (menu[i].length() > maxLen)
				maxLen = menu[i].length();
		}
		int x = 0;
		switch (ha)
		{
		case Center: x = 40 - maxLen / 2; break;
		case Left:   x = 0;	              break;
		case Right:  x = 80 - maxLen;     break;
		}
		char c;
		int pos = 0;
		do
		{
			for (int i = 0; i < menu.size(); i++)
			{
				if (i == pos)
				{
					SetColor(0, 15);
					gotoxy(x, y + i);
					std::cout << std::setw(maxLen) << std::left;
					gotoxy(x, y + i);
					std::cout << menu[i] << std::endl;
					SetColor(15, 0);
				}
				else
				{
					SetColor(15, 0);
					gotoxy(x, y + i);
					std::cout << std::setw(maxLen) << std::left;
					gotoxy(x, y + i);
					std::cout << menu[i] << std::endl;
				}
			}
			c = _getch();
			switch (c)
			{
			case 72: if (pos > 0)               pos--; break;
			case 80: if (pos < menu.size() - 1) pos++; break;
			case 27: return -1; break;
			}
		} while (c != 13);
		SetColor(7, 0);

		for (size_t i = 0; i < 2; i++)
		{
			SetColor(15, 0);
			gotoxy(x, y + pos);
			std::cout << std::setw(maxLen) << std::left;
			gotoxy(x, y + pos);
			std::cout << menu[pos] << std::endl;
			Sleep(300);
			SetColor(0, 15);
			gotoxy(x, y + pos);
			std::cout << std::setw(maxLen) << std::left;
			gotoxy(x, y + pos);
			std::cout << menu[pos] << std::endl;
			SetColor(15, 0);
			Sleep(300);
		}
		return pos;
	}

	template<class T>
	static int select_vertical(std::vector <T> menu, HorizontalAlignment ha, int y = 12)
	{
		std::setlocale(0, "UKR");
		int maxLen = 0;
		for (size_t i = 0; i < menu.size(); i++)
		{
			if (menu[i].length() > maxLen)
				maxLen = menu[i].length();
		}
		int x = 0;
		switch (ha)
		{
		case Center: x = 40 - maxLen / 2; break;
		case Left:   x = 0;	              break;
		case Right:  x = 80 - maxLen;     break;
		}
		char c;
		int pos = 0;
		do
		{
			for (int i = 0; i < menu.size(); i++)
			{
				if (i == pos)
				{
					SetColor(0, 15);
					gotoxy(x, y + i);
					std::cout << std::setw(maxLen) << std::left;
					gotoxy(x, y + i);
					std::cout << menu[i] << std::endl;
					SetColor(15, 0);
				}
				else
				{
					SetColor(15, 0);
					gotoxy(x, y + i);
					std::cout << std::setw(maxLen) << std::left;
					gotoxy(x, y + i);
					std::cout << menu[i] << std::endl;
				}
			}
			c = _getch();
			switch (c)
			{
			case 72: if (pos > 0)               pos--; break;
			case 80: if (pos < menu.size() - 1) pos++; break;
			case 27: return -1; break;
			}
		} while (c != 13);
		SetColor(7, 0);

		for (size_t i = 0; i < 2; i++)
		{
			SetColor(15, 0);
			gotoxy(x, y + pos);
			std::cout << std::setw(maxLen) << std::left;
			gotoxy(x, y + pos);
			std::cout << menu[pos] << std::endl;
			Sleep(300);
			SetColor(0, 15);
			gotoxy(x, y + pos);
			std::cout << std::setw(maxLen) << std::left;
			gotoxy(x, y + pos);
			std::cout << menu[pos] << std::endl;
			SetColor(15, 0);
			Sleep(300);
		}
		return pos;
	}
};
