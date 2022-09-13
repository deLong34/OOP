//oop7.cpp: Домашняя работа по 7 уроку ООП
#pragma once
#include<iostream>
#include<cstdint>
#include<ostream>
#include<iomanip>
//#include"myGame.cpp"
#include"myGame.h"
using namespace std;

class Date
{
public:
	Date(int d = 1, int m = 1, int y = 1800) : day(d), month(m), year(y) {}
	int getDay() const
	{
		return day;
	}
	int getMonth() const
	{
		return month;
	}
	int getYear() const
	{
		return year;
	}
private:
	int day, month, year;
};
//перегрузка оператора вывода даты
std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << std::setw(2) << std::setfill('0') << date.getDay() << "."
		<< std::setw(2) << std::setfill('0') << date.getMonth() << "."
		<< std::setw(4) << std::setfill('0') << date.getYear() << "г." << std::endl;
	return out;
}
////--2--////////////
std::shared_ptr<Date> maxDate(const std::shared_ptr<Date>& date1, const std::shared_ptr<Date>& date2)
{
	if (date1.get()->getYear() > date2.get()->getYear()) 
		return std::shared_ptr<Date>(date1);
	else if (date1.get()->getYear() < date2.get()->getYear()) 
		return std::shared_ptr<Date>(date2);
	else if (date1.get()->getMonth() > date2.get()->getMonth()) 
		return std::shared_ptr<Date>(date1);
	else if (date1.get()->getMonth() < date2.get()->getMonth()) 
		return std::shared_ptr<Date>(date2);
	else if (date1.get()->getDay() > date2.get()->getDay()) 
		return std::shared_ptr<Date>(date1);
	else 
		return std::shared_ptr<Date>(date2);
};
void swapDate(std::shared_ptr<Date>& date1, std::shared_ptr<Date>& date2)
{
	auto tmp = move(date1);
	date1 = move(date2);
	date2 = move(tmp);
};
///--3--//////////////////////////
std::string getUserInputTxt()
{
	while (true)
	{
		string input;
		cin >> input;
		if (cin.fail())
		{
			cout << "Ошибка ввода, повторите ввод: ";
			cin.clear();
		}
		else
		{
			cin.clear();
			return input;
		}
	}
}
template <typename T>
T getUserInput(bool allowZero, bool allowNegative, bool checkAllinput)
{
	while (true)
	{
		T input;
		cin >> input;
		if (cin.fail() || (input < 0) && !allowNegative || (input == 0) && !allowZero)
		{
			cout << "Ошибка ввода, повторите ввод: ";
			cin.clear();
		}
		else
		{
			if ((cin.peek() != cin.widen('\n')) && checkAllinput)
			{
				cout << "Ошибка ввода, повторите ввод: ";
				cin.clear();
			}
			else
			{
				cin.clear();
				return input;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RU");
  ///-1-///
	std::cout << "Работаем с Date:" << std::endl;
	time_t now = time(0);
	tm currTime;
	gmtime_s(&currTime, &now);
	auto today = std::make_unique<Date>(currTime.tm_mday, currTime.tm_mon + 1, currTime.tm_year + 1900);
	std::unique_ptr<Date> date;
	std::cout << "Сегодня: " << std::endl;
	cout << "День: " << today.get()->getDay() << endl;
	cout << "Месяц: " << today.get()->getMonth() << endl;
	cout << "Год: " << today.get()->getYear() << endl << endl;
	cout << *today << endl;
	cout << "today: " << (static_cast<bool>(today) ? "не нулевой\n" : "нулевой\n");
	cout << "date: " << (static_cast<bool>(date) ? "не нулевой\n" : "нулевой\n");
	cout << "Перемещаем today в date" << endl;
	date = move(today);
	cout << "today: " << (static_cast<bool>(today) ? "не нулевой\n" : "нулевой\n");
	cout << "date: " << (static_cast<bool>(date) ? "не нулевой\n" : "нулевой\n");
	///-2-///
	cout << "Поиск максимальной даты:" << endl << endl;
	auto date1 = make_shared<Date>(29, 9, 1981);
	auto date2 = make_shared<Date>(12, 9, 2022);
	cout << "date1: " << *date1 << endl;
	cout << "date2: " << *date2 << endl;
	auto dateMax = maxDate(date1, date2);
	cout << "dateMax: " << *dateMax << endl;
	cout << "Проверяем исходные объекты:" << endl;
	cout << "date1: " << *date1 << endl;
	cout << "date2: " << *date2 << endl << endl;
	cout << "Меняем date1 с date2: " << endl;
	swapDate(date1, date2);
	cout << "date1: " << *date1 << endl;
	cout << "date2: " << *date2 << endl << endl;
	cout << "Проверяем dateMax: " << endl;
	cout << "dateMax: " << *dateMax << endl;
	//////////--Игра Blackjack--///////////////
	cout << "\t\tСыграем в Blackjack!" << endl << endl;
	int numPlayers = 0;
	while (numPlayers < 1 || numPlayers > 7)
	{
		cout << "На сколько игроков раздаем? (1 - 7): ";
		numPlayers = getUserInput<int>(false, false, false);
	}
	vector<string> names;
	names.reserve(numPlayers);
	string name;
	for (int i = 0; i < numPlayers; ++i)
	{
		cout << "Введите имя " << i + 1 << " игрока: ";
		name = getUserInputTxt();
		names.push_back(name);
	}
	cout << endl;
	// игровой цикл
	Game myGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N')
	{
		myGame.Play();
		cout << "\nСыграем ещё? (Y/N): ";
		cin >> again;
	}
}