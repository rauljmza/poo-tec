#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <limits>
#include "sistema_gestion.h"
#include "material_reciclable.h"
#include "centro_acopio.h"
#include "recolector.h"

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
    std::cin.get();
}

int mostrarMenuPrincipal() {
    int opcion;
    bool opcionValida = false;
    
    while(!opcionValida) {
        std::cout << "\n=== SISTEMA DE RECICLAJE BIOWAY ===\n"
                 << "1. Ver centros de acopio\n"
                 << "2. Ver recolectores\n"
                 << "3. Registrar nuevo material\n"
                 << "4. Registrar recolección\n"
                 << "5. Ver reportes\n"
                 << "6. Salir\n"
                 << "Opción: ";
        
        if(std::cin >> opcion && opcion >= 1 && opcion <= 6) {
            opcionValida = true;
        } else {
            std::cout << "\n¡Error! Seleccione opción válida (1-6)\n";
            limpiarBuffer();
            pausarPantalla();
            limpiarPantalla();
        }
    }
    return opcion;
}

void registrarNuevoMaterial(SistemaGestion& sistema) {
    char nombre[50], categoria[30];
    float precio, cantidad;
    int tiempoDescomposicion;
    char necesitaLimpieza;
    bool limpieza;
    float bonus;

    std::cout << "\n=== REGISTRO DE NUEVO MATERIAL ===\n";
    
    limpiarBuffer();
    std::cout << "Nombre del material: ";
    std::cin.getline(nombre, 49);

    std::cout << "Categoría: ";
    std::cin.getline(categoria, 29);

    std::cout << "Precio por kilo: $";
    std::cin >> precio;

    std::cout << "Cantidad en kilos: ";
    std::cin >> cantidad;

    std::cout << "¿Necesita limpieza? (s/n): ";
    std::cin >> necesitaLimpieza;
    limpieza = (necesitaLimpieza == 's' || necesitaLimpieza == 'S');

    std::cout << "Tiempo de descomposición (años): ";
    std::cin >> tiempoDescomposicion;

    std::cout << "Bonus de reciclaje (0-1): ";
    std::cin >> bonus;

    MaterialReciclable nuevoMaterial(nombre, cantidad, precio, limpieza, 
                                   categoria, tiempoDescomposicion, bonus);
    
    if (sistema.agregarMaterialCatalogo(nuevoMaterial)) {
        std::cout << "\n=== MATERIAL REGISTRADO ===\n";
        nuevoMaterial.mostrarDatos();
    } else {
        std::cout << "\nError: No se pudo registrar el material.\n";
    }
}

void registrarRecoleccion(SistemaGestion& sistema) {
    char nombreRecolector[50];
    char tipoMaterial[50];
    float cantidad;

    std::cout << "\n=== REGISTRO DE RECOLECCIÓN ===\n";
    
    limpiarBuffer();
    std::cout << "Nombre del recolector: ";
    std::cin.getline(nombreRecolector, 49);

    std::cout << "Tipo de material: ";
    std::cin.getline(tipoMaterial, 49);

    std::cout << "Cantidad en kilos: ";
    std::cin >> cantidad;

    std::cout << "\nRegistrando recolección...\n"
              << "Recolector: " << nombreRecolector << "\n"
              << "Material: " << tipoMaterial << "\n"
              << "Cantidad: " << cantidad << " kg\n"
              << "\n¡Recolección registrada con éxito!\n";
}

int main() {
    SistemaGestion sistema;
    int opcion;
    
    CentroAcopio centro1("Centro Norte", "Av. Principal 123", 1000.0, 
                        "Lun-Sab: 8:00-17:00");
    sistema.agregarCentroAcopio(centro1);
    
    Recolector recolector1("Juan Pérez", "Zona Norte");
    recolector1.agregarMaterialEspecializado("PET");
    recolector1.setRating(4);
    sistema.registrarRecolector(recolector1);

    do {
        opcion = mostrarMenuPrincipal();
        limpiarBuffer();

        switch(opcion) {
            case 1: {
                limpiarPantalla();
                std::cout << "\n=== CENTROS DE ACOPIO ===\n";
                sistema.calcularEstadisticasGenerales();
                pausarPantalla();
                break;
            }
            case 2: {
                limpiarPantalla();
                std::cout << "\n=== RECOLECTORES ===\n";
                recolector1.mostrarPerfil();
                pausarPantalla();
                break;
            }
            case 3: {
                limpiarPantalla();
                registrarNuevoMaterial(sistema);
                pausarPantalla();
                break;
            }
            case 4: {
                limpiarPantalla();
                registrarRecoleccion(sistema);
                pausarPantalla();
                break;
            }
            case 5: {
                limpiarPantalla();
                std::cout << "\n=== REPORTES ===\n";
                sistema.mostrarCatalogoMateriales();
                pausarPantalla();
                break;
            }
            case 6: {
                limpiarPantalla();
                std::cout << "¡Gracias por usar el sistema de gestión de residuos de BioWay!\n"
                         << "Programa realizado por: Raul Mendoza - CEO BioWay / A01712018\n";
                pausarPantalla();
                break;
            }
        }
    } while(opcion != 6);

    return 0;
}

#endif