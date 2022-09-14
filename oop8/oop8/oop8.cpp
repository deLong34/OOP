
#include<iostream>
#include<stdexcept>
#include"Header.h"

using namespace std;

///////--1--////////
class DivisionByZero : public std::exception
{
public:
	DivisionByZero(const string& err = "Деление на 0!") : error(err)
	{};
	const char* what() const noexcept 
	{ 
		return error.c_str(); 
	}
private:
	string error;
};

template <typename T>
double_t div(T dividend, T divider)
{
	if (divider == 0) 
		throw DivisionByZero();

	return static_cast<double_t>(dividend) / divider;
}
///////--2--////////
class Ex
{
public:
	Ex(double arg) : x(arg)
	{};
	double what() const noexcept
	{ 
		return x; 
	};
private:
	double x;
};

class Bar
{
public:
	Bar() : y(0)
	{};
	void set(double a)
	{
		if (y + a > 100) throw Ex(a * y);
		else y = a;
	}
private:
	double y;
};
//

int main()
{
	setlocale(LC_ALL, "RU");
	//-1-////////////
	cout << "Работаем с div:" << endl;
	double a, b, result;
	try
	{
		cout << "введите числитель a = ";
		a = getUserInput<double>(true, true, true);
		cout << "введите знаменатель b = ";
		b = getUserInput<double>(true, true, true);
		result = div<double>(a, b);
		cout << a << " / " << b << " = " << result << endl;
	}
	catch (const std::exception& exception)
	{
		cerr << "Возникла ошибка: " << exception.what() << endl;
	}
	catch (...)
	{
		cerr << "Возникла не известная ошибка!" << endl;
	}
	//-2-///////////////
	cout << "Работаем с Bar:" << endl;
	Bar bar;
	double с;
	try
	{
		do
		{
			cout << "Введите число (double): ";
			с = getUserInput<double>(true, true, true);
			bar.set(с);
			cout << endl;
		} while (с != 0);
	}
	catch (const Ex& ex)
	{
		cerr << "Ошибка Ex (" << ex.what() << ")" << endl;
	}
	catch (...)
	{
		cerr << "Возникла не известная ошибка!" << endl;
	}
	//-3-/////////
	system("cls");
	Robot rb;
	char c;
	do
	{
		cout << "Работа с классом Робот:" << endl;
		rb.print();
		cout << endl << "Для перемещения W-A-S-D, для выхода Q" << endl;
		c = getUserInputKey();
		system("cls");
		try
		{
			switch (c)
			{
			case 'd':
			case 'D':
				rb.move(Direction::RIGHT);
				break;
			case 'a':
			case 'A':
				rb.move(Direction::LEFT);
				break;
			case 'w':
			case 'W':
				rb.move(Direction::UP);
				break;
			case 's':
			case 'S':
				rb.move(Direction::DOWN);
				break;
			case 'q':
			case 'Q':
				break;
			default:
				rb.move(Direction::other);
			}
		}
		catch (const OffTheField& ex)
		{
			cerr << "Попытка выхода за пределы поля! " << ex.what() << endl;
		}
		catch (const IllegalCommand& ex)
		{
			cerr << "Указано неизвестное направление!" << endl;
		}
		catch (...)
		{
			cerr << "Неизвестная ошибка!" << endl;
		}
	} while (c != 'q' && c != 'Q');

}

