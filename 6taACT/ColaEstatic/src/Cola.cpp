#include "Cola.h"

persona::persona(){
    nombre="juanito";
    edad=13;
}

persona::persona(std::string n, int e): nombre(n), edad(e) {}
void persona::operator=(persona& x)
{
    nombre=x.nombre;
    edad=x.edad;
}

std::ostream& operator<<( std::ostream& o, persona& p)
{
    o<<"nombre: "<<p.nombre<<"\t edad: "<<p.edad<<std::endl;
    return o;
}
std::istream& operator>>( std::istream& o, persona& p)
{
    std::cout<<"\n inserta nombre: ";
    o>>p.nombre;
    std::cout<<"\n inserta edad: ";
    std::cin.ignore();
    o>>p.edad;
    return o;
}

bool Cola::vacia()const
{
    if(ult==-1)
        return true;
    return false;
}
bool Cola::llena()const
{
    if(ult==TAM-1)
        return true;
    return false;
}

int Cola::ultimo()const
{
    return ult;
}

std::ostream& operator<<(std::ostream & o, Cola& L)
{
    int i=0;
    std::cout<<"\n";
    while(i<=L.ultimo())
    {
        ;
        o<<L.datos[i];
        i++;
    }
    return o;
}

void Cola::enqueue(persona& elem)
{
    inserta(elem,0);
}

persona& Cola::dequeue()
{
    if(vacia()){
        std::cout<<"\n La cola esta vacia"<<std::endl;
    }
    else{
        ult--;
        return datos[ult+1];
    }
}

bool Cola::elimina(int pos)
{
    if(vacia() || pos<0 || pos>ult)
    {
        std::cout<<"\n error de eliminacion";
        return true;
    }
    int i=pos;
    while(i<ult)
    {
        datos[i]=datos[i+1];
        i++;
    }
    ult--;
    return false;
}
int Cola::inserta(persona& elem, int pos)
{
    if(llena()|| pos<0 || pos>ult+1)
    {
        std::cout<<"\n Error de insercion";
        return 0;
    }
    int i=ult+1;
    while(i>pos)
    {
        datos[i]=datos[i-1];
        i--;
    }
    datos[pos]=elem;
    ult++;
    return 1;
}

 int Cola::busquedaLineal(persona& elem){
    if(vacia()){
        return -1;
    }
    for(int i=0; i<=ult; i++){
        if(elem==datos[i]){
            return i;
        }
    }
    return -1;
 }
