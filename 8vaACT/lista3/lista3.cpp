#include <iostream>
#include <string>

using namespace std;

// CLASE SOCIOCLUB
class SocioClub {
private:
    int numeroSocio;
    string nombreSocio;
    string domicilio;
    int anioIngreso;

public:
    SocioClub() : numeroSocio(0), nombreSocio(""), domicilio(""), anioIngreso(0) {}
    SocioClub(int num, string nom, string dom, int anio)
        : numeroSocio(num), nombreSocio(nom), domicilio(dom), anioIngreso(anio) {}

    // Getters públicos para que los métodos de la lista puedan buscar y comparar
    int getNumeroSocio() const { return numeroSocio; }
    string getNombre() const { return nombreSocio; }
    string getDomicilio() const { return domicilio; }

    bool operator==(const SocioClub& otro) const {
        return numeroSocio == otro.numeroSocio;
    }

    bool operator<(const SocioClub& otro) const {
        return numeroSocio < otro.numeroSocio;
    }

    // El operador friend << accede directamente a los miembros privados para la impresión
    friend ostream& operator<<(ostream& os, const SocioClub& s) {
        os << "\n*** DATOS DE SOCIO ***"
           << "\nNumero de Socio: " << s.numeroSocio
           << "\nNombre: " << s.nombreSocio
           << "\nDomicilio: " << s.domicilio
           << "\nAño de Ingreso: " << s.anioIngreso << "\n";
        return os;
    }
};

// Declaración forward de LSLSE
template<class T>
class LSLSE;

// CLASE NODE
template<class T>
class node {
private:
    T data;
    node<T>* sig;

public:
    node() : sig(nullptr) {};
    friend class LSLSE<T>;
};

// CLASE LSLSE (Lista Simplemente Ligada Simple Enlazada)
template<class T>
class LSLSE {
private:
    node<T>* lista;

    // Métodos privados (const para ser llamados por la interfaz pública)
    node<T>* buscarPorNumero(int num) const;
    node<T>* buscarPorNombreYDom(string nombre, string dom) const;
    int contarSocios() const;

public:
    LSLSE() : lista(nullptr) {};

    // Funciones básicas de la lista
    bool vacia() const;
    node<T>* ultimo() const;
    node<T>* primero() const;
    node<T>* anterior(node<T>* pos) const;
    void insertar(node<T>* pos, T elem);
    bool eliminar(node<T>* pos);
    void imprimir() const;

    // Métodos públicos para acceder a los miembros internos del nodo (necesario para main)
    T& getData(node<T>* pos) const { return pos->data; }
    node<T>* getNext(node<T>* pos) const { return pos->sig; }

    // Métodos de la lógica de negocio (interfaz pública)
    bool existeSocio(int num) const { return buscarPorNumero(num) != nullptr; }

    bool eliminarSocioPorNumero(int num) {
        node<T>* pos = buscarPorNumero(num);
        return eliminar(pos);
    }

    bool imprimirSocioPorNombreYDom(string nombre, string dom) const {
        node<T>* pos = buscarPorNombreYDom(nombre, dom);
        if (pos) {
            cout << getData(pos);
            return true;
        }
        return false;
    }

    int totalSocios() const {
        return contarSocios();
    }
};

// IMPLEMENTACIÓN DE MÉTODOS DE LSLSE
template<class T>
void LSLSE<T>::imprimir() const {
    node<T>* aux = primero();
    while (aux != nullptr) {
        // Uso de getData() para acceder al dato encapsulado
        cout << getData(aux) << "-> ";
        // Uso de getNext() para avanzar
        aux = getNext(aux);
    }
    cout << "NULL\n";
}

template<class T>
bool LSLSE<T>::eliminar(node<T>* pos) {
    if (vacia() || pos == nullptr) {
        return false;
    }
    if (pos == lista) {
        lista = pos->sig;
    } else {
        anterior(pos)->sig = pos->sig;
    }
    delete pos;
    return true;
}

template<class T>
void LSLSE<T>::insertar(node<T>* pos, T elem) {
    node<T>* aux = new node<T>;
    aux->data = elem;
    if (pos == nullptr) {
        aux->sig = lista;
        lista = aux;
    } else {
        aux->sig = pos->sig;
        pos->sig = aux;
    }
}

template<class T>
node<T>* LSLSE<T>::anterior(node<T>* pos) const {
    if (vacia() || pos == nullptr) {
        return nullptr;
    }
    node<T>* aux = lista;
    while (aux != nullptr && aux->sig != pos) {
        aux = aux->sig;
    }
    return aux;
}

template<class T>
node<T>* LSLSE<T>::primero() const {
    return vacia() ? nullptr : lista;
}

template<class T>
node<T>* LSLSE<T>::ultimo() const {
    if (vacia()) return nullptr;
    node<T>* aux = lista;
    while (aux->sig != nullptr) {
        aux = aux->sig;
    }
    return aux;
}

template<class T>
bool LSLSE<T>::vacia() const {
    return lista == nullptr;
}

// Métodos privados (const)
template<class T>
node<T>* LSLSE<T>::buscarPorNumero(int num) const {
    node<T>* aux = lista;
    while (aux != nullptr) {
        if (aux->data.getNumeroSocio() == num)
            return aux;
        aux = aux->sig;
    }
    return nullptr;
}

template<class T>
node<T>* LSLSE<T>::buscarPorNombreYDom(string nombre, string dom) const {
    node<T>* aux = lista;
    while (aux != nullptr) {
        if (aux->data.getNombre() == nombre && aux->data.getDomicilio() == dom)
            return aux;
        aux = aux->sig;
    }
    return nullptr;
}

template<class T>
int LSLSE<T>::contarSocios() const {
    int c = 0;
    node<T>* aux = lista;
    while (aux != nullptr) {
        c++;
        aux = aux->sig;
    }
    return c;
}

// main
int main() {
    LSLSE<SocioClub> lista;
    int opcion;

    do {
        cout << "\n=-= SOCIOS DE CLUB =-=\n";
        cout << "1. Registrar nuevo socio\n";
        cout << "2. Dar de baja un socio\n";
        cout << "3. Generar reporte de socios\n";
        cout << "4. Buscar socio (nombre y domicilio)\n";
        cout << "5. Total de socios registrados\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            // Manejo de error de entrada simple
            cin.clear();
            cin.ignore(256, '\n');
            opcion = -1;
            cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }

        if (opcion == 1) {
            int num, anio;
            string nombre, dom;

            cout << "Numero de socio: ";
            cin >> num;
            cin.ignore();
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Domicilio: ";
            getline(cin, dom);
            cout << "Anio de ingreso: ";
            cin >> anio;

            SocioClub s(num, nombre, dom, anio);

            if (lista.existeSocio(num)) {
                cout << "Ya existe un socio con ese numero.\n";
            } else {
                node<SocioClub>* aux = lista.primero();
                node<SocioClub>* posAnterior = nullptr;

                // Lógica de inserción ordenada usando getData() y getNext()
                while (aux != nullptr && lista.getData(aux) < s) {
                    posAnterior = aux;
                    aux = lista.getNext(aux);
                }

                lista.insertar(posAnterior, s);
                cout << "Socio registrado correctamente.\n";
            }

        } else if (opcion == 2) {
            int num;
            cout << "Ingrese numero de socio a eliminar: ";
            cin >> num;

            if (lista.eliminarSocioPorNumero(num))
                cout << "Socio eliminado.\n";
            else
                cout << "No se encontro socio.\n";

        } else if (opcion == 3) {
            cout << "\n--- REPORTE DE SOCIOS ---\n";
            lista.imprimir();
            cout << "---------------------------\n";

        } else if (opcion == 4) {
            string nombre, dom;
            cin.ignore();
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Domicilio: ";
            getline(cin, dom);

            cout << "\n--- RESULTADO DE BUSQUEDA ---\n";
            if (!lista.imprimirSocioPorNombreYDom(nombre, dom))
                cout << "No se encontro socio.\n";
            cout << "-------------------------------\n";


        } else if (opcion == 5) {
            cout << "Total de socios registrados: " << lista.totalSocios() << "\n";
        }

    } while (opcion != 0);

    cout << "\nPrograma finalizado.\n";
    return 0;
}
