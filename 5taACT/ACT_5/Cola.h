#ifndef COLA_H
#define COLA_H

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

    // Sobrecarga de entrada
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

    // Sobrecarga de salida
    friend ostream& operator<<(ostream& o, const Solicitud& s) {
        o << "Alumno: " << s.nombreAlumno << "\n";
        o << "Carrera: " << s.carrera << "\n";
        o << "Materias aprobadas: " << s.materiasAprobadas << "\n";
        o << "Promedio: " << s.promedio << "\n";
        return o;
    }
};

// --------------------- Clase Cola ---------------------
class Cola {
private:
    Solicitud datos[TAM];
    int frente;
    int final;
    int cantidad;

public:
    Cola() : frente(0), final(-1), cantidad(0) {}

    bool vacia() const { return cantidad == 0; }
    bool llena() const { return cantidad == TAM; }

    // Encolar
    bool enqueue(const Solicitud& s) {
        if (llena()) {
            cout << "Cola llena.\n";
            return false;
        }
        final = (final + 1) % TAM;
        datos[final] = s;
        cantidad++;
        return true;
    }

    // Desencolar
    bool dequeue(Solicitud& s) {
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
    Solicitud front() const {
        if (vacia()) {
            cout << "Cola vacía.\n";
            return Solicitud();
        }
        return datos[frente];
    }
};

#endif
