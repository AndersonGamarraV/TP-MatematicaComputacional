#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include"InfInt.h"
/*
    Estamos usando una libreria de GitHub para poder obtener una clase
    llamada InfInt ya que esta clase no ayudara a almacenar enteros con 
    mayor tamaño. Los long int no tiene el espacio suficiente para poder
    almacenar los primos que necesitamos.
*/
using namespace std;
/*
    La estructura RSAFUNCIONES sera con funciones staticas 
    porque no necesitaremos crear objetos, solo usar sus funciones
*/
struct RSAFUNCIONES{
    static void Generar(){
        InfInt primo1,primo2,n,fi,cpublica,cprivada;
        cout<<"Escribe el primer numero primo";cin>>primo1;
        cout<<"Escribre el segundo numero primo";cin>>primo2;

    }
    static vector<InfInt> Encriptar(string mensaje,InfInt modulo,InfInt e){

    }
    static string Desencriptar(string mensaje,InfInt modulo,InfInt e){

    }
};

int main(){
    //MENU DE OPCIONES
    while (true)
    {
        unsigned short opcion;
        cout<<"1.-Generar Claves\n2.-Encriptar\n3.-Desencriptar\n4.-Salir"<<endl;
        cout<<"¿Que quieres hacer? ";
        cin>>opcion;
        switch (opcion)
        {
        case 1: 
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            return 1;
        }
    }
    
    return 0;
}
