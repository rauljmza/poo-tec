#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <limits>
#include "sistema_gestion.h"
#include "material_reciclable.h"
#include "centro_acopio.h"
#include "recolector.h"

/*
    Limpieza de pantalla de la consola: compatible con Windows y MacOS.
*/
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/*
    La limpieza del buffer previene errores de lectura de datos.
*/
void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
    Pausa de la ejecucción del programa para esperar acciones del usuario.
*/
void pausarPantalla() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.get();
}

/*
    Despliegue del menú principal donde el usuario elige opciones a ejecutar.
*/
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

/*
    Registro de un nuevo material en el sistema.
    Entrada de datos: nombre, categoría, precio, cantidad, limpieza, tiempo de descomposición, bonus.
*/
void registrarNuevoMaterial(SistemaGestion& sistema) {
    char nombre[50], categoria[30];
    float precio, cantidad;
    int tiempoDescomposicion;
    char necesitaLimpieza;
    bool limpieza;
    float bonus;

    std::cout << "\n=== REGISTRO DE NUEVO MATERIAL ===\n";

    // Captura de datos del nuevo material.
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

    // Creación y registro del material en el sistema.
    MaterialReciclable nuevoMaterial(nombre, cantidad, precio, limpieza, 
                                   categoria, tiempoDescomposicion, bonus);
    
    if (sistema.agregarMaterialCatalogo(nuevoMaterial)) {
        std::cout << "\n=== MATERIAL REGISTRADO ===\n";
        nuevoMaterial.mostrarDatos();
    } else {
        std::cout << "\nError: No se pudo registrar el material.\n";
    }
}

/*
    Registro de una nueva recolección en el sistema.
    Entrada de datos: nombre del recolector, tipo de material, cantidad.
*/
void registrarRecoleccion(SistemaGestion& sistema) {
    // Declaración de variables para el almacenamiento de datos de recolección.
    char nombreRecolector[50];
    char tipoMaterial[50];
    float cantidad;

    std::cout << "\n=== REGISTRO DE RECOLECCIÓN ===\n";
    
    // Captura de datos de la recolección
    limpiarBuffer();
    std::cout << "Nombre del recolector: ";
    std::cin.getline(nombreRecolector, 49);

    std::cout << "Tipo de material: ";
    std::cin.getline(tipoMaterial, 49);

    std::cout << "Cantidad en kilos: ";
    std::cin >> cantidad;

    // Confirmación del éxito en el registro.
    std::cout << "\nRegistrando recolección...\n"
              << "Recolector: " << nombreRecolector << "\n"
              << "Material: " << tipoMaterial << "\n"
              << "Cantidad: " << cantidad << " kg\n"
              << "\n¡Recolección registrada con éxito!\n";
}

/*
    Función principal ejecutable del programa.
    Control del flujo principal y gestión del menú.
*/
int main() {
    SistemaGestion sistema;
    int opcion;
    
    // Datos iniciales de ejemplo.
    CentroAcopio centro1("Centro Norte", "Av. Principal 123", 1000.0, 
                        "Lun-Sab: 8:00-17:00");
    sistema.agregarCentroAcopio(centro1);
    
    Recolector recolector1("Juan Pérez", "Zona Norte");
    recolector1.agregarMaterialEspecializado("PET");
    recolector1.setRating(4);
    sistema.registrarRecolector(recolector1);

    // Ciclo principal del sistema.
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