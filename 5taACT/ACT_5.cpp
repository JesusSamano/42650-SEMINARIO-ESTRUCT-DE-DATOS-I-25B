#include <iostream>
#include <string>
#define TAM 50
using namespace std;

// --------------------- Clase Solicitud ---------------------
class Solicitud {
private:
    string nombreAlumno;
    string carrera;
    int materiasAprobadas;
    float promedio;

    //CONSTRUCTOR
public:
    Solicitud(string nom = "", string car = "", int mat = 0, float prom = 0.0)
        : nombreAlumno(nom), carrera(car), materiasAprobadas(mat), promedio(prom) {}

    // SOBRECARGA DE LA ENTRADA
        friend istream& operator>>(istream& i, Solicitud& s) {
        i.ignore();
        cout << "Nombre del alumno: ";
        getline(i, s.nombreAlumno);
        cout << "Carrera: ";
        getline(i, s.carrera);
        cout << "Materias aprobadas: ";
        i >> s.materiasAprobadas;
        cout << "Promedio: ";
        i >> s.promedio;
        return i;
    }

    // SOBRECARGA DE LA SALIDA
    friend ostream& operator<<(ostream& o, const Solicitud& s) {
        o << "Alumno: " << s.nombreAlumno << "\n";
        o << "Carrera: " << s.carrera << "\n";
        o << "Materias aprobadas: " << s.materiasAprobadas << "\n";
        o << "Promedio: " << s.promedio << "\n";
        return o;
    }
};

// --------------------- Clase Cola (basada en Lista estática) ---------------------
class Cola {
private:
    Solicitud datos[TAM];
    int frente;  // apunta al primer elemento válido
    int final;   // apunta al último elemento válido
    int cantidad; // número actual de elementos

    //CONSTRUCTOR 2
public:
    Cola() : frente(0), final(-1), cantidad(0) {}

    bool vacia() const { return cantidad == 0; }
    bool llena() const { return cantidad == TAM; }

    // Encolar: al final es PUSH
    bool encolar(const Solicitud& s) {
        if (llena()) {
            cout << "Cola llena.\n";
            return false;
        }
        final = (final + 1) % TAM;
        datos[final] = s;
        cantidad++;
        return true;
    }

    // Desencolar: del frente es POP
    bool desencolar(Solicitud& s) {
        if (vacia()) {
            cout << "Cola vacía.\n";
            return false;
        }
        s = datos[frente];
        frente = (frente + 1) % TAM;
        cantidad--;
        return true;
    }

    // Consultar frente
    Solicitud frenteElemento() const {
        if (vacia()) {
            cout << "Cola vacía.\n";
            return Solicitud();
        }
        return datos[frente];
    }

    // Mostrar cola completa
    void imprime() const {
        if (vacia()) {
            cout << "Cola vacía.\n";
            return;
        }
        cout << "\n--- Solicitudes en cola ---\n";
        int idx = frente;
        for (int i = 0; i < cantidad; i++) {
            cout << datos[idx] << "-----------------\n";
            idx = (idx + 1) % TAM;
        }
    }
};

// --------------------- MAIN ---------------------
int main() {
    Cola cola;
    int opcion;

    do {
        cout << "\n--- MENU COLA DE SOLICITUDES ---\n";
        cout << "1. Dar de alta solicitud (encolar)\n";
        cout << "2. Elaborar constancia (desencolar)\n";
        cout << "3. Mostrar todas las solicitudes en espera\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            Solicitud s;
            cin >> s;
            cola.encolar(s);
            cout << "Solicitud registrada exitosamente.\n";
            break;
        }
        case 2: {
            Solicitud s;
            if (cola.desencolar(s)) {
                cout << "\n--- CONSTANCIA ELABORADA ---\n";
                cout << s;
            }
            break;
        }
        case 3:
            cola.imprime();
            break;
        case 4:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 4);

    return 0;
}
