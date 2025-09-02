//Crear lifo, transformar de listas a pilas

#include <iostream>
#include <string>
using namespace std;

const int MAX = 100; // capacidad máxima de la lista

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

    // Sobrecarga de comparación (para búsqueda)
    bool operator==(const Empleado& e) const {
        return claveEmpleado == e.claveEmpleado; // lo consideramos igual si tienen misma clave
    }
};

// --------------------- LISTA ESTÁTICA ---------------------
class ListaEstatica {
private:
    Empleado datos[MAX];
    int tam; // último índice ocupado

public:
    ListaEstatica() { tam = -1; }

    bool Vacia() const { return tam == -1; }
    bool Llena() const { return tam == MAX - 1; }

    // Agregar al final
    int Agrega(Empleado e) {
        if (Llena()) return 0;
        datos[++tam] = e;
        return 1;
    }

    // Inserta en posición específica
    int Inserta(Empleado e, int pos) {
        if (Llena()) return 0;
        if (pos < 0 || pos > tam + 1) return -1;
        for (int i = tam + 1; i > pos; i--)
            datos[i] = datos[i - 1];
        datos[pos] = e;
        tam++;
        return 1;
    }

    // Busca por clave de empleado
    int Busca(const Empleado& e) {
        if (Vacia()) return -2;
        for (int i = 0; i <= tam; i++) {
            if (datos[i] == e) return i;
        }
        return -1; // no encontrado
    }

    // Elimina por posición
    int Elimina(int pos) {
        if (Vacia()) return -2;
        if (pos < 0 || pos > tam) return -1;
        for (int i = pos; i < tam; i++)
            datos[i] = datos[i + 1];
        tam--;
        return 1;
    }

    // Mostrar lista
    void Muestra() {
        if (Vacia()) {
            cout << "La lista esta vacia.\n";
            return;
        }
        for (int i = 0; i <= tam; i++) {
            cout << "--- Empleado en posicion " << i << " ---\n";
            cout << datos[i];
        }
    }
};

// --------------------- MAIN ---------------------
int main() {
    ListaEstatica lista;
    int opcion;

    do {
        cout << "\n--- MENU LISTA DE EMPLEADOS ---\n";
        cout << "1. Agregar empleado\n";
        cout << "2. Buscar empleado\n";
        cout << "3. Eliminar empleado\n";
        cout << "4. Insertar empleado en posicion\n";
        cout << "5. Mostrar empleados\n";
        cout << "6. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            if (lista.Llena()) {
                cout << "No se puede agregar, la lista está llena.\n";
            } else {
                Empleado e;
                cin.ignore();
                cin >> e;
                lista.Agrega(e);
                cout << "Empleado agregado al final.\n";
            }
            break;
        }
        case 2: {
            if (lista.Vacia()) {
                cout << "La lista esta vacia.\n";
            } else {
                Empleado e;
                cin.ignore();
                cin >> e;
                int pos = lista.Busca(e);
                if (pos == -1) cout << "No se encontró al empleado.\n";
                else cout << "Empleado encontrado en posicion " << pos << ".\n";
            }
            break;
        }
        case 3: {
            if (lista.Vacia()) {
                cout << "La lista esta vacia.\n";
            } else {
                int pos;
                cout << "Dame la posicion del empleado a eliminar: ";
                cin >> pos;
                int res = lista.Elimina(pos);
                if (res == 1) cout << "Empleado eliminado.\n";
                else cout << "No se pudo eliminar, posición invalida.\n";
            }
            break;
        }
        case 4: {
    if (lista.Llena()) {
        cout << "La lista está llena, no se puede insertar.\n";
    } else {
        cout << "Dame el Empleado a insertar:\n";
        Empleado e;
        cin.ignore();
        cin >> e;
        cout << "Dame la posicion donde se debe insertar el Empleado: ";
        int pos;
        cin >> pos;

        int res = lista.Inserta(e, pos);
        if (res == 1)
            cout << "Empleado insertado correctamente en la posición " << pos << ".\n";
        else if (res == -1)
            cout << "No se puede insertar en la posición " << pos << ", es invalida.\n";
        else
            cout << "No se pudo insertar, error inesperado.\n";
    }
    break;
}

        case 5:
            lista.Muestra();
            break;
        case 6:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 6);

    return 0;
}

