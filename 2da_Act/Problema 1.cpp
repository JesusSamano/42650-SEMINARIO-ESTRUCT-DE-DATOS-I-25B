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

public:
    // Constructor  Por def (sin parametros) copia
    Empleado(int clave = 0, string nom = "", string dom = "", float sue = 0.0, string jefe = "")
        : claveEmpleado(clave), nombre(nom), domicilio(dom), sueldo(sue), reportaA(jefe) {}

    int getClave() const { return claveEmpleado; }
    string getNombre() const { return nombre; }
    float getSueldo() const { return sueldo; }

    // Métodos
    void cambiarDomicilio(string nuevoDom) { domicilio = nuevoDom; }
    void actualizarSueldo(float porcentaje) { sueldo += sueldo * (porcentaje / 100.0); }
    void cambiarReportaA(string nuevoJefe) { reportaA = nuevoJefe; }
    void imprimirDatos() const {
        cout << "Clave: " << claveEmpleado << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Domicilio: " << domicilio << endl;
        cout << "Sueldo: $" << sueldo << endl;
        cout << "Reporta a: " << reportaA << endl;
    }

    // Sobrecarga de operadores
    bool operator==(const Empleado& e) const {
        return claveEmpleado == e.claveEmpleado;
    }

    bool operator!=(const Empleado& e) const {
        return !(*this == e);
    }

    bool operator<(const Empleado& e) const {
        return sueldo < e.sueldo;
    }

    bool operator>(const Empleado& e) const {
        return sueldo > e.sueldo;
    }

    Empleado operator+(const Empleado& e) const {
        return Empleado(
            0, // clave ficticia
            nombre + " & " + e.nombre,
            domicilio + " / " + e.domicilio,
            sueldo + e.sueldo,
            "Fusion"
        );
    }

    // Sobrecarga de flujo de salida
    friend ostream& operator<<(ostream& o, const Empleado& e) {
        o << "Clave: " << e.claveEmpleado << "\n";
        o << "Nombre: " << e.nombre << "\n";
        o << "Domicilio: " << e.domicilio << "\n";
        o << "Sueldo: $" << e.sueldo << "\n";
        o << "Reporta a: " << e.reportaA << "\n";
        return o;
    }

    // Sobrecarga de flujo de entrada
    friend istream& operator>>(istream& i, Empleado& e) {
        cout << "Clave: "; i >> e.claveEmpleado; i.ignore();
        cout << "Nombre: "; getline(i, e.nombre);
        cout << "Domicilio: "; getline(i, e.domicilio);
        cout << "Sueldo: "; i >> e.sueldo; i.ignore();
        cout << "Reporta a: "; getline(i, e.reportaA);
        return i;
    }
};

int main() {
    // USUARIOS
    Empleado JefePlanta(1, "Jesus Samano", "Av. Siempre Viva 123", 25000, "Director General");
    Empleado JefePersonal(2, "Alexa Martinez", "Calle Reforma 45", 22000, "Director General");

    int opcion;
    do {
        cout << "\n--- MENU EMPLEADOS ---\n";
        cout << "1. Cambiar domicilio\n";
        cout << "2. Actualizar sueldo\n";
        cout << "3. Imprimir datos\n";
        cout << "4. Cambiar jefe\n";
        cout << "5. Comparar empleados (==, !=, <, >)\n";
        cout << "6. Unir empleados (+)\n";
        cout << "7. Ingresar nuevo empleado (>>)\n";
        cout << "8. Mostrar empleado << \n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

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
        case 5: {
            cout << "Comparando JefePlanta y JefePersonal...\n";
            if (JefePlanta == JefePersonal)
                cout << "Tienen el mismo puesto.\n";

            else if (JefePlanta != JefePersonal)
                cout << "Tienen diferente puesto.\n";

            if (JefePlanta > JefePersonal)
                cout << JefePlanta.getNombre() << " gana mas.\n";

            else if (JefePlanta < JefePersonal)
                cout << JefePersonal.getNombre() << " gana mas.\n";
            else
                cout << "Ambos ganan lo mismo.\n";
            break;
        }
        case 6: {
            cout << "Union de empleados\n";
            Empleado fusion = JefePlanta + JefePersonal;
            cout << fusion;
            break;
        }
        case 7: {
            cout << "Ingresar nuevo empleado:\n";
            Empleado nuevo;
            cin.ignore();
            cin >> nuevo;
            cout << "Empleado ingresado:\n" << nuevo;
            break;
        }
        case 8: {
            cout << "Mostrando empleados:\n";
            cout << "JefePlanta:\n" << JefePlanta;
            cout << "JefePersonal:\n" << JefePersonal;
            break;
        }
        }
    } while (opcion != 0);

    return 0;
}

