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
    RGBA()
    {
        m_red = 0;
        m_green = 0;
        m_blue = 0;
        m_alpha = 255;
    };
    ~RGBA();

private:
    uint8_t m_red, m_green, m_blue, m_alpha;


};

    int main()
    {
        setlocale(LC_ALL, "Rus");
        Power P;
        //P.set(2.3, 3);
        P.calculate();

    }