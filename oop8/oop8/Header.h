#pragma once
//#include <cstdint>
//#include <stdexcept>
#include <string>
//#include <iostream>
using namespace std;

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
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			if ((cin.peek() != cin.widen('\n')) && checkAllinput)
			{
				cout << "Ошибка ввода, повторите ввод: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				return input;
			}
		}
	}
}
///--3--//////////////////
#define SIZE_FIELD 10

struct Pos
{
	int16_t x, y;
};

enum class Direction
{
	RIGHT, LEFT, DOWN, UP, other
};

class OffTheField : public std::exception
{
public:
	OffTheField(Pos pos, Direction dir)
	{
		error = "Текущая позиция робота (";
		error += std::to_string(pos.x);
		error += ",";
		error += std::to_string(pos.y);
		error += ") направление движения: ";
		switch (dir)
		{
		case Direction::RIGHT:
			error += "вправо";
			break;
		case Direction::LEFT:
			error += "влево";
			break;
		case Direction::DOWN:
			error += "вниз";
			break;
		case Direction::UP:
			error += "вверх";
			break;
		default:
			break;
		}
	};

	const char* what() const noexcept { return error.c_str(); };

private:
	std::string error;
};

char getUserInputKey()
{
	char c;
	cin.get(c);
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return c;
}

class IllegalCommand : public std::exception
{
public:
	IllegalCommand() = default;
};

class Robot
{
public:
	Robot() : currPos{}
	{};

	void move(Direction dir)
	{
		switch (dir)
		{
		case Direction::RIGHT:
			if (++currPos.x >= SIZE_FIELD)
			{
				--currPos.x;
				throw OffTheField(currPos, dir);
			}
			break;
		case Direction::LEFT:
			if (--currPos.x < 0)
			{
				++currPos.x;
				throw OffTheField(currPos, dir);
			}
			break;
		case Direction::DOWN:
			if (++currPos.y >= SIZE_FIELD)
			{
				--currPos.y;
				throw OffTheField(currPos, dir);
			}
			break;
		case Direction::UP:
			if (--currPos.y < 0)
			{
				++currPos.y;
				throw OffTheField(currPos, dir);
			}
			break;
		default: throw IllegalCommand();
			break;
		}
	};

	void print()
	{
		for (size_t i = 0; i < SIZE_FIELD; i++)
		{
			for (size_t j = 0; j < SIZE_FIELD; j++)
			{
				if (j == currPos.x && i == currPos.y) std::cout << "X";
				else std::cout << "_";
			}
			std::cout << std::endl;
		}
	}

private:
	Pos currPos;
};