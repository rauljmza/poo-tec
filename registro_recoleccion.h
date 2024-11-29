#ifndef REGISTRO_RECOLECCION_H
#define REGISTRO_RECOLECCION_H

#include <iostream>
#include <string.h>

class RegistroRecoleccion {
private:
    char fecha[20];
    char tipoMaterial[30];
    float cantidad;
    char ubicacion[50];
    
public:
    // Constructor por defecto
    RegistroRecoleccion() {
        fecha[0] = '\0';
        tipoMaterial[0] = '\0';
        cantidad = 0.0;
        ubicacion[0] = '\0';
    }

    // Constructor con parámetros
    RegistroRecoleccion(const char* _fecha, const char* _tipoMaterial,
                       float _cantidad, const char* _ubicacion) {
        strncpy(fecha, _fecha, 19);
        fecha[19] = '\0';
        
        strncpy(tipoMaterial, _tipoMaterial, 29);
        tipoMaterial[29] = '\0';
        
        cantidad = _cantidad;
        
        strncpy(ubicacion, _ubicacion, 49);
        ubicacion[49] = '\0';
    }
    
    void mostrarDetalle() const {
        std::cout << "\n=== Detalle de Recolección ==="
                 << "\nFecha: " << fecha
                 << "\nMaterial: " << tipoMaterial
                 << "\nCantidad: " << cantidad << " kg"
                 << "\nUbicación: " << ubicacion << std::endl;
    }
    
    // Getters
    const char* getFecha() const { return fecha; }
    const char* getTipoMaterial() const { return tipoMaterial; }
    float getCantidad() const { return cantidad; }
    const char* getUbicacion() const { return ubicacion; }

    // Operador de asignación
    RegistroRecoleccion& operator=(const RegistroRecoleccion& otro) {
        if (this != &otro) {
            strncpy(fecha, otro.fecha, 19);
            fecha[19] = '\0';
            strncpy(tipoMaterial, otro.tipoMaterial, 29);
            tipoMaterial[29] = '\0';
            cantidad = otro.cantidad;
            strncpy(ubicacion, otro.ubicacion, 49);
            ubicacion[49] = '\0';
        }
        return *this;
    }
};

#endif