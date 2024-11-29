#ifndef MATERIAL_H
#define MATERIAL_H

#include <string.h>
#include <iostream>

class Material {
protected:
    char nombre[50];
    float cantidad;
    float precioBase;
    
public:
    Material(const char* _nombre = "", float _cantidad = 0.0, float _precioBase = 0.0) {
        strncpy(nombre, _nombre, 49);
        nombre[49] = '\0';
        cantidad = _cantidad;
        precioBase = _precioBase;
    }
    
    float calcularValor() const {
        return cantidad * precioBase;
    }
        
    void mostrarDatos() const {
        std::cout << "\nInformación del Material"
                 << "\nNombre: " << nombre
                 << "\nCantidad: " << cantidad << " kg"
                 << "\nPrecio base: $" << precioBase << "/kg"
                 << "\nValor total: $" << calcularValor() << std::endl;
    }
        
    const char* getNombre() const { return nombre; }
    float getCantidad() const { return cantidad; }
    float getPrecioBase() const { return precioBase; }
        
    void setNombre(const char* _nombre) {
        strncpy(nombre, _nombre, 49);
        nombre[49] = '\0';
    }
    
    void setCantidad(float _cantidad) {
        if (_cantidad >= 0) cantidad = _cantidad;
    }
    
    void setPrecioBase(float _precio) {
        if (_precio >= 0) precioBase = _precio;
    }
};

#endif