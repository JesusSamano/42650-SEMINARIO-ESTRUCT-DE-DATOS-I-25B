#include <iostream>
using namespace std;

class Materia {
private:
    int clave;
    string nombre;
    string maestro;
    int creditos;

public:
    // Constructor
    Materia(int c, string n, string m, int cr) {
        clave = c;
        nombre = n;
        maestro = m;
        creditos = cr;
    }

    // Métodos
    void setClave(int c) { clave = c; }
    void setMaestro(string m) { maestro = m; }

    void imprimirDatos() {
        cout << "\nMateria: " << nombre << endl;
        cout << "Clave: " << clave << endl;
        cout << "Maestro: " << maestro << endl;
        cout << "Creditos: " << creditos << endl;
    }
};

int main() {
    Materia Programacion(101, "Programacion", "Luis Torres", 8);
    Materia BasesDatos(202, "Bases de Datos", "Maria Gomez", 10);

    int opcion;
    do {
        cout << "\n--- MENU MATERIAS ---\n";
        cout << "1. Cambiar clave de Programacion\n";
        cout << "2. Cambiar maestro de Bases de Datos\n";
        cout << "3. Imprimir datos de Bases de Datos\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            int nuevaClave;
            cout << "Nueva clave para Programacion: ";
            cin >> nuevaClave;
            Programacion.setClave(nuevaClave);
            cout << "Clave actualizada correctamente.\n";
            break;
        }
        case 2: {
            string nuevoMaestro;
            cout << "Nuevo maestro para Bases de Datos: ";
            cin.ignore(); // limpiar buffer
            getline(cin, nuevoMaestro);
            BasesDatos.setMaestro(nuevoMaestro);
            cout << "Maestro actualizado correctamente.\n";
            break;
        }
        case 3:
            BasesDatos.imprimirDatos();
            Programacion.imprimirDatos();
            break;
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
