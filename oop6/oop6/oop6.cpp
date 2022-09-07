// oop6.cpp 
#include <iostream>
#include <iosfwd>
#include "myGame.cpp"
using namespace std;


/////////////--1--/////////////////
template <typename T>
T getCinInput (bool allowZero, bool allowNegative, bool checkAllinput)
{
	while (true)
	{
		T input;
		cin >> input;
		if (cin.fail() || (input < 0) && !allowNegative || (input == 0) && !allowZero)
		{
			cout << "Ошибка данных, повторите ввод: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		{
			if ((cin.peek() != cin.widen('\n')) && checkAllinput)
			{
				cout << "Ошибка данных, повторите ввод: ";
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
/////////////--2--///////////////
ostream& endll(ostream& out)
{
	char enter = out.widen('\n');
	out.put(enter);
	out.put(enter);
	out.flush();
	return out;
}
//////////////--3--////////
///-Player-///
class Player : public GenericPlayer
{
public:
	Player(const string& name) : GenericPlayer(name) {};
	//~Player() {};
	virtual bool IsHitting() const
	{
		cout << name << ", нужна еще карта? (Y/N): ";
		char res;
		cin >> res;
		return (res == 'y' || res == 'Y');
	}
	void Win() const
	{
		cout << name << " выиграл!" << endl;
	}
	void Lose() const
	{
		cout << name << " проиграл." << endl;
	}
	void Push() const
	{
		cout << name << " сыграл вничью." << endl;
	}
private:
};
////////////--4--///////////
///-House-///
class House : public GenericPlayer
{
public:
	House(const string& name = "House") : GenericPlayer(name) {}
	virtual ~House() = default;
	virtual bool IsHitting() const override
	{
		return (GetTotal() <= 16);
	}
	void FlipFirstCard()
	{
		if (!(cards.empty()))
		{
			cards[0]->Flip();
		}
		else
		{
			cout << "Нет карт для переворота!\n";
		}
	}
private:


};
//////////--5--//////////
///перегрузка << для Card
ostream& operator<<(ostream& os, const Card& aCard)
{
	const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8",
							 "9","10", "J", "Q", "K" };
	const string SUITS[] = { "♣️", "♦️", "♥️", "♠️" };
	if (aCard.View)
	{
		os << RANKS[static_cast<uint16_t>(aCard.Nom)] << SUITS[static_cast<uint16_t>(aCard.Mas)];
	}
	else
	{
		os << "XX";
	}
	return os;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	//-1-//
	cout << "Вводите одно целое число:" << endl;
	int a = getCinInput<int>(true, true, true);
	cout << "Ваше число: " << a << endl;
	//-2-//
	cout << "Работа endll:" << endl;
	cout << "Привет! Сейчас будет endll: " << endll;
	cout << "Что там сверху после endll?" << endl;

}

