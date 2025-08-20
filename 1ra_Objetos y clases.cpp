#include <iostream>
#include <string>
using namespace std;

class Empleado {
private:
    int claveEmpleado;
    string nombre;
    string domicilio;
    float sueldo;
    string reportaA;

public: // Constructor
    Empleado(int clave, string nom, string dom, float sue, string jefe)
        : claveEmpleado(clave), nombre(nom), domicilio(dom), sueldo(sue), reportaA(jefe) {}

    int getClave() const { return claveEmpleado; }

     // Métodos
    void cambiarDomicilio(string nuevoDom) {
        domicilio = nuevoDom;
    }

    void actualizarSueldo(float porcentaje) {
        sueldo += sueldo * (porcentaje / 100.0);
    }

    void cambiarReportaA(string nuevoJefe) {
        reportaA = nuevoJefe;
    }

    void imprimirDatos() const {
        cout << "Clave: " << claveEmpleado << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Domicilio: " << domicilio << endl;
        cout << "Sueldo: $" << sueldo << endl;
        cout << "Reporta a: " << reportaA << endl;
    }
};

int main() {
    //USUARIOS
    Empleado JefePlanta(1, "Carlos Pérez", "Av. Siempre Viva 123", 25000, "Director General");
    Empleado JefePersonal(2, "Ana López", "Calle Reforma 45", 22000, "Director General");

    int opcion;
    do {
        cout << "\n--- MENU EMPLEADOS ---\n";
        cout << "1. Cambiar domicilio\n";
        cout << "2. Actualizar sueldo\n";
        cout << "3. Imprimir datos\n";
        cout << "4. Cambiar jefe\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        //MENU
        int clave;
        switch (opcion) {
        case 1: {
            cout << "Clave del empleado: ";
            cin >> clave;
            cin.ignore();
            cout << "Nuevo domicilio: ";
            string dom;
            getline(cin, dom);

            if (clave == JefePlanta.getClave())
                JefePlanta.cambiarDomicilio(dom);
            else if (clave == JefePersonal.getClave())
                JefePersonal.cambiarDomicilio(dom);
            break;
        }
        case 2: {
            cout << "Clave del empleado: ";
            cin >> clave;
            cout << "Porcentaje de aumento: ";
            float porc;
            cin >> porc;

            if (clave == JefePlanta.getClave())
                JefePlanta.actualizarSueldo(porc);
            else if (clave == JefePersonal.getClave())
                JefePersonal.actualizarSueldo(porc);
            break;
        }
        case 3: {
            cout << "Clave del empleado: ";
            cin >> clave;

            if (clave == JefePlanta.getClave())
                JefePlanta.imprimirDatos();
            else if (clave == JefePersonal.getClave())
                JefePersonal.imprimirDatos();
            break;
        }
        case 4: {
            cout << "Clave del empleado: ";
            cin >> clave;
            cin.ignore();
            cout << "Nuevo jefe: ";
            string jefe;
            getline(cin, jefe);

            if (clave == JefePlanta.getClave())
                JefePlanta.cambiarReportaA(jefe);
            else if (clave == JefePersonal.getClave())
                JefePersonal.cambiarReportaA(jefe);
            break;
        }
        }
    } while (opcion != 0);

    return 0;
}
