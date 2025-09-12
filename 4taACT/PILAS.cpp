#include <iostream>
#include <string>
using namespace std;

const int MAX = 100; // capacidad máxima de la pila

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

    int getClave() const { return claveEmpleado; }
    string getNombre() const { return nombre; }

    // Sobrecarga de entrada y salida
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

    friend ostream& operator<<(ostream& o, const Empleado& e) {
        o << "Clave: " << e.claveEmpleado << "\n";
        o << "Nombre: " << e.nombre << "\n";
        o << "Domicilio: " << e.domicilio << "\n";
        o << "Sueldo: $" << e.sueldo << "\n";
        o << "Reporta a: " << e.reportaA << "\n";
        return o;
    }
};

// --------------------- CLASE PILA ---------------------
class Pila {
private:
    Empleado datos[MAX];
    int tope; // índice del último elemento

public:
    Pila() : tope(-1) {}

    bool vacia() const { return tope == -1; }
    bool llena() const { return tope == MAX - 1; }

    // Push: apilar
    bool push(const Empleado& e) {
        if (llena()) return false;
        datos[++tope] = e;
        return true;
    }

    // Pop: desapilar
    bool pop() {
        if (vacia()) return false;
        tope--;
        return true;
    }

    // Top: cima de la pila
    Empleado topElemento() const {
        if (vacia()) {
            cout << "La pila está vacía.\n";
            return Empleado(); // regresa un objeto vacío
        }
        return datos[tope];
    }
};

// --------------------- MAIN ---------------------
int main() {
    Pila pila;
    int opcion;

    do {
        cout << "\n--- MENU PILA DE EMPLEADOS ---\n";
        cout << "1. Push (apilar empleado)\n";
        cout << "2. Pop (desapilar empleado)\n";
        cout << "3. Top (consultar cima)\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            if (pila.llena()) {
                cout << "La pila está llena, no se puede apilar.\n";
            } else {
                Empleado e;
                cin.ignore();
                cin >> e;
                pila.push(e);
                cout << "Empleado apilado correctamente.\n";
            }
            break;
        }
        case 2: {
            if (pila.vacia()) {
                cout << "La pila está vacía, no se puede desapilar.\n";
            } else {
                pila.pop();
                cout << "Empleado desapilado correctamente.\n";
            }
            break;
        }
        case 3: {
            if (pila.vacia()) {
                cout << "La pila está vacía.\n";
            } else {
                cout << "Empleado en la cima:\n";
                cout << pila.topElemento();
            }
            break;
        }
        case 4:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 4);

    return 0;
}
