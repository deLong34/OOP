// Домашнее задание по 2 уроку ООП на С++, Литвинов Дмитрий
#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

////////////////--1--////////////////
class Figure
{
public:
	Figure() = default;
};
//Параллелограмм
class Parallelogram : public Figure
{
public:
	Parallelogram(double _x, double _y, double _a, double _b, double _h) : x(_x), y(_y), a(_a), b(_b), h(_h) {};
	~Parallelogram() {};
protected:
	double x, y, a, b, h;
};
//Квадрат
class Square : public Parallelogram
{
public:
	Square (double _x, double _y, double _a) : Parallelogram(_x, _y, _a, _a, _a) {}
	~Square() {};

private:
};
//Ромб
class Rhombus : Parallelogram
{
public:
	Rhombus(double _x, double _y, double _a, double _h) : Parallelogram (_x, _y, _a, _a, _h) {}

private:

};
//Круг
class Circle : public Figure
{
public:
	Circle();
	~Circle();

private:

};

Circle::Circle()
{
}

Circle::~Circle()
{
}

//////////////////////////////////

int main()
{
    setlocale(LC_ALL, "Rus");



    std::cout << "Hello World!\n";
}