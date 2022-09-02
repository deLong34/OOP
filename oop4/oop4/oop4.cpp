//oop4.cpp Домашняя работа по 4 уроку ООП
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <iterator>
using namespace std;

/////////////--1--///////////
class ArrayInt
{
private:
	int m_lenght;
	int* m_data;
public:
	ArrayInt() : m_lenght(0), m_data(nullptr) { }
	ArrayInt(int _size) : m_lenght(_size)
	{
		if (_size > 0)
			m_data = new int[m_lenght];
		else
			m_data = nullptr;
	}
	ArrayInt(int _size, int init_value) : m_lenght(_size)
	{
		if (_size > 0)
			m_data = new int[m_lenght];
		else
			m_data = nullptr;
		for (size_t i = 0; i < m_lenght; i++)
		{
			m_data[i] = init_value;
		}
	}
	~ArrayInt()
	{
		delete[] m_data;
		m_data = nullptr;
	}
	int size()
	{
		return m_lenght;
	}
	friend ostream& operator<<(ostream& out, ArrayInt& AI);
	int& operator[] (int index)
	{
		assert(index >= 0 && index < m_lenght);
		return m_data[index];
	}
	void clear()
	{
		if (m_data != nullptr)
		{
			delete[] m_data;
			m_data = nullptr;
			m_lenght = 0;
		}
	}
	void resize(int newSize)
	{
		if (newSize == m_lenght) return;
		if (newSize <= 0)
		{
			clear();
			return;
		}
		int* newData = new int[newSize];
		int CopySize = (newSize >= m_lenght) ? m_lenght : newSize;
		for (size_t i = 0; i < CopySize; i++)
		{
			newData[i] = m_data[i];
		}
		delete m_data;
		m_data = newData;
		m_lenght = newSize;
	}
	void insert(int value, int index)
	{
		resize(m_lenght + 1);
		for (size_t i = m_lenght - 1; i > index; i--)
		{
			m_data[i] = m_data[i - 1];
		}
		m_data[index] = value;
	}
	void pop_back() //удаляем из конца массива
	{
		resize(m_lenght - 1);
	}
	void pop_front() //удаляет из начала массива
	{
		for (size_t i = 0; i < m_lenght - 1; i++)
		{
			m_data[i] = m_data[i + 1];
		}
		resize(m_lenght - 1);
	}
	void sort()//сортируем пузырьком
	{
		int tmp = 0;
		for (size_t i = 0; i < m_lenght - 1; i++)
		{
			for (size_t j = i + 1; j < m_lenght; j++)
			{
				if (m_data[i] < m_data[j])
				{
					tmp = m_data[i];
					m_data[i] = m_data[j];
					m_data[j] = tmp;
				}
			}

		}
	}
	void print() //печатаем
	{
		for (size_t i = 0; i < m_lenght; i++)
		{
			cout << m_data[i] << " ";
		}
		cout << endl;
	}
};
// перегрузка <<
ostream& operator<<(ostream& out, ArrayInt& AI)
{
	for (size_t i = 0; i < AI.size(); i++)
	{
		out << AI.m_data[i] << " ";
	}
	return out;
}
//////////--3--///////////
enum Mast { chervy, buby, piky, kresty } mast;
enum Nominal { tus = 1, dvoyka, troyka, chetverka, pyaterka, shesterka, semerka, vosmerka, devyatka, desyatka, valet, dama, korol } nominal;
class Card
{
public:
	Card(Nominal _nom, Mast _mas) : Nom(_nom), Mas(_mas) { }
	~Card() {}
	void Flip() { View == false ? View = true : View = false; }
	int GetValue() 
	{
		int val = 0;
		val = Nom;
		if (val > 10)
		{
			val = 10;
		}
		return val; 
	}
private:
	Mast Mas;
	Nominal Nom;
	bool View = false;
};///
class Hand
{
public:
	Hand()
	{
    	cards.reserve(7);
	}
	virtual ~Hand()
	{
		Clear();
	}
	void Add(Card* _Card)
	{
		cards.push_back(_Card);
	}
	void Clear()
	{
		cards.clear();
	}
	int GetTotal()
	{
		if (cards.empty())
		{
			return 0;
		}
		int total = 0;
		bool isTuz = false;
		for (size_t i = 0; i < cards.size(); i++)
		{
			total += cards[i]->GetValue();
		}
		for (size_t i = 0; i < cards.size(); i++)
		{
			if (cards[i]->GetValue() == Nominal::tus)
			{
				if (total <= 11) total += 10;
			}
		}
		return total;
	}
private:
	vector<Card*> cards;
};
////////////////////////////
int main()
{
	setlocale(LC_ALL, "Rus");
	ArrayInt Arr(10, 7);
	cout << Arr << endl;
	//Arr.clear();
	//cout << Arr << "clear" << endl;
	Arr.resize(9);
	cout << Arr << endl;
	Arr.insert(8, 9);
	cout << Arr << endl;
	Arr.sort();
	Arr.insert(10, 9);
	Arr.print();
	Arr.sort();
	Arr.print();
	///////-2-//////////
	vector<int> V1(10, 11);
	V1[2] = 1;
	V1[5] = 5;
	ArrayInt ArrV1(1, V1[0]);
	//ArrV1.print();
	if (V1.size() != 0)
	{
		for (size_t i = 1; i < V1.size() - 1; i++)
		{
			bool flag = false;
			for (size_t j = 0; j < ArrV1.size(); j++)
			{
				if (V1[i] == ArrV1[j])
				{
					flag = true;
					break;
				}
			}
			if (flag == false)
			{
				ArrV1.insert(V1[i], 0);
			}
		}
	}
	ArrV1.print();
	cout << "В нашем векторе " << ArrV1.size() << " различных значений." << endl;
}