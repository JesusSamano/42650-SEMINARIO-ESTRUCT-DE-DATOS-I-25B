#include <iostream>
#include <string>
#include <limits>

// --- CLASE SOCIOCLUB ---
class SocioClub {
private:
    int NumeroSocio;
    std::string NombreSocio;
    std::string Domicilio;
    int AnioIngreso;

public:
    //constructor
    SocioClub() : NumeroSocio(0), NombreSocio(""), Domicilio(""), AnioIngreso(0) {}
    SocioClub(int ns, const std::string& n, const std::string& d, int a)
        : NumeroSocio(ns), NombreSocio(n), Domicilio(d), AnioIngreso(a) {}

    // metodos de acceso
    int getNumeroSocio() const { return NumeroSocio; }
    std::string getNombreSocio() const { return NombreSocio; }
    std::string getDomicilio() const { return Domicilio; }
    void setNumeroSocio(int ns) { NumeroSocio = ns; }

    //sobrecarga de operador == y !=
    bool operator==(const SocioClub& otro) const {
        return NumeroSocio == otro.NumeroSocio;
    }
    bool operator!=(const SocioClub& otro) const {
        return !(*this == otro);
    }
    //DISEÑO PARA IMPRIMIR
    friend std::ostream& operator<<(std::ostream& os, const SocioClub& socio) {
        os << "No. de socio " << socio.NumeroSocio
           << " | Nombre: " << socio.NombreSocio
           << " | Domicilio: " << socio.Domicilio
           << " | Ingreso: " << socio.AnioIngreso;
        return os;
    }
};

//PLANTILLA

template<class T>
class LDLLSE;

template<class T> //CLASS DE NODO
class nodo{
private:
    T data;
    nodo<T>* sig; //puntero al sig nodo
    nodo<T>* ant; //puntero al ante nodo
public:
    nodo():sig(nullptr), ant(nullptr){};
    nodo(const T& d) : data(d), sig(nullptr), ant(nullptr) {}
    friend class LDLLSE<T>;
};

template<class T> //CLASS DE LSLLSE
class LDLLSE{
private:
    nodo<T>* ancla;
public:
    LDLLSE(): ancla(nullptr){};
    ~LDLLSE() { anula(); }
    bool vacia()const;
    nodo<T>* primero()const;
    nodo<T>* ultimo()const;
    nodo<T>* anterior(nodo<T>*)const;
    nodo<T>* siguiente(nodo<T>* )const;
    nodo<T>* localiza(T)const;
    T recupera(nodo<T>* )const;
    void imprime()const;
    void anula();
    void inserta(nodo<T>* pos);
    void elimina(nodo<T>* pos);
};

// --- IMPLEMENTACIÓN DE MÉTODOS REQUERIDOS ---

template<class T>
void LDLLSE<T>::inserta(nodo<T>* pos){   //INSERTAR
    if (ancla != nullptr) {
        ancla->ant = pos;
    }
    pos->sig = ancla;
    pos->ant = nullptr;
    ancla = pos;
}

template<class T>
void LDLLSE<T>::elimina(nodo<T>* pos){ //ELIMINA
    if (pos == nullptr || vacia()) {
        return;
    }

    if (pos->ant != nullptr) {
        pos->ant->sig = pos->sig;
    } else {
        ancla = pos->sig;
    }

    if (pos->sig != nullptr) {
        pos->sig->ant = pos->ant;
    }

    delete pos;
}

// --- IMPLEMENTACIÓN DE OTROS MÉTODOS ORIGINALES ---

template<class T>
nodo<T>* LDLLSE<T>::primero()const{
    return ancla;
}

template<class T>
nodo<T>* LDLLSE<T>::ultimo()const{
    if(vacia()){
        return ancla;
    }
    else{
        nodo<T>* aux=ancla;
        while(aux->sig!=nullptr){
            aux=aux->sig;
        }
        return aux;
    }
}

template<class T>
nodo<T>* LDLLSE<T>::anterior(nodo<T>* pos)const{
    if(vacia()|| pos==nullptr){
        return nullptr;
    }
    else{
        return pos->ant;
    }
}

template<class T>
nodo<T>* LDLLSE<T>::siguiente(nodo<T>* pos)const{
    if(vacia()|| pos==nullptr){
        return nullptr;
    }
    else{
        return pos->sig;
    }
}

template<class T>
nodo<T>* LDLLSE<T>::localiza(T elem)const{ //LOCALIZA
    nodo<T>* aux=ancla;
    while(aux!=nullptr && aux->data!=elem){
        aux=aux->sig;
    }
    return aux;
}

template<class T>
T LDLLSE<T>::recupera(nodo<T>* pos)const{
    if(vacia()|| pos==nullptr){
        return T();
    }
    else{
        return pos->data;
    }
}

template<class T>
bool LDLLSE<T>::vacia()const{
    if(ancla==nullptr){
        return true;
    }
    return false;
}

template<class T>
void LDLLSE<T>::imprime()const{
    if(!vacia()){
        nodo<T>* aux=ancla;
        while(aux!=nullptr){
            std::cout<<aux->data<<std::endl;
            aux=aux->sig;
        }
    } else {
        std::cout << "Lista SIN socios.\n";
    }
}

template<class T>
void LDLLSE<T>::anula(){
    nodo<T>* aux;
    while(ancla!=nullptr){
        aux=ancla;
        ancla=aux->sig;
        delete aux;
    }
}


void limpiarBuffer() { // --- funcion para limpiar bufer ---
    if (std::cin.fail()) {
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}




// --- MENU ---
int main()
{
    LDLLSE<SocioClub> listaSocios;
    int opcion;

    do {

        std::cout << "\nCLUB DE SOCIOS BIEN 0.4\n";
        std::cout << "1. Registrar nuevo socio\n";
        std::cout << "2. Dar de baja socio\n";
        std::cout << "3. Generar un reporte con los datos de todos los socios\n"; // Requisito
        std::cout << "4. Buscar socio (Nombre/Domicilio)\n"; // Requisito
        std::cout << "5. Imprimir los socios registrados\n"; // Requisito
        std::cout << "0. Salir\n";
        std::cout << "Selecciones opcion: ";

        std::cin >> opcion;
        limpiarBuffer();

        switch(opcion) {
            case 1: { // Registrar un nuevo socio
                int num, anio;
                std::string nombre, dom;

                std::cout << "No. de Socio: ";
                if (!(std::cin >> num)) { std::cout << "Entrada invalida.\n"; limpiarBuffer(); break; }
                limpiarBuffer();

                SocioClub tempSocio; tempSocio.setNumeroSocio(num);
                if (listaSocios.localiza(tempSocio) != nullptr) {
                    std::cout << "Error: Socio con numero " << num << " ya existe.\n";
                    break;
                }

                std::cout << "Nombre del Socio: ";
                std::getline(std::cin, nombre);
                std::cout << "Domicilio: ";
                std::getline(std::cin, dom);
                std::cout << "Anio de Ingreso (int): ";
                if (!(std::cin >> anio)) { std::cout << "Entrada invalida.\n"; limpiarBuffer(); break; }

                listaSocios.inserta(new nodo<SocioClub>(SocioClub(num, nombre, dom, anio)));
                std::cout << "Socio registrado con exito.\n";
                break;
            }
            case 2: { // Dar de baja un socio del club
                int num;
                std::cout << "Numero de Socio a eliminar: ";
                if (!(std::cin >> num)) { std::cout << "Entrada invalida.\n"; limpiarBuffer(); break; }

                SocioClub socioBuscar;
                socioBuscar.setNumeroSocio(num);
                nodo<SocioClub>* pos = listaSocios.localiza(socioBuscar);

                if (pos != nullptr) {
                    listaSocios.elimina(pos);
                    std::cout << "No. de socio" << num << " eliminado.\n";
                } else {
                    std::cout << "Error: Socio con número " << num << " no encontrado.\n";
                }
                break;
            }
            case 3: { // Generar un reporte con los datos de todos los socios (Separado del caso 5)
                std::cout << "\n--- REPORTE COMPLETO DE SOCIOS ---\n";
                listaSocios.imprime();
                break;
            }
            case 5: { // Imprimir los socios registrados (Separado del caso 3)
                std::cout << "\n--- LISTA DE SOCIOS REGISTRADOS ---\n";
                listaSocios.imprime();
                break;
            }
            case 4: { // Buscar por nombre y domicilio a un socio del club
                std::string nombre, domicilio;
                std::cout << "Buscar por Nombre (parcial permitido): ";
                std::getline(std::cin, nombre);
                std::cout << "Buscar por Domicilio (parcial permitido): ";
                std::getline(std::cin, domicilio);

                nodo<SocioClub>* aux = listaSocios.primero();
                bool encontrado = false;
                std::cout << "\n--- Resultados de Busqueda ---\n";
                while (aux != nullptr) {
                    SocioClub socio = listaSocios.recupera(aux);

                    bool matchNombre = nombre.empty() || socio.getNombreSocio().find(nombre) != std::string::npos;
                    bool matchDomicilio = domicilio.empty() || socio.getDomicilio().find(domicilio) != std::string::npos;

                    if (matchNombre && matchDomicilio) {
                        std::cout << socio << std::endl;
                        encontrado = true;
                    }
                    aux = listaSocios.siguiente(aux);
                }
                if (!encontrado) {
                    std::cout << "No se encontraron socios que coincidan.\n";
                }
                break;
            }
            case 0:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);

    return 0;
}
