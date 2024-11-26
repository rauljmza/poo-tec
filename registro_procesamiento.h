#ifndef REGISTRO_PROCESAMIENTO_H
#define REGISTRO_PROCESAMIENTO_H

#include <string>
#include <iostream>

class RegistroProcesamiento {
private:
    std::string fecha;            // Fecha del procesamiento
    std::string tipoMaterial;     // Tipo de material procesado
    float cantidadProcesada;      // Cantidad procesada en kg
    float eficiencia;             // Eficiencia del procesamiento (0.0 - 1.0)

public:
    // Constructor
    RegistroProcesamiento(std::string _fecha, std::string _tipoMaterial,
                         float _cantidadProcesada, float _eficiencia) 
        : fecha(_fecha), tipoMaterial(_tipoMaterial), 
          cantidadProcesada(_cantidadProcesada) {
        // Validamos la eficiencia en el constructor
        eficiencia = (_eficiencia >= 0 && _eficiencia <= 1) ? _eficiencia : 0;
    }

    // Método para calcular el rendimiento del procesamiento
    float calcularRendimiento() const {
        return cantidadProcesada * eficiencia;
    }

    // Método para mostrar los detalles del procesamiento
    void mostrarDetalle() const {
        std::cout << "\n=== Detalle de Procesamiento ==="
                 << "\nFecha: " << fecha
                 << "\nMaterial: " << tipoMaterial
                 << "\nCantidad procesada: " << cantidadProcesada << " kg"
                 << "\nEficiencia: " << (eficiencia * 100) << "%"
                 << "\nRendimiento efectivo: " << calcularRendimiento() << " kg" 
                 << std::endl;
    }

    // Getters
    std::string getFecha() const { return fecha; }
    std::string getTipoMaterial() const { return tipoMaterial; }
    float getCantidadProcesada() const { return cantidadProcesada; }
    float getEficiencia() const { return eficiencia; }

    // No incluimos setters ya que un registro no debe modificarse una vez creado
};

#endif // REGISTRO_PROCESAMIENTO_H