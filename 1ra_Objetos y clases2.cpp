#include <iostream>
#include <string>
#include <iomanip>

class Materia {
private:


public:
    int Clave;
    std::string Nombre;
    std::string ProfesorTit;
    std::string LibroTexto;
    // Constructor
    Materia(int clave, std::string nombre, std::string profesor, std::string libro)
        : Clave(clave), Nombre(nombre), ProfesorTit(profesor), LibroTexto(libro) {}

    // Métodos
    void Imprime() {

        std::cout << "\nClave: " << Clave << std::endl;
        std::cout << "Nombre: " << Nombre << std::endl;
        std::cout << "Profesor: " << ProfesorTit << std::endl;
        std::cout << "Libro de texto: " << LibroTexto << std::endl;
    }

    void CambiaClave(int nuevaClave) {
        Clave = nuevaClave;
        std::cout << "Clave actualizada correctamente." << std::endl;
    }

    void CambiaProfe(std::string nuevoProfesor) {
        ProfesorTit = nuevoProfesor;
        std::cout << "Profesor actualizado correctamente." << std::endl;
    }
};

// Función para mostrar el menú
void mostrarMenu() {
    std::cout << "\nMENU DE OPCIONES" << std::endl;
    std::cout << "1. Cambiar clave de Programacion" << std::endl;
    std::cout << "2. Cambiar profesor de BasesDatos" << std::endl;
    std::cout << "3. Imprimir datos de BasesDatos" << std::endl;
    std::cout << "4. Salir" << std::endl;
    std::cout << "Seleccione una opcion: ";
}

int main() {
    // Crear las materias específicas
    Materia Programacion(567, "Programacion", "Alexandra Garcia", "Introduccion a C++");
    Materia BasesDatos(789, "Bases de Datos", "Aalejandra Martinez", "Fundamentos de SQL");

    int opcion, nuevaClave;
    std::string nuevoProfesor;

    do {
        mostrarMenu();
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar buffer

        switch(opcion) {
            case 1: // Cambiar clave de Programacion
                std::cout << "\nIngrese la nueva clave para Programacion: ";
                std::cin >> nuevaClave;
                Programacion.CambiaClave(nuevaClave);
                break;

            case 2: // Cambiar profesor de BasesDatos
                std::cout << "\nIngrese el nuevo profesor para BasesDatos: ";
                std::getline(std::cin, nuevoProfesor);
                BasesDatos.CambiaProfe(nuevoProfesor);
                break;

            case 3: // Imprimir datos de BasesDatos
                std::cout << "\nDatos de la materia BasesDatos:";
                BasesDatos.Imprime();
                break;

            case 4:
                std::cout << "Saliendo del programa..." << std::endl;
                break;

            default:
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 4);

    return 0;
}
