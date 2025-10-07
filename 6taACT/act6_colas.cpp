#include <iostream>
#include <string>
using namespace std;

//**************************** Clase Solicitud ****************************
class Solicitud {
private:
    string nombreAlumno;
    string carrera;
    int materiasAprobadas;
    float promedio;
public:
    Solicitud() : nombreAlumno(""), carrera(""), materiasAprobadas(0), promedio(0.0) {}
    Solicitud(string n, string c, int m, float p)
        : nombreAlumno(n), carrera(c), materiasAprobadas(m), promedio(p) {}

    // Sobrecarga de operadores
    friend istream& operator>>(istream& in, Solicitud& s) {
        cout << "\nNombre del alumno: ";
        getline(in >> ws, s.nombreAlumno);
        cout << "Carrera: ";
        getline(in >> ws, s.carrera);
        cout << "Total de materias aprobadas: ";
        in >> s.materiasAprobadas;
        cout << "Promedio general: ";
        in >> s.promedio;
        return in;
    }

    friend ostream& operator<<(ostream& out, const Solicitud& s) {
        out << "\n--- Constancia de estudio ---"
            << "\nAlumno: " << s.nombreAlumno
            << "\nCarrera: " << s.carrera
            << "\nMaterias aprobadas: " << s.materiasAprobadas
            << "\nPromedio general: " << s.promedio
            << "\n-----------------------------\n";
        return out;
    }

    bool operator==(const Solicitud& s) const {
        return nombreAlumno == s.nombreAlumno;
    }

    // Para la búsqueda binaria (ordenar por nombre)
    bool operator<(const Solicitud& s) const {
        return nombreAlumno < s.nombreAlumno;
    }

    string getNombre() const { return nombreAlumno; }
};

//**************************** Clase Cola Genérica ****************************
template <class T>
class Cola {
private:
    static const int TAM = 100;
    T datos[TAM];
    int frente, fin;
public:
    Cola() : frente(0), fin(-1) {}

    bool vacia() const { return fin < frente; }
    bool llena() const { return fin == TAM - 1; }

    void enqueue(const T& elem) {
        if (llena()) {
            cout << "Error: la cola esta llena.\n";
            return;
        }
        datos[++fin] = elem;
    }

    T dequeue() {
        if (vacia()) {
            cout << "Error: la cola esta vacía.\n";
            return T();
        }
        return datos[frente++];
    }

    void mostrar() const {
        if (vacia()) {
            cout << "\nNo hay solicitudes en la cola.\n";
            return;
        }
        cout << "\nSolicitudes en cola:\n";
        for (int i = frente; i <= fin; ++i)
            cout << i - frente + 1 << ". " << datos[i].getNombre() << endl;
    }

    // Búsqueda lineal
    int busquedaLineal(const T& elem) const {
        for (int i = frente; i <= fin; ++i) {
            if (datos[i] == elem)
                return i - frente; // posición relativa en la cola
        }
        return -1;
    }

    // Búsqueda binaria (requiere que los datos estén ordenados por nombre)
    int busquedaBinaria(const T& elem) const {
        int izq = frente, der = fin;
        while (izq <= der) {
            int mid = (izq + der) / 2;
            if (datos[mid] == elem)
                return mid - frente;
            else if (datos[mid] < elem)
                izq = mid + 1;
            else
                der = mid - 1;
        }
        return -1;
    }

    int size() const { return fin - frente + 1; }

    // Ordenar por nombre (para búsqueda binaria)
    void ordenar() {
        for (int i = frente; i < fin; ++i) {
            for (int j = i + 1; j <= fin; ++j) {
                if (datos[j] < datos[i]) {
                    T temp = datos[i];
                    datos[i] = datos[j];
                    datos[j] = temp;
                }
            }
        }
    }
};


int main() {
    Cola<Solicitud> cola;
    int opcion;
    Solicitud s;

    do {
        cout << "1. Dar de alta alumno \n";
        cout << "2. Elaborar constancia\n";
        cout << "3. Buscar de manera lineal\n";
        cout << "4. Buscar de manera binaria\n";
        cout << "5. Mostrar solicitudes en cola\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cin >> s;
            cola.enqueue(s);
            cout << "\nSolicitud agregada correctamente.\n";
            break;

        case 2:
            if (!cola.vacia()) {
                cout << "\nElaborando constancia...\n";
                cout << cola.dequeue();
            } else {
                cout << "\nNo hay solicitudes por atender.\n";
            }
            break;

        case 3: {
            cout << "\nIngrese el nombre del alumno a buscar: ";
            {
                string nombre;
                cin.ignore();
                getline(cin, nombre);
                Solicitud buscar(nombre, "", 0, 0);
                int pos = cola.busquedaLineal(buscar);
                if (pos != -1)
                    cout << "\nFaltan " << pos
                         << " constancias antes de la de " << nombre << ".\n";
                else
                    cout << "\nNo se encontro la solicitud. Debe darla de alta.\n";
            }
            break;
        }

        case 4: {
            cola.ordenar();
            cout << "\nIngrese el nombre del alumno a buscar (busqueda binaria): ";
            {
                string nombre;
                cin.ignore();
                getline(cin, nombre);
                Solicitud buscar(nombre, "", 0, 0);
                int pos = cola.busquedaBinaria(buscar);
                if (pos != -1)
                    cout << "\nFaltan " << pos
                         << " constancias antes de la de " << nombre << ".\n";
                else
                    cout << "\nNo se encontro la solicitud. Debe darla de alta.\n";
            }
            break;
        }

        case 5:
            cola.mostrar();
            break;

        case 0:
            cout << "\nSaliendo del sistema...\n";
            break;

        default:
            cout << "\nOpcion no válida.\n";
        }

    } while (opcion != 0);

    return 0;
}
