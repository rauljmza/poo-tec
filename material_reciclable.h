#ifndef MATERIAL_RECICLABLE_H  // Guarda de inclusión
#define MATERIAL_RECICLABLE_H

// Inclusiones necesarias
#include "material.h"           // Incluimos la clase base
#include <string>              // Para std::string

// Forward declarations si fueran necesarias
// (en este caso no las necesitamos)

class MaterialReciclable : public Material {
private:
    bool limpiezaRequerida;      // Indica si el material requiere limpieza
    std::string categoria;        // Categoría del material (papel, plástico, etc.)
    int tiempoDescomposicion;     // Tiempo de descomposición en años
    float bonusReciclaje;         // Bonificación adicional por reciclaje
    std::string estado;           // Estado actual del material reciclable
    
public:
    // Constructor con valores por defecto
    MaterialReciclable(std::string _nombre = "", float _cantidad = 0.0, 
                      float _precioBase = 0.0, bool _limpiezaRequerida = false,
                      std::string _categoria = "", int _tiempoDesc = 0,
                      float _bonusReciclaje = 0.0);
    
    // El resto de la declaración de métodos...
    void procesarMaterial();
    bool validarCalidad() const;
    float calcularValor() const override;
    void mostrarDatos() const override;
    
    // Getters
    bool getLimpiezaRequerida() const;
    std::string getCategoria() const;
    int getTiempoDescomposicion() const;
    float getBonusReciclaje() const;
    std::string getEstado() const;
    
    // Setters
    void setLimpiezaRequerida(bool _limpiezaRequerida);
    void setCategoria(std::string _categoria);
    void setTiempoDescomposicion(int _tiempo);
    void setBonusReciclaje(float _bonus);
    void setEstado(std::string _estado);
};

// Implementación de los métodos
inline MaterialReciclable::MaterialReciclable(std::string _nombre, float _cantidad, 
    float _precioBase, bool _limpiezaRequerida, std::string _categoria, 
    int _tiempoDesc, float _bonusReciclaje) 
    : Material(_nombre, _cantidad, _precioBase) {
    limpiezaRequerida = _limpiezaRequerida;
    categoria = _categoria;
    tiempoDescomposicion = _tiempoDesc;
    bonusReciclaje = _bonusReciclaje;
    estado = "nuevo";
}

inline void MaterialReciclable::procesarMaterial() {
    if (validarCalidad()) {
        estado = "procesado";
    } else {
        estado = "rechazado";
    }
}

inline bool MaterialReciclable::validarCalidad() const {
    return !limpiezaRequerida || estado == "procesado";
}

inline float MaterialReciclable::calcularValor() const {
    float valorBase = Material::calcularValor();
    return valorBase * (1.0 + bonusReciclaje);
}

inline void MaterialReciclable::mostrarDatos() const {
    Material::mostrarDatos();
    std::cout << "Categoría: " << categoria
             << "\nRequiere limpieza: " << (limpiezaRequerida ? "Sí" : "No")
             << "\nTiempo de descomposición: " << tiempoDescomposicion << " años"
             << "\nBonus de reciclaje: " << (bonusReciclaje * 100) << "%"
             << "\nEstado: " << estado << std::endl;
}

// Getters
inline bool MaterialReciclable::getLimpiezaRequerida() const { return limpiezaRequerida; }
inline std::string MaterialReciclable::getCategoria() const { return categoria; }
inline int MaterialReciclable::getTiempoDescomposicion() const { return tiempoDescomposicion; }
inline float MaterialReciclable::getBonusReciclaje() const { return bonusReciclaje; }
inline std::string MaterialReciclable::getEstado() const { return estado; }

// Setters
inline void MaterialReciclable::setLimpiezaRequerida(bool _limpiezaRequerida) {
    limpiezaRequerida = _limpiezaRequerida;
}

inline void MaterialReciclable::setCategoria(std::string _categoria) {
    categoria = _categoria;
}

inline void MaterialReciclable::setTiempoDescomposicion(int _tiempo) {
    if (_tiempo >= 0) tiempoDescomposicion = _tiempo;
}

inline void MaterialReciclable::setBonusReciclaje(float _bonus) {
    if (_bonus >= 0 && _bonus <= 1) bonusReciclaje = _bonus;
}

inline void MaterialReciclable::setEstado(std::string _estado) {
    estado = _estado;
}

#endif // MATERIAL_RECICLABLE_H