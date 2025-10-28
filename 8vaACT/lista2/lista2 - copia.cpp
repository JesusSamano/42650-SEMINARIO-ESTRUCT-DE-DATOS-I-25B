#include <iostream>
#include <string>
using namespace std;

template<class T>
class LSLSE;

template<class T>
class node {
private:
    T data;
    node<T>* sig; // Apunta al siguiente nodo

public:
    node() : sig(nullptr) {};
    friend class LSLSE<T>;
};

template<class T>
class LSLSE {
private:
    node<T>* lista; // puntero al primer nodo

    // Métodos privados
    node<T>* buscarPorNumero(int num) const;
    node<T>* buscarPorNombreYDom(string nombre, string dom) const;
    int contarSocios() const;

public:
    LSLSE() : lista(nullptr) {}; // Constructor para lista vacía
    bool vacia() const;
    node<T>* ultimo() const;
    node<T>* primero() const;
    node<T>* anterior(node<T>* pos) const;
    void insertar(node<T>* pos, T elem);
    bool eliminar(node<T>* pos);
    void imprimir() const;

    T& getData(node<T>* pos) const { return pos->data; }
    node<T>* getNext(node<T>* pos) const { return pos->sig; }

    // Métodos públicos para acceder a la funcionalidad privada
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

template<class T>
void LSLSE<T>::imprimir() const {
    node<T>* aux = lista;
    while (aux != nullptr) {
        cout << aux->data << "-> ";
        aux = aux->sig;
    }
}

template<class T>
bool LSLSE<T>::eliminar(node<T>* pos) {
    if (vacia() || pos == nullptr) {
        return false;
    }
    if (pos == lista) {
        lista = lista->sig;
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

// Métodos privados
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

// Clase SocioClub
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

    int getNumeroSocio() const { return numeroSocio; }
    string getNombre() const { return nombreSocio; }
    string getDomicilio() const { return domicilio; }
    int getAnioIngreso() const { return anioIngreso; }

    bool operator==(const SocioClub& otro) const {
        return numeroSocio == otro.numeroSocio;
    }

    bool operator<(const SocioClub& otro) const {
        return numeroSocio < otro.numeroSocio;
    }

    friend ostream& operator<<(ostream& os, const SocioClub& s) {
        os << "\nNumero de Socio: " << s.numeroSocio
           << "\nNombre: " << s.nombreSocio
           << "\nDomicilio: " << s.domicilio
           << "\nAño de Ingreso: " << s.anioIngreso << "\n";
        return os;
    }
};

// Función principal
int main() {
    LSLSE<SocioClub> lista;
    int opcion;

    do {
        cout << "\nSOCIOS DE CLUB =-)\n";
        cout << "1. Registrar nuevo socio\n";
        cout << "2. Dar de baja un socio\n";
        cout << "3. Generar reporte de socios\n";
        cout << "4. Buscar socio (nombre y domicilio)\n";
        cout << "5. Total de socios registrados\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

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
            lista.imprimir();

        } else if (opcion == 4) {
            string nombre, dom;
            cin.ignore();
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Domicilio: ";
            getline(cin, dom);

            if (!lista.imprimirSocioPorNombreYDom(nombre, dom))
                cout << "No se encontro socio.\n";

        } else if (opcion == 5) {
            cout << "Total de socios registrados: " << lista.totalSocios() << "\n";
        }

    } while (opcion != 0);

    cout << "\nPrograma finalizado.\n";
    return 0;
}
