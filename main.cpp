#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include<tuple>
#include"InfInt.h"
/*
    -------------------------INFINT.H------------------------------
    Estamos usando una libreria de GitHub para poder obtener una clase
    llamada InfInt ya que esta clase no ayudara a almacenar enteros con 
    mayor tamaño. Los long int no tiene el espacio suficiente para poder
    almacenar los primos que necesitamos.
*/
using namespace std;
/*
    ------------------ALGORITMO DE EUCLIDES-----------------------
    Para poder hallar el mcd usamos el algoritmo de Euclides. Usamos el 
    paradigma de la Recursividad para poder hacerlo.
*/
InfInt Mcd(InfInt a,InfInt b){
    if(b!=0)
        return Mcd(b,a%b);
    return a;
}
/*
    --------------ALGORITMO INVERTIDO DE EUCLIDES---------------
    Para poder hallar la clave privada debemos hacer el algoritmo
    invertido de euclides.
*/
tuple<InfInt,InfInt,InfInt> Euclides(InfInt a,InfInt b){
    if(a==0)
        return make_tuple(b,0,1);
    
    InfInt mcd,x,y;
    tie(mcd,x,y)=Euclides(b%a,a);//Existe recursivdad
    return make_tuple(mcd,y-(b/a)*x,x);
}
/*
---------------------ModuloPotencia-----------------------------
Se relizara esta funcion para poder hallar la potencia de cada caracter
del mensaje elevado a la clave publica multiplicado por n que es el modulo
*/
InfInt ModuloPotencia(InfInt base,InfInt exponente,InfInt modulo){
    InfInt resultado =1;
    while (--exponente>=0)
    {
        resultado =resultado*base;
        resultado%=modulo;
    }
    return resultado;
}
/*
    -----------------RSAFUNCIONES-------------------------------
    La estructura RSAFUNCIONES sera con funciones staticas 
    porque no necesitaremos crear objetos, solo usar sus funciones
*/
struct RSAFUNCIONES{
    static void Generar(){
        InfInt primo1,primo2,n,fi,cpublica,cprivada;
        /*
            cplubica -> e
            cprivada -> d
        */
        cout<<"Escribe el primer numero primo";cin>>primo1;
        cout<<"Escribre el segundo numero primo";cin>>primo2;
        n = primo1*primo2;
        fi = (primo1-1)*(primo2-1);
        do{
            cout<<"Escribe e: ";cin>>cpublica;
        }while (!(cpublica<fi && Mcd(cpublica,fi)==1));
        cprivada=get<1>(Euclides(cpublica,fi));//Tiene una posibilidad de que salga negativo
        while (cprivada<0){//En caso sea negativo, este while seguira hasta que se haga positivo
            cprivada=cprivada+fi;
        }
        //IMPRIMIENDO LAS CLAVES
        cout<<"Modulo: "<<n<<endl;
        cout<<"Clave Publica: "<<cpublica<<endl;
        cout<<"Clave Privada: "<<cprivada<<endl;
        
    }
    static vector<InfInt> Encriptar(string mensaje,InfInt cpublica, InfInt modulo){
        vector<InfInt> resultado;
        for(auto c : mensaje){
            resultado.push_back(ModuloPotencia((int)c,cpublica,modulo));
        }
        return resultado;
    }
    static string Desencriptar(string mensaje,InfInt cprivada, InfInt modulo){
        vector<InfInt> msg;
        string resultado;
        string temporal("");
        for(auto c:mensaje){
            if(c=='-'){
                msg.push_back(temporal);//Puedes guardar string en un vector InfInt debido a que existe un constructor en la libre InfInt.h que acepta un string
                                        //Asimiso, hace el constructor hace uso de un metodo llamada fromString, que tiene como parametro un string
                temporal="";
            }
            else
                temporal=temporal+c;
        }
        if(temporal.length()>0){
            msg.push_back(temporal);
        }
        
        for(auto c : msg){
            auto numero = ModuloPotencia(c,cprivada,modulo);
            resultado = resultado+(char)(numero.toInt());
        }
        return resultado;
    }
};

int main(){
    //MENU DE OPCIONES
    while (true)
    {
        unsigned short opcion;
        cout<<"\n1.-Generar Claves\n2.-Encriptar\n3.-Desencriptar\n4.-Salir"<<endl;
        cout<<"¿Que quieres hacer? ";
        cin>>opcion;
        switch (opcion){
            case 1: {
                RSAFUNCIONES::Generar();
                break;
            }
            case 2:{
                string mensaje;
                InfInt e,n;
                cout<<"Escribe el mensaje: "; cin.ignore();
                getline(cin,mensaje);
                cout<< "Clave Publica (e): "; cin>>e;
                cout<<"Modulo (n): ";cin>>n;
                auto resultado = RSAFUNCIONES::Encriptar(mensaje,e,n);
                for(auto n : resultado){
                    cout<<n<<"-";
                }
                break;
            }
            case 3:{
                string mensaje;
                InfInt d,n;
                cout<<"Escribe el mensaje: "; cin.ignore();
                getline(cin,mensaje);
                cout<< "Clave Privada (d): "; cin>>d;
                cout<<"Modulo (n): ";cin>>n;
                auto resultado = RSAFUNCIONES::Desencriptar(mensaje,d,n);
                cout<<resultado;
                break;
            }
        default:
            break;
        }
    }
    
    return 0;
}
