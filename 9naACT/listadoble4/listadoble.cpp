#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// CLASE SOCIOCLUB
class SocioClub {
private:
    int numeroSocio;
    string nombreSocio;
    string domicilio;
    int anioIngreso;

public:
    // Constructores
    SocioClub() : numeroSocio(0), nombreSocio(""), domicilio(""), anioIngreso(0) {}
    SocioClub(int num, string nom, string dom, int anio)
        : numeroSocio(num), nombreSocio(nom), domicilio(dom), anioIngreso(anio) {}

    // Getters (Métodos de Acceso)
    int getNumeroSocio() const { return numeroSocio; }
    string getNombre() const { return nombreSocio; }
    string getDomicilio() const { return domicilio; }

    // Sobrecarga de operadores
    bool operator==(const SocioClub& otro) const {
        return numeroSocio == otro.numeroSocio;
    }

    bool operator<(const SocioClub& otro) const {
        return numeroSocio < otro.numeroSocio;
    }

    // Operador de impresión (Friend para acceder a miembros privados)
    friend ostream& operator<<(ostream& os, const SocioClub& s) {
        os << "\n*** DATOS DE SOCIO ***"
           << "\nNúmero de Socio: " << s.numeroSocio
           << "\nNombre: " << s.nombreSocio
           << "\nDomicilio: " << s.domicilio
           << "\nAño de Ingreso: " << s.anioIngreso << "\n";
        return os;
    }
};

// Declaración forward de LDLLSE
template<class T>
class LDLLSE;

// CLASE NODO (DOBLEMENTE LIGADA)
template<class T>
class nodo {
private:
    T data;
    nodo<T>* sig;
    nodo<T>* ant;
public:
    nodo() : sig(nullptr), ant(nullptr) {};
    friend class LDLLSE<T>;
};

// CLASE LDLLSE (Lista Doblemente Ligada)
template<class T>
class LDLLSE {
private:
    nodo<T>* ancla;

    // Métodos privados de soporte para la lógica de negocio
    nodo<T>* buscarPorNumero(int num) const;
    nodo<T>* buscarPorNombreYDom(string nombre, string dom) const;
    // Hacemos 'imprime' privado para forzar el uso de 'generarReporte'
    void imprime() const;

public:
    LDLLSE() : ancla(nullptr) {};
    ~LDLLSE(){ anula(); }

    // Funciones básicas de la lista
    bool vacia() const;
    nodo<T>* primero() const;
    nodo<T>* anterior(nodo<T>* pos) const;
    nodo<T>* siguiente(nodo<T>* pos) const;
    void anula();
    void inserta(nodo<T>* pos, T elem);
    void elimina(nodo<T>* pos);

    // Métodos de la lógica de negocio (Interfaz Pública)
    bool existeSocio(int num) const;
    bool eliminarSocioPorNumero(int num);
    void generarReporte() const; // Este método usa el privado imprime()
    bool imprimirSocioPorNombreYDom(string nombre, string dom) const;
    void insertarOrdenado(T elem);
    int totalSocios() const;
};

// IMPLEMENTACIÓN DE MÉTODOS DE LDLLSE

template<class T>
void LDLLSE<T>::inserta(nodo<T>* pos, T elem) {
    nodo<T>* nuevo = new nodo<T>;
    nuevo->data = elem;

    if (pos == nullptr) {
        if (ancla == nullptr) {
            ancla = nuevo;
        } else {
            nuevo->sig = ancla;
            ancla->ant = nuevo;
            ancla = nuevo;
        }
    } else {
        nuevo->sig = pos->sig;
        nuevo->ant = pos;
        if (pos->sig != nullptr) {
            pos->sig->ant = nuevo;
        }
        pos->sig = nuevo;
    }
}

template<class T>
void LDLLSE<T>::elimina(nodo<T>* pos) {
    if (vacia() || pos == nullptr) {
        return;
    }

    if (pos == ancla) {
        ancla = pos->sig;
        if (ancla != nullptr) {
            ancla->ant = nullptr;
        }
    } else {
        pos->ant->sig = pos->sig;
        if (pos->sig != nullptr) {
            pos->sig->ant = pos->ant;
        }
    }
    delete pos;
}

// Implementación de LDLLSE<T>::imprime() (Mantenida como PRIVADA)
template<class T>
void LDLLSE<T>::imprime() const {
    nodo<T>* aux = ancla;
    if (vacia()) {
        cout << "Lista de socios vacía." << endl;
        return;
    }
    while (aux != nullptr) {
        cout << aux->data; // Usa el operador << de SocioClub (acceso controlado)
        aux = aux->sig;
    }
}

// Implementación de Lógica de Negocio

template<class T>
void LDLLSE<T>::insertarOrdenado(T elem) {
    nodo<T>* aux = primero();
    nodo<T>* posAnterior = nullptr;

    while (aux != nullptr && aux->data < elem) {
        posAnterior = aux;
        aux = siguiente(aux);
    }
    inserta(posAnterior, elem);
}

template<class T>
nodo<T>* LDLLSE<T>::buscarPorNumero(int num) const {
    nodo<T>* aux = ancla;
    while (aux != nullptr) {
        if (aux->data.getNumeroSocio() == num) {
            return aux;
        }
        aux = aux->sig;
    }
    return nullptr;
}

template<class T>
bool LDLLSE<T>::existeSocio(int num) const {
    return buscarPorNumero(num) != nullptr;
}

template<class T>
bool LDLLSE<T>::eliminarSocioPorNumero(int num) {
    nodo<T>* pos = buscarPorNumero(num);
    if (pos) {
        elimina(pos);
        return true;
    }
    return false;
}

// Implementación de LDLLSE<T>::generarReporte() (PÚBLICA)
template<class T>
void LDLLSE<T>::generarReporte() const {
    cout << "\n--- REPORTE COMPLETO DE SOCIOS ---\n";
    imprime(); // Llama al método privado de recorrido
    cout << "------------------------------------\n";
}

template<class T>
nodo<T>* LDLLSE<T>::buscarPorNombreYDom(string nombre, string dom) const {
    nodo<T>* aux = ancla;
    while (aux != nullptr) {
        if (aux->data.getNombre() == nombre && aux->data.getDomicilio() == dom)
            return aux;
        aux = aux->sig;
    }
    return nullptr;
}

template<class T>
bool LDLLSE<T>::imprimirSocioPorNombreYDom(string nombre, string dom) const {
    nodo<T>* pos = buscarPorNombreYDom(nombre, dom);
    if (pos) {
        cout << "\n--- RESULTADO DE BÚSQUEDA ---\n";
        cout << pos->data;
        cout << "-------------------------------\n";
        return true;
    }
    return false;
}

template<class T>
int LDLLSE<T>::totalSocios() const {
    int c = 0;
    nodo<T>* aux = ancla;
    while (aux != nullptr) {
        c++;
        aux = aux->sig;
    }
    return c;
}

// ... (Implementación de primero, anterior, siguiente, anula, vacia, etc.)
template<class T> nodo<T>* LDLLSE<T>::primero() const { return ancla; }
template<class T> nodo<T>* LDLLSE<T>::anterior(nodo<T>* pos) const {
    if (vacia() || pos == nullptr || pos == ancla) return nullptr;
    return pos->ant;
}
template<class T> nodo<T>* LDLLSE<T>::siguiente(nodo<T>* pos) const {
    if (vacia() || pos == nullptr) return nullptr;
    return pos->sig;
}
template<class T> void LDLLSE<T>::anula() {
    nodo<T>* aux;
    while (ancla != nullptr) {
        aux = ancla;
        ancla = aux->sig;
        delete aux;
    }
}
template<class T> bool LDLLSE<T>::vacia() const { return ancla == nullptr; }


// main
int main() {
    LDLLSE<SocioClub> lista;
    int opcion;

    do {
        // MENÚ
        cout << "\n=====================================" << endl;
        cout << "  MENÚ DEL CLUB DEPORTIVO (LDLLSE)" << endl;
        cout << "=====================================" << endl;
        cout << "1. Registrar un nuevo socio" << endl;
        cout << "2. Dar de baja un socio del club" << endl;
        cout << "3. Generar un reporte con los datos de todos los socios" << endl; // Usa generarReporte()
        cout << "4. Buscar por nombre y domicilio a un socio del club" << endl;
        cout << "5. Imprimir los socios registrados" << endl; // Redirigido a generarReporte()
        cout << "6. Total de socios registrados" << endl;
        cout << "0. Salir" << endl;
        cout << "=====================================" << endl;
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            cin.clear();
            limpiarBuffer();
            opcion = -1;
            cout << "Entrada inválida. Intente de nuevo.\n";
            continue;
        }

        // LÓGICA DE OPERACIONES
        if (opcion == 1) { // Registrar un nuevo socio
            int num, anio;
            string nombre, dom;

            cout << "\n--- REGISTRAR NUEVO SOCIO ---" << endl;
            cout << "Número de socio: ";
            if (!(cin >> num)) {
                cout << "Error en el número de socio. Cancelando registro.\n";
                cin.clear();
                limpiarBuffer();
                continue;
            }
            limpiarBuffer();

            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Domicilio: ";
            getline(cin, dom);

            cout << "Año de ingreso: ";
            if (!(cin >> anio)) {
                cout << "Error en el año de ingreso. Cancelando registro.\n";
                cin.clear();
                limpiarBuffer();
                continue;
            }
            limpiarBuffer();

            SocioClub s(num, nombre, dom, anio);

            if (lista.existeSocio(num)) {
                cout << "ERROR: Ya existe un socio con el número " << num << ". No puede haber dos socios con el mismo número.\n";
            } else {
                lista.insertarOrdenado(s);
                cout << "Socio registrado correctamente.\n";
            }

        } else if (opcion == 2) { // Dar de baja un socio del club
            int num;
            cout << "\n--- DAR DE BAJA SOCIO ---" << endl;
            cout << "Ingrese número de socio a eliminar: ";
            if (!(cin >> num)) {
                cout << "Error en el número de socio.\n";
                cin.clear();
                limpiarBuffer();
                continue;
            }
            limpiarBuffer();

            if (lista.eliminarSocioPorNumero(num))
                cout << "Socio con número " << num << " dado de baja con éxito.\n";
            else
                cout << "ERROR: No se encontro socio con el numero " << num << ".\n";

        } else if (opcion == 3 || opcion == 5) { // Generar reporte e Imprimir socios
            lista.generarReporte();

        } else if (opcion == 4) { // Buscar por nombre y domicilio a un socio del club
            string nombre, dom;
            cout << "\n--- BUSCAR SOCIO POR NOMBRE Y DOMICILIO ---" << endl;
            limpiarBuffer();
            cout << "Nombre: ";
            getline(cin, nombre);
            cout << "Domicilio: ";
            getline(cin, dom);

            if (!lista.imprimirSocioPorNombreYDom(nombre, dom))
                cout << "No se encontró socio con esos datos.\n";

        } else if (opcion == 6) { // Total de socios registrados
            cout << "\nTotal de socios registrados: " << lista.totalSocios() << "\n";
        }

    } while (opcion != 0);

    cout << "\nPrograma finalizado.\n";
    return 0;
}
