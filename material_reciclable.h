#ifndef MATERIAL_RECICLABLE_H
#define MATERIAL_RECICLABLE_H

#include "material.h"
#include <string.h>

/*
 * Clase MaterialReciclable
 * 
 * La extensión de la clase base Material para la representación específica
 * de materiales reciclables en el sistema. La implementación incluye 
 * atributos adicionales para el control del proceso de reciclaje y 
 * el estado del material.
 */
class MaterialReciclable : public Material {
private:
    /* 
     * Indicador booleano para la determinación de si el material requiere un proceso
     * de limpieza antes de su procesamiento.
     */
    bool limpiezaRequerida;

    /* 
     * Arreglo de caracteres para la categorización del material.
     * La asignación de 30 caracteres permite la clasificación detallada,
     * reservando el último espacio para el terminador nulo '\0'.
     */
    char categoria[30];

    /* 
     * Valor entero para la especificación del tiempo de descomposición
     * del material en años.
     */
    int tiempoDescomposicion;

    /* 
     * Valor flotante para la especificación del beneficio adicional
     * por reciclaje, expresado como un multiplicador (ejemplo: 0.1 = 10%).
     */
    float bonusReciclaje;

    /* 
     * Arreglo de caracteres para el seguimiento del estado actual del material.
     * La limitación a 20 caracteres permite estados como "nuevo", "procesado",
     * "rechazado", reservando el último espacio para el terminador nulo.
     */
    char estado[20];
    
public:
    /* 
     * Constructor con parámetros por defecto.
     * La implementación de strncpy asegura la copia segura de strings
     * con limitación de longitud para prevención de desbordamientos.
     */
    MaterialReciclable(const char* _nombre = "", float _cantidad = 0.0, 
                      float _precioBase = 0.0, bool _limpiezaRequerida = false,
                      const char* _categoria = "", int _tiempoDesc = 0,
                      float _bonusReciclaje = 0.0)
        : Material(_nombre, _cantidad, _precioBase) {
        limpiezaRequerida = _limpiezaRequerida;
        
        // Copia segura de la categoría con limitación a 29 caracteres
        strncpy(categoria, _categoria, 29);
        categoria[29] = '\0';  // Garantía de terminación correcta del string
        
        tiempoDescomposicion = _tiempoDesc;
        bonusReciclaje = _bonusReciclaje;
        
        // Estado inicial establecido como "nuevo"
        strncpy(estado, "nuevo", 19);
        estado[19] = '\0';
    }
    
    /* 
     * Sobreescritura del método calcularValor para la inclusión
     * del bonus por reciclaje en el cálculo del valor total.
     */
    float calcularValor() const override {
        float valorBase = Material::calcularValor();
        return valorBase * (1.0 + bonusReciclaje);
    }
    
    /* 
     * Sobreescritura del método mostrarDatos para la inclusión
     * de la información específica de materiales reciclables.
     */
    void mostrarDatos() const override {
        Material::mostrarDatos();
        std::cout << "Categoría: " << categoria
                 << "\nRequisito de limpieza: " << (limpiezaRequerida ? "Sí" : "No")
                 << "\nTiempo de descomposición: " << tiempoDescomposicion << " años"
                 << "\nBonus de reciclaje: " << (bonusReciclaje * 100) << "%"
                 << "\nEstado actual: " << estado << std::endl;
    }
    
    /* 
     * Verificación de la calidad del material basada en su estado
     * y requisitos de limpieza.
     */
    bool validarCalidad() const {
        return !limpiezaRequerida || strcmp(estado, "procesado") == 0;
    }
    
    /* 
     * Actualización del estado del material según el resultado
     * de la validación de calidad.
     */
    void procesarMaterial() {
        if (validarCalidad()) {
            strncpy(estado, "procesado", 19);
        } else {
            strncpy(estado, "rechazado", 19);
        }
        estado[19] = '\0';  // Garantía de terminación correcta del string
    }

    // Métodos de acceso a los atributos
    const char* getCategoria() const { return categoria; }
    const char* getEstado() const { return estado; }
    bool getLimpiezaRequerida() const { return limpiezaRequerida; }
    int getTiempoDescomposicion() const { return tiempoDescomposicion; }
    float getBonusReciclaje() const { return bonusReciclaje; }

    /* 
     * Sobrecarga del operador de asignación para la copia segura
     * de todos los atributos de la clase.
     */
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

#endif // MATERIAL_RECICLABLE_H