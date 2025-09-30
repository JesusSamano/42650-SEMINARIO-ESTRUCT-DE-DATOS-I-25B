#include <iostream>
#include <string>
const int TAM=100;

// Clase Solicitud (alumno)
class Solicitud
{
private:
    std::string nombre;
    std::string carrera;
    int materiasAprobadas;
    float promedio;
public:
    Solicitud();
    Solicitud(std::string n, std::string c, int m, float p);
    void operator=(Solicitud& x);
    friend std::ostream& operator<<( std::ostream&, Solicitud&);
    friend std::istream& operator>>( std::istream&, Solicitud&);
};

// Constructor para pedir datos están en vacios a espera
Solicitud::Solicitud(){
    nombre="Sin nombre";
    carrera="Sin carrera";
    materiasAprobadas=0;
    promedio=0.0;
}

// Constructor con sus variables asignadas
Solicitud::Solicitud(std::string n, std::string c, int m, float p)
: nombre(n), carrera(c), materiasAprobadas(m), promedio(p) {}

void Solicitud::operator=(Solicitud& x)
{
    nombre=x.nombre;
    carrera=x.carrera;
    materiasAprobadas=x.materiasAprobadas;
    promedio=x.promedio;
}

// Sobrecarga operador <<
std::ostream& operator<<( std::ostream& o, Solicitud& s)
{
    o<<"Alumno: "<<s.nombre<<"\nCarrera: "<<s.carrera
     <<"\nMaterias aprobadas: "<<s.materiasAprobadas
     <<"\nPromedio: "<<s.promedio<<"\n";
    return o;
}

// Sobrecarga operador >>
std::istream& operator>>( std::istream& i, Solicitud& s)
{
    std::cout<<"\nNombre del alumno: ";
    std::getline(i, s.nombre);
    std::cout<<"Carrera: ";
    std::getline(i, s.carrera);
    std::cout<<"Materias aprobadas: ";
    i>>s.materiasAprobadas;
    std::cout<<"Promedio: ";
    i>>s.promedio;
    i.ignore(); // limpiar buffer
    return i;
}

//Clase Cola
class Cola
{
private:
    Solicitud datos[TAM];
    int ult;
    bool elimina(int pos);
    int inserta(Solicitud& elem, int pos);
public:
    Cola():ult(-1) {}
    bool vacia()const;
    bool llena()const;
    int ultimo()const;
    friend std::ostream& operator<<(std::ostream & o, Cola& L);
    void enqueue(Solicitud& elem);
    Solicitud& dequeue();
};

bool Cola::vacia()const
{
    return (ult==-1);
}

bool Cola::llena()const
{
    return (ult==TAM-1);
}

int Cola::ultimo()const
{
    return ult;
}

std::ostream& operator<<(std::ostream & o, Cola& L)
{
    int i=0;
    std::cout<<"\nSolicitudes en la cola:\n";
    while(i<=L.ultimo())
    {
        o<<L.datos[i]<<"\n";
        i++;
    }
    return o;
}

void Cola::enqueue(Solicitud& elem)
{
    inserta(elem,0);
}

Solicitud& Cola::dequeue()
{
    if(vacia()){
        std::cout<<"\n La cola está vacía\n";
        exit(1);
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
        std::cout<<"\n Error de eliminacion";
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

int Cola::inserta(Solicitud& elem, int pos)
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

//**************************** MAIN *****************************************
int main()
{
    Cola colaSolicitudes;
    Solicitud s;
    int opcion;

    do{
        std::cout<<"\n--- MENU ---\n";
        std::cout<<"1. Dar de alta solicitud\n";
        std::cout<<"2. Elaborar constancia\n";
        std::cout<<"3. Ver solicitudes pendientes\n";
        std::cout<<"4. Salir\n";
        std::cout<<"Opcion: ";
        std::cin>>opcion;
        std::cin.ignore(); // limpiar buffer

        switch(opcion){
            case 1:
                std::cin>>s;
                colaSolicitudes.enqueue(s);
                break;
            case 2:
                if(!colaSolicitudes.vacia()){
                    s = colaSolicitudes.dequeue();
                    std::cout<<"\nConstancia elaborada:\n"<<s;
                }else{
                    std::cout<<"\nNo hay solicitudes pendientes.\n";
                }
                break;
            case 3:
                if(!colaSolicitudes.vacia()){
                    std::cout<<colaSolicitudes;
                }else{
                    std::cout<<"\nNo hay solicitudes en la cola.\n";
                }
                break;
            case 4:
                std::cout<<"\nSaliendo...\n";
                break;
            default:
                std::cout<<"\nOpcion invalida.\n";
        }
    }while(opcion!=4);

    return 0;
}
