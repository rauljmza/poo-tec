#ifndef REGISTRO_PROCESAMIENTO_H
#define REGISTRO_PROCESAMIENTO_H

#include <iostream>
#include <string.h>

class RegistroProcesamiento {
private:
    char fecha[20];
    char tipoMaterial[30];
    float cantidadProcesada;
    float eficiencia;

public:
    // Constructor por defecto
    RegistroProcesamiento() {
        fecha[0] = '\0';
        tipoMaterial[0] = '\0';
        cantidadProcesada = 0.0;
        eficiencia = 0.0;
    }

    RegistroProcesamiento(const char* _fecha, const char* _tipoMaterial,
                         float _cantidadProcesada, float _eficiencia) {
        strncpy(fecha, _fecha, 19);
        fecha[19] = '\0';
        
        strncpy(tipoMaterial, _tipoMaterial, 29);
        tipoMaterial[29] = '\0';
        
        cantidadProcesada = _cantidadProcesada;
        eficiencia = (_eficiencia >= 0 && _eficiencia <= 1) ? _eficiencia : 0;
    }

    float calcularRendimiento() const {
        return cantidadProcesada * eficiencia;
    }

    void mostrarDetalle() const {
        std::cout << "\n=== Detalle de Procesamiento ==="
                 << "\nFecha: " << fecha
                 << "\nMaterial: " << tipoMaterial
                 << "\nCantidad procesada: " << cantidadProcesada << " kg"
                 << "\nEficiencia: " << (eficiencia * 100) << "%"
                 << "\nRendimiento efectivo: " << calcularRendimiento() << " kg" 
                 << std::endl;
    }

    // Getters con calificador const
    const char* getFecha() const { return fecha; }
    const char* getTipoMaterial() const { return tipoMaterial; }
    float getCantidadProcesada() const { return cantidadProcesada; }
    float getEficiencia() const { return eficiencia; }
};

#endif