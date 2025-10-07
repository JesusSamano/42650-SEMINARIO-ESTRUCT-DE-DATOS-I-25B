#include <iostream>
#include <string>
using namespace std;


class Solicitud {
private:
    string nombreAlumno;
    string carrera;
    string preparatoria;
    float promedio;
public:
    Solicitud() : nombreAlumno(""), carrera(""), preparatoria(""), promedio(0.0) {}
    Solicitud(string n, string c, string p, float prom)
        : nombreAlumno(n), carrera(c), preparatoria(p), promedio(prom) {}

    // Sobrecarga de operadores
    friend istream& operator>>(istream& in, Solicitud& s) {
        cout << "\nNombre del alumno: ";
        getline(in >> ws, s.nombreAlumno);
        cout << "Carrera a cursar: ";
        getline(in >> ws, s.carrera);
        cout << "Preparatoria de procedencia: ";
        getline(in >> ws, s.preparatoria);
        cout << "Promedio general: ";
        in >> s.promedio;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Solicitud& s) {
        out << "\n--- Solicitud de ingreso ---"
            << "\nAlumno: " << s.nombreAlumno
            << "\nCarrera: " << s.carrera
            << "\nPreparatoria: " << s.preparatoria
            << "\nPromedio: " << s.promedio
            << "\n----------------------------\n";
        return out;
    }

    bool operator==(const Solicitud& s) const {
        return nombreAlumno == s.nombreAlumno;
    }

    bool operator<(const Solicitud& s) const {
        // Orden descendente por promedio (los mejores primeros)
        return promedio > s.promedio;
    }

    float getPromedio() const { return promedio; }
    string getNombre() const { return nombreAlumno; }
};


class Lista {
private:
    static const int TAM = 100;
    Solicitud datos[TAM];
    int ult;
public:
    Lista() : ult(-1) {}

    bool vacia() const { return ult == -1; }
    bool llena() const { return ult == TAM - 1; }
    int ultimo() const { return ult; }

    void insertarFinal(const Solicitud& s) {
        if (llena()) {
            cout << "Error: la lista esta llena.\n";
            return;
        }
        datos[++ult] = s;
    }

    void mostrar() const {
        if (vacia()) {
            cout << "\nNo hay solicitudes en la lista.\n";
            return;
        }
        cout << "\nSolicitudes registradas:\n";
        for (int i = 0; i <= ult; ++i) {
            cout << i + 1 << ". " << datos[i].getNombre()
                 << " (Promedio: " << datos[i].getPromedio() << ")\n";
        }
    }

    // Algoritmo de inserción (según el pseudocódigo dado)
    void ordenarPorPromedio() {
        int i = 1;
        while (i <= ult) {
            Solicitud aux = datos[i];
            int j = i;
            while (j > 0 && aux < datos[j - 1]) {
                datos[j] = datos[j - 1];
                j = j - 1;
            }
            if (i != j)
                datos[j] = aux;
            i = i + 1;
        }
    }

    // Algoritmo de búsqueda binaria (según el pseudocódigo dado)
    int busquedaBinaria(const Solicitud& elem) const {
        int i = 0, j = ult;
        while (i <= j) {
            int medio = (i + j) / 2;
            if (datos[medio] == elem)
                return medio;
            else if (elem < datos[medio])
                j = medio - 1;
            else
                i = medio + 1;
        }
        return -1;
    }

    Solicitud get(int pos) const { return datos[pos]; }
};

//**************************** Función principal ****************************
int main() {
    Lista lista;
    int opcion;

    do {
        cout << "\n=== COORDINACIÓN ESCOLAR ===\n";
        cout << "1. Dar de alta solicitud\n";
        cout << "2. Mostrar solicitudes\n";
        cout << "3. Buscar solicitud (búsqueda binaria)\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            Solicitud s;
            cin >> s;
            lista.insertarFinal(s);
            lista.ordenarPorPromedio(); // Ordenar cada vez que se agrega
            cout << "\nSolicitud agregada correctamente.\n";
            break;
        }
        case 2:
            lista.mostrar();
            break;
        case 3: {
            if (lista.vacia()) {
                cout << "\nNo hay solicitudes registradas.\n";
                break;
            }
            string nombre;
            cout << "\nIngrese el nombre del alumno a buscar: ";
            cin.ignore();
            getline(cin, nombre);
            Solicitud buscado(nombre, "", "", 0.0);
            int pos = lista.busquedaBinaria(buscado);
            if (pos != -1) {
                cout << "\nSolicitud encontrada en la posición: " << pos + 1
                     << " (lugar por promedio)\n";
                cout << lista.get(pos);
            } else {
                cout << "\nNo se encontró la solicitud. Debe darla de alta.\n";
            }
            break;
        }
        case 0:
            cout << "\nSaliendo del sistema...\n";
            break;
        default:
            cout << "\nOpción no válida.\n";
        }

    } while (opcion != 0);

    return 0;
}
