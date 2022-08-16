// 

#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

///////////////////==1==////////////////////

class Power
{
private:
    float a, b;

public:
    Power()
    {
        a = 2.15;
        b = 3;
    }
    void set(float _a, float _b)
    {
        a = _a;
        b = _b;
    }

    void calculate()
    {
       // float c;
       // c = pow(a, b);
       // cout << "Результат: " << c << endl;
       //можно одной строкой:
        cout << "Результат: " << pow(a, b) << endl;
    }
};

//////////////////==2==//////////////////////

class RGBA
{
public:
    RGBA(uint8_t _m_red = 0, uint8_t _m_green = 0, uint8_t _m_blue = 0, uint8_t _m_alpha = 255)
    {
        m_red = _m_red;
        m_green = _m_green;
        m_blue = _m_blue;
        m_alpha = _m_alpha;
    };
  
    void print()
    {
        cout << "Выводим значения по 2 заданию: " << m_red << " . " << m_green << " . " << m_blue << " . " << m_alpha << endl;
    }

private:
    uint8_t m_red, m_green, m_blue, m_alpha;


};

/////////////////==3==//////////////////////

class Stack
{
public:
    void reset()
    {
        for (size_t i = 0; i < 9; i++)
        {
            arrA[i] = 0;
        }
        count = 0;
    }
    bool push(int _num)
    {
        if (count < 9)
        {
            arrA[count] = _num;
            count++;
            return true;
        }
        else
        {
            return false;
        }
    }
    int pop()
    {
        if (count != 0)
        {
            return arrA[count--];
        }
        else
        {
            cout << "Внимание!!! Стек пустой" << endl;
        }
    }
    void print()
    {
        cout << "(";
        for (size_t i = 0; i < count; i++)
        {
            cout << " " << arrA[i];
        }
        cout << " )" << endl;
    }


private:
    int arrA[10];
    int count;

};


    int main()
    {
        setlocale(LC_ALL, "Rus");
        Power P;
        //P.set(2.3, 3);
        P.calculate();
        RGBA R;
        R.print();

        Stack stack;
        stack.reset();
        stack.print();

        stack.push(3);
        stack.push(7);
        stack.push(5);
        stack.print();

        stack.pop();
        stack.print();

        stack.pop();
        stack.pop();
        stack.print();

        return 0;
    }