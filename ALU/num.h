#ifndef NUM_H
#define NUM_H

#include "iostream"
#include <vector>

using namespace std;

class num
{
public:
    num();
    num(string num);
    ~num();

    void setSigno(string sig);
    string getSigno();
    void setExponente(int exp);
    int getExponente();
    void setMantisa(string man);
    string getMantisa();

    int getExponenteNumero(string exp);
    int getNum(int posicion);

private:
    string signo;
    int exponente;
    string mantisa;
};

#endif // NUM_H
