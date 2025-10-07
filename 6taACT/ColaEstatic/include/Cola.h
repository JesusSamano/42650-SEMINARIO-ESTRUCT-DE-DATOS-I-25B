#ifndef COLA_H
#define COLA_H
#include <iostream>
const int TAM=100;

//***************************Definicion de la clase persona*************************
//**********************************************************************************
class persona
{
private:
    std::string nombre;
    int edad;
public:
    persona();
    void operator=(persona& x);
    persona(std::string n, int e);
    friend std::ostream& operator<<( std::ostream&, persona&);
    friend std::istream& operator>>( std::istream&, persona&);
    bool operator==(persona&p){
        return p.nombre==nombre&&p.edad==edad;
    }
};
//***************************************************************************************



//****************************Definicion de la clase Pila****************************
//***********************************************************************************
class Cola
{
private:
    persona datos[TAM];
    int ult;
    bool elimina(int pos);
    int inserta(persona& elem, int pos);
public:
    Cola():ult(-1) {}
    bool vacia()const;
    bool llena()const;
    int ultimo()const;
    friend std::ostream& operator<<(std::ostream & o, Cola& L);
    void enqueue(persona& elem);
    persona& dequeue();
    int busquedaLineal(persona&);

};
//*************************************************************************************

#endif // COLA_H
