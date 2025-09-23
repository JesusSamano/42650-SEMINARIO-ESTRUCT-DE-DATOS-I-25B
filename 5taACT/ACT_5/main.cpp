#include <iostream>
#include "Cola.h"
using namespace std;

int main() {
    Cola MiCola;
    Solicitud x;
    int opcion;

    do {
        cout << "\n--- MENU COLA DE SOLICITUDES ---\n";
        cout << "1. Dar de alta solicitud (Encolar)\n";
        cout << "2. Elaborar constancia (Desencolar)\n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            if (MiCola.llena()) {
                cout << "La cola está llena, no se puede registrar más solicitudes.\n";
            } else {
                cin >> x;
                MiCola.enqueue(x);
                cout << "Solicitud registrada exitosamente.\n";
            }
            break;

        case 2:
            if (MiCola.vacia()) {
                cout << "No hay solicitudes pendientes.\n";
            } else {
                Solicitud s;
                MiCola.dequeue(s);
                cout << "\n--- CONSTANCIA ELABORADA ---\n";
                cout << s;
            }
            break;

        case 3:
            cout << "Saliendo del programa...\n";
            break;

        default:
            cout << "Opción inválida, intenta de nuevo.\n";
        }
    } while (opcion != 3);

    return 0;
}
