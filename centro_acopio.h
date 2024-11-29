#ifndef CENTRO_ACOPIO_H
#define CENTRO_ACOPIO_H

#include "material_reciclable.h"
#include "registro_procesamiento.h"
#include "recolector.h"

#define MAX_INVENTARIO 100
#define MAX_RECOLECTORES 20
#define MAX_PROCESAMIENTOS 200

class CentroAcopio {
private:
    char nombre[50];
    char ubicacion[50];
    float capacidadMaxima;
    float capacidadActual;
    char horario[30];
    MaterialReciclable inventario[MAX_INVENTARIO];
    int numInventario;
    Recolector recolectoresAsignados[MAX_RECOLECTORES];
    int numRecolectores;
    RegistroProcesamiento historialProcesamientos[MAX_PROCESAMIENTOS];
    int numProcesamientos;

public:
    CentroAcopio(const char* _nombre = "", const char* _ubicacion = "",
                 float _capacidadMaxima = 0.0, const char* _horario = "") {
        strncpy(nombre, _nombre, 49);
        nombre[49] = '\0';
        strncpy(ubicacion, _ubicacion, 49);
        ubicacion[49] = '\0';
        capacidadMaxima = _capacidadMaxima;
        capacidadActual = 0.0;
        strncpy(horario, _horario, 29);
        horario[29] = '\0';
        numInventario = 0;
        numRecolectores = 0;
        numProcesamientos = 0;
    }

    bool recibirMaterial(const MaterialReciclable& material) {
        if (numInventario < MAX_INVENTARIO) {
            float nuevaCantidad = capacidadActual + material.getCantidad();
            if (nuevaCantidad <= capacidadMaxima) {
                inventario[numInventario] = material;
                numInventario++;
                capacidadActual = nuevaCantidad;
                return true;
            }
        }
        return false;
    }

    bool procesarLote(const char* tipoMaterial, float cantidad) {
        if (cantidad <= 0) return false;

        float cantidadProcesada = 0;
        for (int i = 0; i < numInventario; i++) {
            if (strcmp(inventario[i].getNombre(), tipoMaterial) == 0) {
                float cantidadDisponible = inventario[i].getCantidad();
                if (cantidadDisponible >= cantidad) {
                    inventario[i].setCantidad(cantidadDisponible - cantidad);
                    cantidadProcesada = cantidad;
                    capacidadActual -= cantidad;
                    break;
                }
            }
        }

        if (cantidadProcesada > 0 && numProcesamientos < MAX_PROCESAMIENTOS) {
            historialProcesamientos[numProcesamientos] = RegistroProcesamiento(
                "Fecha actual",
                tipoMaterial,
                cantidadProcesada,
                0.9
            );
            numProcesamientos++;
            return true;
        }
        return false;
    }

    bool asignarRecolector(const Recolector& recolector) {
        if (numRecolectores < MAX_RECOLECTORES) {
            recolectoresAsignados[numRecolectores] = recolector;
            numRecolectores++;
            return true;
        }
        return false;
    }

    void mostrarInformacion() const {
        std::cout << "\n=== Información del Centro de Acopio ==="
                 << "\nNombre: " << nombre
                 << "\nUbicación: " << ubicacion
                 << "\nHorario: " << horario
                 << "\nCapacidad: " << capacidadActual << "/" << capacidadMaxima << " kg"
                 << "\nRecolectores asignados: " << numRecolectores
                 << "\nEficiencia de procesamiento: " 
                 << (calcularEficienciaProcesamiento() * 100) << "%"
                 << std::endl;

        if (numInventario > 0) {
            std::cout << "\nInventario actual:";
            for (int i = 0; i < numInventario; i++) {
                std::cout << "\n- " << inventario[i].getNombre() 
                         << ": " << inventario[i].getCantidad() << " kg";
            }
            std::cout << std::endl;
        }
    }

    float calcularEficienciaProcesamiento() const {
        if (numProcesamientos == 0) return 0.0;
        float eficienciaTotal = 0.0;
        for (int i = 0; i < numProcesamientos; i++) {
            eficienciaTotal += historialProcesamientos[i].getEficiencia();
        }
        return eficienciaTotal / numProcesamientos;
    }

    // Getters
    const char* getNombre() const { return nombre; }
    const char* getUbicacion() const { return ubicacion; }
    float getCapacidadMaxima() const { return capacidadMaxima; }
    float getCapacidadActual() const { return capacidadActual; }
    const char* getHorario() const { return horario; }
};

#endif