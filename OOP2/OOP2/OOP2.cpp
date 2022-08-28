// Домашнее задание по 3 уроку ООП на С++, Литвинов Дмитрий
#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

////////////////--1--////////////////
class Figure
{
public:
	Figure() = default;
	virtual double area() = 0;
};
//Параллелограмм
class Parallelogram : public Figure
{
public:
	Parallelogram(double _x, double _y, double _a, double _h) : x(_x), y(_y), a(_a), h(_h) {}
	~Parallelogram() {}
	virtual double area() override
	{
		return a * h;
	}
protected:
	double x, y, a, h;
};
//Прямоугольник
class Rectangle : public Parallelogram
{
public:
	Rectangle(double _x, double _y, double _a, double _b) : Parallelogram(_x, _y, _a, _b) {}
	~Rectangle() {}
	virtual double area() override
	{
		return a * h;
	}
private:
};
//Квадрат
class Square : public Parallelogram
{
public:
	Square(double _x, double _y, double _a) : Parallelogram(_x, _y, _a, _a) {}
	~Square() {}
	virtual double area() override
	{
		return a * a;
	}
private:
};
//Ромб
class Rhombus : public Parallelogram
{
public:
	Rhombus(double _x, double _y, double _a, double _h) : Parallelogram(_x, _y, _a, _h) {}
	~Rhombus() {}
	virtual double area() override
	{
		return a * h;
	}
private:

};
//Круг
class Circle : public Figure
{
public:
	Circle(double _x, double _y, double _R) : x(_x), y(_y), R(_R) {}
	~Circle() {};
	virtual double area() override
	{
		return 3.14 * R * R;
	}
private:
	double x, y, R;
};
///////////////////--2--///////////
//Машина
class Car
{
public:
	Car(string _company, string _model) : company(_company), model(_model) { cout << __FUNCTION__ << endl; }
	Car() {}
	~Car() {}
protected:
	string company, model;
};
//Легковая
class PassengerCar : virtual public Car
{
public:
	PassengerCar(string _company, string _model) : Car(_company, _model) { cout << __FUNCTION__ << endl; }
	~PassengerCar() {}
protected:
};
//Автобус
class Bus : virtual public Car
{
public:
	Bus(string _company, string _model) : Car(_company, _model) { cout << __FUNCTION__ << endl; }
	~Bus() {}
protected:
};
//Минивен
class Minivan : public PassengerCar, public Bus
{
public:
	Minivan(string _company, string _model) : PassengerCar(_company, _model), Bus(_company, _model) { cout << __FUNCTION__ << endl; }
	~Minivan() {}
private:
};
////////////////--3--/////////////
class Fraction
{
private:
	double num, den;
	double res = 1;
public:
	Fraction(double _num = 1, double _den = 1) : num(_num), den(_den)
	{
		if (den != 0)
		{
			//cout << "Наша дробь: " << num << " / " << den << endl;
			res = num / den;
		}
		else {
			cout << "Делить на 0 нельзя!" << endl;
		}
	}
	void show() {
		cout << "Наша дробь: " << num << " / " << den << endl;
	}
	Fraction operator+(Fraction b) {
		return Fraction(this->res + b.res);
	}
	Fraction operator-(Fraction b) {
		return Fraction(this->res - b.res);
	}
	Fraction operator*(Fraction b) {
		return Fraction(this->res * b.res);
	}
	Fraction operator/(Fraction b) {
		return Fraction(this->res / b.res);
	}
	Fraction operator-() {
		return Fraction(-res);
	}
    bool operator<(Fraction b) {
		return this->res < b.res;
	}
	bool operator>=(Fraction b) {
		return this->res < b.res;
	}
	bool operator>(Fraction b) {
		return this->res > b.res;
	}
	bool operator<=(Fraction b) {
		return this->res > b.res;
	}
};
/////////////////--4--////////////
enum Mast { chervy, buby, piky, kresty } mast;
enum Nominal
{ tus = 1, dvoyka = 2, troyka, chetverka, pyaterka, shesterka, semerka, vosmerka, devyatka, desyatka, valet = 10, dama = 10, korol = 10 } nominal;
class Card
{
public:
	Card(Nominal _nom, Mast _mas) : Nom(_nom), Mas(_mas) {}
	~Card() {}
	void Flip()	{ View == false ? View = true : View = false; }
	Nominal GetValue() { return Nom; }
	
private:
	Mast Mas;
	Nominal Nom;
	bool View = false;
};
//////////////////////////////////
int main()
{
	setlocale(LC_ALL, "Rus");
	Minivan M1("Toyota", "Delica");
	Bus B1("Ikarus", "Ikar");
	PassengerCar P1("Volga", "Gas21");
//////////
	Fraction F1(2, 4);
	Fraction F2(2, 7);
	F1.show();
	F2.show();
	Fraction F3 = F1 + F2;
	F3.show();
	if (F1 < F2)
	{ cout << "Первая дробь меньше второй." << endl; }
	else { cout << "Первая дробь НЕ меньше второй." << endl; }

	Card C1(troyka, piky);
	int vol = C1.GetValue();
	cout << vol << endl;
}