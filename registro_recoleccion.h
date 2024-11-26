#ifndef REGISTRO_RECOLECCION_H
#define REGISTRO_RECOLECCION_H

#include <string>
#include <iostream>

class RegistroRecoleccion {
private:
    std::string fecha;            // Fecha de la recolección
    std::string tipoMaterial;     // Tipo de material recolectado
    float cantidad;               // Cantidad recolectada en kg
    std::string ubicacion;        // Ubicación donde se realizó la recolección
    
public:
    // Constructor
    RegistroRecoleccion(std::string _fecha, std::string _tipoMaterial, 
                       float _cantidad, std::string _ubicacion) 
        : fecha(_fecha), tipoMaterial(_tipoMaterial), 
          cantidad(_cantidad), ubicacion(_ubicacion) {}
    
    // Método para mostrar los detalles del registro
    void mostrarDetalle() const {
        std::cout << "\n=== Detalle de Recolección ==="
                 << "\nFecha: " << fecha
                 << "\nMaterial: " << tipoMaterial
                 << "\nCantidad: " << cantidad << " kg"
                 << "\nUbicación: " << ubicacion << std::endl;
    }
    
    // Getters
    std::string getFecha() const { return fecha; }
    std::string getTipoMaterial() const { return tipoMaterial; }
    float getCantidad() const { return cantidad; }
    std::string getUbicacion() const { return ubicacion; }

    // No incluimos setters porque un registro no debería modificarse una vez creado
};

#endif // REGISTRO_RECOLECCION_H