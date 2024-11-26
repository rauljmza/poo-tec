#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <iostream>

class Material {
protected:
    std::string nombre;        // Nombre del material
    float cantidad;           // Cantidad en kilogramos
    float precioBase;        // Precio por kilogramo
    
public:
    // Constructor con valores por defecto
    Material(std::string _nombre = "", float _cantidad = 0.0, float _precioBase = 0.0) {
        nombre = _nombre;
        cantidad = _cantidad;
        precioBase = _precioBase;
    }
    
    // Destructor virtual
    virtual ~Material() = default;
        
    // Método virtual para calcular el valor del material
    virtual float calcularValor() const {
        return cantidad * precioBase;
    }
        
    // Método virtual para mostrar información del material
    virtual void mostrarDatos() const {
        std::cout << "\nInformación del Material"
                 << "\nNombre: " << nombre
                 << "\nCantidad: " << cantidad << " kg"
                 << "\nPrecio base: $" << precioBase << "/kg"
                 << "\nValor total: $" << calcularValor() << std::endl;
    }
        
    // Getters
    std::string getNombre() const { return nombre; }
    float getCantidad() const { return cantidad; }
    float getPrecioBase() const { return precioBase; }
        
    // Setters
    void setNombre(std::string _nombre) { nombre = _nombre; }
    void setCantidad(float _cantidad) {
        if (_cantidad >= 0) cantidad = _cantidad;
    }
    void setPrecioBase(float _precio) {
        if (_precio >= 0) precioBase = _precio;
    }
};

#endif // MATERIAL_H