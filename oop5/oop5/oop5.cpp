//oop5.cpp 
// Домашнее задание по 5 уроку ООП на С++, Литвинов Дмитрий
#include <iostream>
#include <cstdint>
#include <string>
#include "myGame.cpp"

using namespace std;

////////////////--1--////////////////
template<typename T>
class Pair1
{
public:
	Pair1(const T& _fi, const T& _se) : fi(_fi), se(_se) {};
	T first() const 
	{ 
		return fi; 
	};
	T second() const 
	{ 
		return se; 
	};
private:
	T fi, se;
};
//////////////--2--////////////////////
template<typename T1, typename T2>
class Pair
{
public:
	Pair(const T1& _fi, const T2& _se) : fi(_fi), se(_se) {};
	T1 first() const 
	{ 
		return fi; 
	};
	T2 second() const 
	{ 
		return se; 
	};
private:
	T1 fi;
	T2 se;
};
//////////////--3--////////////////////
template <typename T3>
class StringValuePair : public Pair<string, T3>
{
public:
	StringValuePair(const string& str, const T3& se) : Pair<string, T3>(str, se)
	{};
};
//////////////--4--////////////////////
class GenericPlayer : public Hand
{
public:
	GenericPlayer(const string& _name = ""): name(_name) {};
	virtual ~GenericPlayer() = default;

	virtual bool IsHitting() const //нужни ли игроку еще карта?
	{
		return false;
	}
	bool IsBoosted() //возвращает True, если перебор и False, если перебора нет
	{
		return (GetTotal() > 21);
	}
	void Bust() const
	{
		cout << "У игрока " << name << " перебор!" << endl;
	}

private:
	string name;
};

int main()
{
	setlocale(LC_ALL, "Rus");
	//////-1-//////
	//Pair1<int> p1(6, 9);
	//cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
	//const Pair1<double> p2(3.4, 7.8);
	//cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
	//////-2-//////
	Pair<int, double> p1(6, 7.8);
	cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
	const Pair<double, int> p2(3.4, 5);
	cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
	//////-3-//////
	StringValuePair<int> svp("Amazing", 7);
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
	//////
	return 0;
}