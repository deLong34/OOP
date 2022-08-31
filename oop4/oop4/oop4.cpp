//oop4.cpp Домашняя работа по 4 уроку ООП
#include <iostream>
#include <string>
#include <cassert>
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
	void print()
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

////////////////////////////
int main()
{
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

}

