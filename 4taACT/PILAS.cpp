#include <iostream>
#include <string>
using namespace std;

#define TAM 50

// --------------------- CLASE EMPLEADO ---------------------
class Empleado {
private:
    int claveEmpleado;
    string nombre;
    string domicilio;
    float sueldo;
    string reportaA;

public:
    // Constructor
    Empleado(int clave = 0, string nom = "", string dom = "", float sue = 0.0, string jefe = "")
        : claveEmpleado(clave), nombre(nom), domicilio(dom), sueldo(sue), reportaA(jefe) {}

    // Sobrecarga de entrada
    friend istream& operator>>(istream& i, Empleado& e) {
        cout << "Clave: ";
        i >> e.claveEmpleado;
        i.ignore();
        cout << "Nombre: ";
        getline(i, e.nombre);
        cout << "Domicilio: ";
        getline(i, e.domicilio);
        cout << "Sueldo: ";
        i >> e.sueldo;
        i.ignore();
        cout << "Reporta a: ";
        getline(i, e.reportaA);
        return i;
    }

    // Sobrecarga de salida
    friend ostream& operator<<(ostream& o, const Empleado& e) {
        o << "Clave: " << e.claveEmpleado << "\n";
        o << "Nombre: " << e.nombre << "\n";
        o << "Domicilio: " << e.domicilio << "\n";
        o << "Sueldo: $" << e.sueldo << "\n";
        o << "Reporta a: " << e.reportaA << "\n";
        return o;
    }
};

// CLASE PILA
template <class T>
class Pila {
private:
    T datos[TAM]; // arreglo fijo
    int tope; // índice del último elemento

public:
    Pila() : tope(-1) {}

    bool vacia() const { return tope == -1; }
    bool llena() const { return tope == TAM - 1; }

    bool push(const T& elem) {
        if (llena()) {
            cout << "La pila esta llena.\n";
            return false;
        }
        datos[++tope] = elem;
        return true;
    }



    bool pop() {
        if (vacia()) {
            cout << "La pila esta vacia.\n";
            return false;
        }
        tope--;
        return true;
    }

    T top() const {
        if (vacia()) {
            cout << "La pila esta vacia.\n";
            return T(); // regresa objeto por defecto
        }
        return datos[tope];
    }
};

// MAIN
int main() {
    Pila<Empleado> pila;
    int opcion;

    do {
        cout << "\n--- MENU PILA DE EMPLEADOS ---\n";
        cout << "1. Push (apilar empleado)\n";
        cout << "2. Pop (desapilar empleado)\n";
        cout << "3. Top (mostrar cima)\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            if (pila.llena()) {
                cout << "La pila esta llena.\n";
            } else {
                Empleado e;
                cin.ignore();
                cin >> e;
                pila.push(e);
            }
            break;
        }
        case 2:
            pila.pop();
            break;
        case 3: {
            Empleado e = pila.top();
            if (!pila.vacia())
                cout << "--- Empleado en la cima ---\n" << e;
            break;
        }
        case 4:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);

    return 0;
}
