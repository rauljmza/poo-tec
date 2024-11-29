#ifndef MATERIAL_RECICLABLE_H
#define MATERIAL_RECICLABLE_H

#include "material.h"
#include <string.h>

class MaterialReciclable : public Material {
private:
    bool limpiezaRequerida;
    char categoria[30];
    int tiempoDescomposicion;
    float bonusReciclaje;
    char estado[20];
    
public:
    MaterialReciclable(const char* _nombre = "", float _cantidad = 0.0, 
                      float _precioBase = 0.0, bool _limpiezaRequerida = false,
                      const char* _categoria = "", int _tiempoDesc = 0,
                      float _bonusReciclaje = 0.0)
        : Material(_nombre, _cantidad, _precioBase) {
        limpiezaRequerida = _limpiezaRequerida;
        strncpy(categoria, _categoria, 29);
        categoria[29] = '\0';
        tiempoDescomposicion = _tiempoDesc;
        bonusReciclaje = _bonusReciclaje;
        strcpy(estado, "nuevo");
    }
    
    float calcularValor() const {
        float valorBase = Material::calcularValor();
        return valorBase * (1.0 + bonusReciclaje);
    }
    
    void mostrarDatos() const {
        Material::mostrarDatos();
        std::cout << "Categoría: " << categoria
                 << "\nRequiere limpieza: " << (limpiezaRequerida ? "Sí" : "No")
                 << "\nTiempo de descomposición: " << tiempoDescomposicion << " años"
                 << "\nBonus de reciclaje: " << (bonusReciclaje * 100) << "%"
                 << "\nEstado: " << estado << std::endl;
    }
    
    bool validarCalidad() const {
        return !limpiezaRequerida || strcmp(estado, "procesado") == 0;
    }
    
    void procesarMaterial() {
        if (validarCalidad()) {
            strcpy(estado, "procesado");
        } else {
            strcpy(estado, "rechazado");
        }
    }
    
    const char* getNombre() const { return Material::getNombre(); }
    float getCantidad() const { return Material::getCantidad(); }
    const char* getCategoria() const { return categoria; }
    const char* getEstado() const { return estado; }
    bool getLimpiezaRequerida() const { return limpiezaRequerida; }
    int getTiempoDescomposicion() const { return tiempoDescomposicion; }
    float getBonusReciclaje() const { return bonusReciclaje; }

    MaterialReciclable& operator=(const MaterialReciclable& otro) {
        if (this != &otro) {
            Material::operator=(otro);
            limpiezaRequerida = otro.limpiezaRequerida;
            strncpy(categoria, otro.categoria, 29);
            categoria[29] = '\0';
            tiempoDescomposicion = otro.tiempoDescomposicion;
            bonusReciclaje = otro.bonusReciclaje;
            strncpy(estado, otro.estado, 19);
            estado[19] = '\0';
        }
        return *this;
    }
};

#endif