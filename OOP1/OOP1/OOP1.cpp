// Домашнее задание по 2 уроку ООП на С++, Литвинов Дмитрий
#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

///////////////////==1==////////////////////
class Person
{
protected:
    string name;
    unsigned int age;
    char gender;
    unsigned int weight;
public:
    Person() { cout << __FUNCTION__ << endl; }
    Person(string _name, unsigned int _age, char _gender, unsigned int _weignt) : name(_name), age(_age), gender(_gender), weight(_weignt)
    {
        cout << __FUNCTION__ << endl; 
    }
    ~Person() { cout << __FUNCTION__ << endl; }
    void setName(string _name)
    {
        name = _name;
    }
    void setAgeW(unsigned int _age, unsigned int _weihgt)
    {
        age = _age;
        weight = _weihgt;
    }
    void print()
    {
        cout << name << " " << age << " " << gender << " " << weight << " " << endl;
    }
};
//Студент
class Student : public Person
{
public:
    Student(int _year, string _name, unsigned int  _age, char _gender, unsigned int _weignt) : Person(_name, _age, _gender, _weignt)
    {
        yearSt = _year;
        name = _name;
        age = _age;
        gender = _gender;
        weight = _weignt;
        studentCount++;
    }
    ~Student()  { cout << __FUNCTION__ << endl; }
    void setYearSt(int _yearSt)
    {
        yearSt = _yearSt;
    }
    void yearInc()
    {
        yearSt++;
    }
    void print()
    {
        Person::print();
        cout << yearSt << " " << endl;
    }
    void counter()
    {
        cout << "Всего студентов: " << studentCount << endl;
    }
private:
    int yearSt;
    static unsigned int studentCount;
};

unsigned int Student::studentCount = 0;
/////////////////////////--2--/////////////////////////
class Fruit
{
public:
    Fruit() { cout << __FUNCTION__ << endl; }
    Fruit(string _color) : color(_color) { cout << __FUNCTION__ << endl; }
    ~Fruit() { cout << __FUNCTION__ << endl; };
    string getName()
    {
        return name;
    }
    string getColor()
    {
       return color;
    }
protected:
    string name;
    string color;
};
//яблоко
class Apple : public Fruit
{
public:
    Apple() { cout << __FUNCTION__ << endl; }
    Apple(string _color) : Fruit(_color) 
    { 
        name = "apple";
    }
    ~Apple() { cout << __FUNCTION__ << endl; };
    string getName()
    {
        return name;
    }
protected:
    string name = "apple";
};
//банана
class Banana : public Fruit
{
public:
    Banana()
    {
        name = "banana";
        color = "yellow";
    };
    ~Banana() { cout << __FUNCTION__ << endl; };
private:
};
//ГранниСмит
class GrannySmith : public Apple
{
public:
    //GrannySmith();
    GrannySmith()
    {
        color = "Green";
    };
    ~GrannySmith() { cout << __FUNCTION__ << endl; };
    string getName()
    {
        return variety + " " + Apple::getName();
    }
private:
    string variety = "Granny Smith";
};

int main()
{
    setlocale(LC_ALL, "Rus"); 
 ///////////////////--1--//////////////////// 
    Student St1(2000, "Mike", 32, 'M', 90);  
    Student St2(2001, "Ira", 18, 'W', 45);
    St1.print();
    St2.print();
    St1.counter();
 ///////////////////--2--////////////////////
    Apple a("Red");
    Banana b;
    GrannySmith c;
    cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
}
////////////--3--///////////////////////
// Игра Blackjack
// Базовый класс Person и производные от него Player и Dealer
// Базовый класс карта Card с полями Масть и Имя (являются перечислением enum), номинал (количество очков)
// Производный класс от игрока и дилера - рука Hand с полем очки Score и методом получения карты Add().
//
// Создаем объект Дилер и от 1 Игроков
// Создаем объект Карта с методом, который случайным образом задает карте масть и имя (тройка, король и тп.)
// В начале игры Игроку и Дилеру в подкласс Рука выдается по две случайные Карты, метод Add должен увеличивать номинал Руки, в соответствии с наминалом полученной карты.
// После этого Иргоку1 задается вопрос: Еще? При положительном - в его Руке запускается метод Add(), при отрицательном - проверка, есть ли еще игроки,
// если есть, то этот вопрос задается Игроку2 или Дилеру, если игроков больше не. Если Дилер отвечает на вопрос Еще - отрицательно, то сраниваются наминалы на Руках всех играков и 
// принимается решение о победе.
// Надеюсь, я правильно понял задание 3? Продумать и описать, а не раелизовать в коде?
