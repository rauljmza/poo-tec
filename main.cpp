#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <limits>
#include "sistema_gestion.h"

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pausarPantalla() {
    std::cout << "\nPresione Enter para continuar...";
    limpiarBuffer();
}

int mostrarMenuPrincipal() {
    int opcion;
    bool opcionValida = false;

    while(!opcionValida) {
        std::cout << "*************************************************\n"
                 << "*         SISTEMA DE RECICLAJE BIOWAY           *\n"
                 << "*************************************************\n\n"
                 << "1. Ver centros de acopio\n"
                 << "2. Ver recolectores\n"
                 << "3. Registrar nuevo material\n"
                 << "4. Registrar recoleccion\n"
                 << "5. Ver reportes\n"
                 << "6. Salir del programa\n\n"
                 << "Ingrese su opcion: ";
        
        if(std::cin >> opcion && opcion >= 1 && opcion <= 6) {
            opcionValida = true;
        } else {
            std::cout << "\n¡ERROR! Opción no válida. Intente de nuevo.\n"
                     << "Debe elegir un número entre 1 y 6\n";
            limpiarBuffer();
            pausarPantalla();
            limpiarPantalla();
        }
    }
    return opcion;
}

int menuCentrosAcopio() {
    int opcion;
    std::cout << "\n=== MENÚ CENTROS DE ACOPIO ===\n"
              << "1. Ver todos los centros\n"
              << "2. Agregar nuevo centro\n"
              << "3. Buscar centro por nombre\n"
              << "4. Regresar al menú principal\n"
              << "\nElija una opción: ";
    std::cin >> opcion;
    return opcion;
}

int menuRecolectores() {
    int opcion;
    std::cout << "\n=== MENÚ RECOLECTORES ===\n"
              << "1. Ver todos los recolectores\n"
              << "2. Agregar nuevo recolector\n"
              << "3. Buscar recolector por nombre\n"
              << "4. Cambiar calificación de recolector\n"
              << "5. Regresar al menú principal\n"
              << "\nElija una opción: ";
    std::cin >> opcion;
    return opcion;
}

int menuReportes() {
    int opcion;
    std::cout << "\n=== MENÚ DE REPORTES ===\n"
              << "1. Reporte de todo el sistema\n"
              << "2. Reporte de materiales\n"
              << "3. Reporte de recolectores\n"
              << "4. Regresar al menú principal\n"
              << "\nElija una opción: ";
    std::cin >> opcion;
    return opcion;
}

void registrarNuevoMaterial(SistemaGestion& sistema) {
    std::string nombre, categoria;
    float precio, cantidad;
    int tiempoDescomposicion;
    char necesitaLimpieza;
    bool limpieza;
    float bonus;

    std::cout << "\n=== REGISTRO DE NUEVO MATERIAL ===\n";
    
    limpiarBuffer();
    std::cout << "Ingrese el nombre del material: ";
    std::getline(std::cin, nombre);

    std::cout << "Ingrese la categoría (papel, vidrio, plástico, etc): ";
    std::getline(std::cin, categoria);

    std::cout << "Ingrese el precio por kilo: $";
    std::cin >> precio;

    std::cout << "Ingrese la cantidad en kilos: ";
    std::cin >> cantidad;

    std::cout << "¿Necesita limpieza? (s/n): ";
    std::cin >> necesitaLimpieza;
    limpieza = (necesitaLimpieza == 's' || necesitaLimpieza == 'S');

    std::cout << "Ingrese tiempo de descomposición (en años): ";
    std::cin >> tiempoDescomposicion;

    std::cout << "Ingrese el bonus de reciclaje (0-1): ";
    std::cin >> bonus;

    // Crear y mostrar el material
    MaterialReciclable nuevoMaterial(nombre, cantidad, precio, limpieza, 
                                   categoria, tiempoDescomposicion, bonus);
    
    std::cout << "\n=== MATERIAL REGISTRADO ===\n";
    nuevoMaterial.mostrarDatos();
}

void registrarNuevaRecoleccion(SistemaGestion& sistema) {
    std::string nombreRecolector, tipoMaterial;
    float cantidad;

    std::cout << "\n=== REGISTRO DE RECOLECCIÓN ===\n";
    
    limpiarBuffer();
    std::cout << "Ingrese el nombre del recolector: ";
    std::getline(std::cin, nombreRecolector);

    std::cout << "Ingrese el tipo de material: ";
    std::getline(std::cin, tipoMaterial);

    std::cout << "Ingrese la cantidad en kilos: ";
    std::cin >> cantidad;

    std::cout << "\nRegistrando recolección...\n"
              << "Recolector: " << nombreRecolector << "\n"
              << "Material: " << tipoMaterial << "\n"
              << "Cantidad: " << cantidad << " kg\n"
              << "\n¡Recolección registrada con éxito!\n";
}

int main() {
    // Crear el sistema
    SistemaGestion sistema;
    
    // Variables para el menú
    int opcionPrincipal;
    int opcionSecundaria;

    // Crear algunos datos de ejemplo
    std::cout << "Inicializando el sistema...\n";
    
    // Crear centros de ejemplo
    CentroAcopio centro1("Centro Norte", "Av. Principal 123", 1000.0, 
                        "Lunes a Sábado: 8:00 - 17:00");
    CentroAcopio centro2("Centro Sur", "Calle 45 #678", 800.0, 
                        "Lunes a Viernes: 9:00 - 18:00");
    
    sistema.agregarCentroAcopio(centro1);
    sistema.agregarCentroAcopio(centro2);
    
    // Crear recolectores de ejemplo
    Recolector recolector1("Juan Pérez", "Zona Norte");
    recolector1.agregarMaterialEspecializado("PET");
    recolector1.setRating(4);
    
    Recolector recolector2("María García", "Zona Sur");
    recolector2.agregarMaterialEspecializado("Papel");
    recolector2.setRating(5);
    
    sistema.registrarRecolector(recolector1);
    sistema.registrarRecolector(recolector2);

    // Menú principal
    do {
        limpiarPantalla();
        opcionPrincipal = mostrarMenuPrincipal();

        switch(opcionPrincipal) {
            case 1: // Centros de Acopio
                do {
                    opcionSecundaria = menuCentrosAcopio();
                    switch(opcionSecundaria) {
                        case 1:
                            std::cout << sistema.generarReporteGlobal() << std::endl;
                            break;
                        case 2:
                            std::cout << "\nFuncionalidad en desarrollo...\n";
                            break;
                        case 3:
                            std::cout << "\nFuncionalidad en desarrollo...\n";
                            break;
                    }
                    if(opcionSecundaria != 4) {
                        pausarPantalla();
                    }
                } while(opcionSecundaria != 4);
                break;

            case 2: // Recolectores
                do {
                    opcionSecundaria = menuRecolectores();
                    switch(opcionSecundaria) {
                        case 1:
                            recolector1.mostrarPerfil();
                            recolector2.mostrarPerfil();
                            break;
                        case 2:
                            std::cout << "\nFuncionalidad en desarrollo...\n";
                            break;
                        case 3:
                            std::cout << "\nFuncionalidad en desarrollo...\n";
                            break;
                        case 4:
                            std::cout << "\nFuncionalidad en desarrollo...\n";
                            break;
                    }
                    if(opcionSecundaria != 5) {
                        pausarPantalla();
                    }
                } while(opcionSecundaria != 5);
                break;

            case 3: // Registrar nuevo material
                registrarNuevoMaterial(sistema);
                pausarPantalla();
                break;

            case 4: // Registrar recolección
                registrarNuevaRecoleccion(sistema);
                pausarPantalla();
                break;

            case 5: // Reportes
                do {
                    opcionSecundaria = menuReportes();
                    switch(opcionSecundaria) {
                        case 1:
                            sistema.calcularEstadisticasGenerales();
                            std::cout << sistema.generarReporteGlobal() << std::endl;
                            break;
                        case 2:
                            sistema.mostrarCatalogoMateriales();
                            break;
                        case 3:
                            recolector1.mostrarPerfil();
                            recolector2.mostrarPerfil();
                            break;
                    }
                    if(opcionSecundaria != 4) {
                        pausarPantalla();
                    }
                } while(opcionSecundaria != 4);
                break;

            case 6: // Salir
                std::cout << "\n¡Gracias por usar el sistema!\n"
                         << "Programa realizado por: [Tu Nombre]\n"
                         << "Materia: Programación Orientada a Objetos\n"
                         << "Profesor: [Nombre del Profesor]\n"
                         << "Fecha: [Fecha de Entrega]\n";
                break;
        }

    } while(opcionPrincipal != 6);

    return 0;
}

#endif // MAIN_CPP