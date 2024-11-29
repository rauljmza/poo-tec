#ifndef REGISTRO_RECOLECCION_H
#define REGISTRO_RECOLECCION_H

#include <iostream>
#include <string.h>

/*
 * Clase RegistroRecoleccion
 * 
 * La implementación de un sistema de registro para la documentación 
 * de las actividades de recolección de materiales. Esta clase facilita
 * el almacenamiento y la gestión de información relacionada con cada
 * evento de recolección en el sistema.
 */
class RegistroRecoleccion {
private:
    /* 
     * Arreglo de caracteres para la documentación de la fecha.
     * La asignación de 20 caracteres permite el almacenamiento de fechas
     * en formato "YYYY-MM-DD HH:MM:SS", con reserva del último espacio
     * para el terminador nulo '\0'.
     */
    char fecha[20];

    /* 
     * Arreglo de caracteres para la clasificación del material.
     * La asignación de 30 caracteres permite la descripción detallada
     * del tipo de material, con reserva del último espacio para
     * el terminador nulo '\0'.
     */
    char tipoMaterial[30];

    /* 
     * Valor flotante para la especificación de la cantidad recolectada.
     * La utilización del tipo float permite la representación de 
     * fracciones de kilogramos.
     */
    float cantidad;

    /* 
     * Arreglo de caracteres para la especificación de la ubicación.
     * La asignación de 50 caracteres facilita el almacenamiento de
     * direcciones detalladas, con reserva del último espacio para
     * el terminador nulo '\0'.
     */
    char ubicacion[50];
    
public:
    /* 
     * Constructor predeterminado para la inicialización de un registro vacío.
     * La inicialización de los arreglos de caracteres con el terminador nulo
     * en la primera posición garantiza strings válidos y vacíos.
     */
    RegistroRecoleccion() {
        fecha[0] = '\0';
        tipoMaterial[0] = '\0';
        cantidad = 0.0;
        ubicacion[0] = '\0';
    }

    /* 
     * Constructor para la creación de un registro completo.
     * La implementación de strncpy asegura la copia segura de strings
     * con limitación de longitud para la prevención de desbordamientos.
     */
    RegistroRecoleccion(const char* _fecha, const char* _tipoMaterial,
                       float _cantidad, const char* _ubicacion) {
        // Copia segura de la fecha con limitación a 19 caracteres
        strncpy(fecha, _fecha, 19);
        fecha[19] = '\0';  // Garantía de terminación correcta del string
        
        // Copia segura del tipo de material con limitación a 29 caracteres
        strncpy(tipoMaterial, _tipoMaterial, 29);
        tipoMaterial[29] = '\0';
        
        cantidad = _cantidad;
        
        // Copia segura de la ubicación con limitación a 49 caracteres
        strncpy(ubicacion, _ubicacion, 49);
        ubicacion[49] = '\0';
    }
    
    /* 
     * Método para la visualización de la información completa del registro
     * en la consola. El calificador const garantiza que no se realizarán
     * modificaciones al objeto durante la visualización.
     */
    void mostrarDetalle() const {
        std::cout << "\n=== Detalle de Recolección ==="
                 << "\nFecha: " << fecha
                 << "\nMaterial: " << tipoMaterial
                 << "\nCantidad: " << cantidad << " kg"
                 << "\nUbicación: " << ubicacion << std::endl;
    }
    
    // Métodos de acceso con calificador const para la garantía
    // de integridad de los datos
    const char* getFecha() const { return fecha; }
    const char* getTipoMaterial() const { return tipoMaterial; }
    float getCantidad() const { return cantidad; }
    const char* getUbicacion() const { return ubicacion; }

    /* 
     * Sobrecarga del operador de asignación para la copia segura
     * de todos los atributos entre objetos de la clase.
     * La implementación incluye verificación de auto-asignación y
     * manejo seguro de strings mediante strncpy.
     */
    RegistroRecoleccion& operator=(const RegistroRecoleccion& otro) {
        if (this != &otro) {  // Verificación de auto-asignación
            // Copia segura de strings con sus respectivas limitaciones
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

#endif // REGISTRO_RECOLECCION_H