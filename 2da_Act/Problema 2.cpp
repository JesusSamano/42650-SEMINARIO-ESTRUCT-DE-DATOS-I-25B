#include <iostream>
#include <string>
using namespace std;

class Materia {
private:
    int clave;
    string nombre;
    string maestro;
    int creditos;

public:
    // Constructor
    Materia(int c = 0, string n = "", string m = "", int cr = 0) {
        clave = c;
        nombre = n;
        maestro = m;
        creditos = cr;
    }

    // Métodos
    void setClave(int c) { clave = c; }
    void setMaestro(string m) { maestro = m; }

    void imprimirDatos() const {
        cout << "\nMateria: " << nombre << endl;
        cout << "Clave: " << clave << endl;
        cout << "Maestro: " << maestro << endl;
        cout << "Creditos: " << creditos << endl;
    }

    // -------- Sobrecarga de operadores --------
    bool operator==(const Materia& m) const { return maestro == m.maestro; }
    bool operator!=(const Materia& m) const { return maestro != m.maestro; }
    bool operator<(const Materia& m) const { return creditos < m.creditos; }
    bool operator>(const Materia& m) const { return creditos > m.creditos; }

    // Fusionar materias
    Materia operator+(const Materia& m) const {
        return Materia(
            0,
            nombre + " & " + m.nombre,
            maestro + " / " + m.maestro,
            creditos + m.creditos
        );
    }

    // Sobrecarga de salida
    friend ostream& operator<<(ostream& o, const Materia& m) {
        o << "Materia: " << m.nombre << "\n";
        o << "Clave: " << m.clave << "\n";
        o << "Maestro: " << m.maestro << "\n";
        o << "Creditos: " << m.creditos << "\n";
        return o;
    }

    // Sobrecarga de entrada
    friend istream& operator>>(istream& i, Materia& m) {
        cout << "Clave: ";
        i >> m.clave;
        i.ignore();
        cout << "Nombre: ";
        getline(i, m.nombre);
        cout << "Maestro: ";
        getline(i, m.maestro);
        cout << "Creditos: ";
        i >> m.creditos;
        return i;
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
        cout << "3. Imprimir datos de materias\n";
        cout << "4. Comparar materias (==, !=, <, >)\n";
        cout << "5. Fusionar materias (+)\n";
        cout << "6. Capturar nueva materia (>>)\n";
        cout << "7. Mostrar materias \n";
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
            cin.ignore();
            getline(cin, nuevoMaestro);
            BasesDatos.setMaestro(nuevoMaestro);
            cout << "Maestro actualizado correctamente.\n";
            break;
        }
        case 3:
            cout << Programacion;
            cout << BasesDatos;
            break;
        case 4: {
            cout << "Comparando maestros de Programacion y Bases de Datos\n";
            if (Programacion == BasesDatos)
                cout << "Ambas materias tienen el mismo maestro.\n";
            else if (Programacion != BasesDatos)
                cout << "Los maestros son diferentes.\n";

            if (Programacion > BasesDatos)
                cout << "Programacion tiene mas creditos.\n";
            else if (Programacion < BasesDatos)
                cout << "Bases de Datos tiene mas creditos.\n";
            else
                cout << "Tienen los mismos creditos.\n";
            break;
        }
        case 5: {
            cout << "Unir materias.\n";
            Materia fusion = Programacion + BasesDatos;
            cout << fusion;
            break;
        }
        case 6: {
            Materia nueva;
            cin.ignore();
            cin >> nueva;
            cout << "Materia ingresada:\n" << nueva;
            break;
        }
        case 7: {
            cout << "Materia Programacion:\n" << Programacion;
            cout << "Materia Bases de Datos:\n" << BasesDatos;
            break;
        }
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}
