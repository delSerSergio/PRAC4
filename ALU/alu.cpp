#include "alu.h"
#include "bitset"

using namespace std;

alu::alu()
{

}

alu::alu(num *num1, num *num2, string op){

    numero1=num1;
    numero2=num2;
    operacion=op;
}

void alu::tipoOperacion(){
    if(operacion=="Suma"){
        funcionSuma();
    }
    /*
    if(operacion=="Multiplicacion"){
        funcionMultiplicacion();
    }
    if(operacion=="Division"){
        funcionDivision();
    }
    */
}

float alu::funcionSuma()
{
    cout<<"Comenzamos con la inicialización de las variables: "<<endl;

    cout<<"El signo del numero 2: "<<numero2->getMantisa()<<endl;

    //PASO 1
    int P = 0;
    int g =0, r = 0, st = 0;
    int n=24;

    // string m, P, g, r, st;
    bool operandosIntercambiados=false;
    bool complementoP=false;

    //PASO 2
    if(numero1->getExponente()<numero2->getExponente())
    {
        num *aux;
        aux=numero2;
        numero2=numero1;
        numero1=aux;

        cout<<"Se intercambian los numeros."<<endl;
        cout<<"Numero 1: "<<numero1<<endl;
        cout<<"Numero 2: "<<numero2<<endl;

        operandosIntercambiados=true;
    }

    //PASO 3
    int d;
    int expSol=numero1->getExponente();
    d=numero1->getExponente()-numero2->getExponente();

    //PASO 4
    string m;
    if(numero1->getSigno()!=numero2->getSigno())
    {
        cout<<"Empezamos a realizar el complemento 2 del numero 2."<<endl;

        m=complemento2(numero2->getMantisa());

        cout<<"La mantisa es: "<<numero2->getMantisa()<<endl;
        cout<<"La mantisa cambiada es: "<<m<<endl;
    }

    //PASO 5
    P = atoi(numero2->getMantisa().c_str());

    //PASO 6
    string G = std::to_string(g);
    string p = std::to_string(P);
    string R = std::to_string(r);
    G=p.substr(0,23);
    R=p.substr(1,23);
    st=OR(p.substr(2,23));

    //PASO 7
    if(numero1->getSigno()!=numero2->getSigno())
    {
        p=desplazarDerecha(numero2->getMantisa(), d, 1);
    }
    else
    {
        p=desplazarDerecha(numero2->getMantisa(), d, 0);
    }

    //PASO 8
    string Pac=sumaBinaria(p,numero1->getMantisa());
    int acarreo=atoi(Pac.substr(0,1).c_str());
    p=Pac.substr(1,24);

    //PASO 9
    if((numero1->getSigno()!=numero2->getSigno())&&(P=1)&&(acarreo=0)||d==0)
    {
           p=complemento2(p);
           complementoP=true;
    }

    //PASO 10
    if((numero1->getSigno()==numero2->getSigno())&&(acarreo=1))
    {
        //st=r||g||st;
        //st=OR(g,r,st);
        R=p.substr(0);
        p=desplazarDerecha(p,1,acarreo);
        //expSol=
    }
    else
    {
       int k=normalizar(p);
       if(k=0)
       {
           //st=OR(r,st);
           r=g;
       }
       else if(k>1)
       {
           r=0;
           st=0;
       }

       p=desplazarDerecha(p,k,g);

       //expSol=
    }

    //COMENZAMOS EL REDONDEO.
    if((r==1 && st==1)||(r==1 && st==0 && p.at(p.length()-1)))
    {
        string nuevaCadena=sumaBinaria(p,"1");
        int acarreo1=atoi(nuevaCadena.substr(0,1).c_str());

        p=nuevaCadena.substr(1,24);

        if(acarreo1==1)
        {
            p=desplazarDerecha(p,1,acarreo1);
            //No se si la variable es esta.
            //expSol=
        }
    }


}

string alu::complemento2(string mantisa)
{
    string mantisaNueva;
    int i;
    bool cambio=false;

    for(i=mantisa.size();i=0;i--)
    {
        if(cambio==false)
        {
            if(mantisa.at(i)==1)
            {
                mantisaNueva='1'+mantisaNueva;
                cambio=true;
            }
            else if(mantisa.at(i)==0)
            {
               mantisaNueva='0'+mantisaNueva;
            }
        }
        else
        {
            if(mantisa.at(i)==1)
            {
                mantisaNueva='0'+mantisaNueva;
            }
            else if(mantisa.at(i)==0)
            {
                mantisaNueva='1'+mantisaNueva;
            }
        }
    }
    return mantisaNueva;
}

string alu::desplazarDerecha(string mantisa, int posiciones, int digito)
{
    //No tengo ni idea de lo que es.
    std:bitset<24> mantisaNueva{mantisa};
    int i, j;
    /*
    for(i=0;i<posiciones;i++)
    {
        for(j=mantisa.size();j>0;j++)
        {
            if(j==0)
            {
                mantisa[j]=digito;
            }
            else
            {
                mantisa[j]=mantisa[j-1];
            }
        }
    }
    */

    for(i=0;i<posiciones;i++)
    {
        for(j=mantisaNueva.size();j>=0;j++)
        {
            if(j==0)
            {
                mantisaNueva[j]=digito;
            }
            else
            {
                mantisaNueva[j]=mantisaNueva[j-1];
            }
        }
    }
    //No tengo ni idea de lo que es.
    std::string nuevaCadena=mantisaNueva.to_string<char, std::char_traits<char>, std::allocator<char> >();
}

int alu::OR(string mantisa)
{
    int i, contador0=0, contador1=0;

    if(mantisa.length()==1)
    {
        return atoi(mantisa.c_str());
    }
    else
    {
        for(i=0;i<mantisa.size();i++)
        {
            if(mantisa[i]=='1')
            {
                contador0=contador0+1;
            }
            else
            {
                contador1=contador1+1;
            }
        }

        if(contador0!=mantisa.size())
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

string alu::sumaBinaria(string parametro1, string parametro2)
{
    int i, anadir, acarreo;
    string nuevaCadena;

    if(parametro1.length()<parametro2.length())
    {
        anadir=parametro1.length()-parametro2.length();
        for(i=0;i<anadir;i++)
        {
            parametro1='0'+parametro1;
        }
    }

    if(parametro2.length()<parametro2.length())
    {
        anadir=parametro2.length()-parametro1.length();
        for(i=0;i<anadir;i++)
        {
            parametro2='0'+parametro2;
        }
    }

    for(i=parametro1.length();i>=0;i--)
    {
        //No tengo ni idea de lo que es esto.
        int aux=(parametro1.at(i)-48)+(parametro2.at(i)-48);

        if(aux+acarreo==0){
            nuevaCadena="0"+ nuevaCadena;
            acarreo=0;
        }
        else if(aux+acarreo==1){
            nuevaCadena="1"+nuevaCadena;
            acarreo=0;
        }
        else if(aux+acarreo==2){
            nuevaCadena="0"+nuevaCadena;
            acarreo=1;
        }
        else{
            nuevaCadena="1"+nuevaCadena;
            acarreo=1;
        }
    }

    nuevaCadena=std::to_string(acarreo)+" "+nuevaCadena;
    return nuevaCadena;
}

int alu::normalizar(string parametro)
{
    int i, contador;
    for(i=0;i<parametro.length();i++)
    {
        if(parametro.at(i)=='1')
        {
            //No creo que esté bien.
            contador=i;
        }
    }
    return contador;
}
