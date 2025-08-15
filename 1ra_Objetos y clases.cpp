#include <iostream>
#include <string>
#include <iomanip> 
#include <vector> 

class Empleado {
private:
    int Clave;
    std::string Nombre;
    std::string Domicilio;
    float Sueldo;
    std::string ReportaA;

public:
    // Constructor
    Empleado(int clave, std::string nombre, std::string domicilio, float sueldo, std::string reportaA)
        : Clave(clave), Nombre(nombre), Domicilio(domicilio), Sueldo(sueldo), ReportaA(reportaA) {}

    // Métodos
    void Imprime() {
        std::cout << "\nDatos del empleado:" << std::endl;
        std::cout << "Clave: " << Clave << std::endl;
        std::cout << "Nombre: " << Nombre << std::endl;
        std::cout << "Domicilio: " << Domicilio << std::endl;
        std::cout << "Sueldo: $" << std::fixed << std::setprecision(2) << Sueldo << std::endl;
        std::cout << "Reporta a: " << ReportaA << std::endl;
    }

    void CambiaDomic(std::string nuevoDomicilio) {
        Domicilio = nuevoDomicilio;
        std::cout << "Domicilio actualizado correctamente." << std::endl;
    }

    void CambiaReportaA(std::string nuevoJefe) {
        ReportaA = nuevoJefe;
        std::cout << "Persona a reportar actualizada correctamente." << std::endl;
    }

    void ActualSueldo(float porcentaje) {
        Sueldo *= (1 + porcentaje / 100);
        std::cout << "Sueldo actualizado correctamente. Nuevo sueldo: $"
                  << std::fixed << std::setprecision(2) << Sueldo << std::endl;
    }

    // Métodos para acceder a atributos privados
    int getClave() const { return Clave; }
    std::string getNombre() const { return Nombre; }
};

//Menu
void mostrarMenu() {
    std::cout << "\nMENU DE OPCIONES" << std::endl;
    std::cout << "1. Cambiar domicilio de un empleado" << std::endl;
    std::cout << "2. Actualizar sueldo de un empleado" << std::endl;
    std::cout << "3. Imprimir datos de un empleado" << std::endl;
    std::cout << "4. Cambiar persona a reportar" << std::endl;
    std::cout << "5. Mostrar todos los empleados" << std::endl;
    std::cout << "6. Salir" << std::endl;
    std::cout << "Seleccione una opcion: ";
}

int main() {
    // EMPLEADOS
    Empleado JefePlanta(123, "Juan Perez", "Av. Industrial 123", 35000.0f, "Gerente General");
    Empleado JefePersonal(456, "Maria Lopez", "Calle Primavera 45", 32000.0f, "Gerente General");

    // Vector para manejar todos los empleados
    std::vector<Empleado*> empleados;
    empleados.push_back(&JefePlanta);
    empleados.push_back(&JefePersonal);

    int opcion, clave;
    bool encontrado;

    do {
        mostrarMenu();
        std::cin >> opcion;

        switch(opcion) {
            case 1: { // Cambiar domicilio
                std::cout << "\nIngrese la clave del empleado (123-JefePlanta, 456-JefePersonal): ";
                std::cin >> clave;
                std::cin.ignore(); // Limpiar buffer

                encontrado = false;
                for (auto emp : empleados) {
                    if (emp->getClave() == clave) {
                        std::string nuevoDomicilio;
                        std::cout << "Ingrese el nuevo domicilio: ";
                        std::getline(std::cin, nuevoDomicilio);
                        emp->CambiaDomic(nuevoDomicilio);
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "Empleado no encontrado." << std::endl;
                }
                break;
            }
            case 2: { // Actualizar sueldo
                std::cout << "\nIngrese la clave del empleado (123-JefePlanta, 456-JefePersonal): ";
                std::cin >> clave;

                encontrado = false;
                for (auto emp : empleados) {
                    if (emp->getClave() == clave) {
                        float porcentaje;
                        std::cout << "Ingrese el porcentaje de incremento: ";
                        std::cin >> porcentaje;
                        emp->ActualSueldo(porcentaje);
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "Empleado no encontrado." << std::endl;
                }
                break;
            }
            case 3: { // Imprimir datos
                std::cout << "\nIngrese la clave del empleado (123-JefePlanta, 456-JefePersonal): ";
                std::cin >> clave;

                encontrado = false;
                for (auto emp : empleados) {
                    if (emp->getClave() == clave) {
                        emp->Imprime();
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "Empleado no encontrado." << std::endl;
                }
                break;
            }
            case 4: { // Cambiar persona a reportar
                std::cout << "\nIngrese la clave del empleado (123-JefePlanta, 456-JefePersonal): ";
                std::cin >> clave;
                std::cin.ignore(); // Limpiar buffer

                encontrado = false;
                for (auto emp : empleados) {
                    if (emp->getClave() == clave) {
                        std::string nuevoJefe;
                        std::cout << "Ingrese el nuevo nombre de la persona a reportar: ";
                        std::getline(std::cin, nuevoJefe);
                        emp->CambiaReportaA(nuevoJefe);
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    std::cout << "Empleado no encontrado." << std::endl;
                }
                break;
            }
            case 5: { // Mostrar todos los empleados
                std::cout << "\nLISTA DE TODOS LOS EMPLEADOS:\n";
                std::cout << "=== JEFE PLANTA (Clave: 123) ===" << std::endl;
                JefePlanta.Imprime();
                std::cout << "\n=== JEFE PERSONAL (Clave: 456) ===" << std::endl;
                JefePersonal.Imprime();
                break;
            }
            case 6:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 6);

    return 0;
}
