#ifndef ALU_H
#define ALU_H

#include "num.h"
#include "string.h"
#include <iostream>

using namespace std;

class alu
{
public:
    alu();
    alu(num *num1, num *num2, string op);
    ~alu();

    void tipoOperacion();
    float funcionSuma();
    float funcionMultiplicacion();
    float funcionDivision();
    string complemento2(string mantisa);
    string desplazarDerecha(string mantisa, int posicion, int digito);
    int OR(string mantisa);
    string sumaBinaria(string parametro1, string parametro2);
    int normalizar(string parametro);

private:
    num *numero1, *numero2;
    string operacion;


};

#endif // ALU_H
