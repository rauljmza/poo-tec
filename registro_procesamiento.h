#ifndef REGISTRO_PROCESAMIENTO_H
#define REGISTRO_PROCESAMIENTO_H

#include <iostream>
#include <string.h>

/*
 * Clase RegistroProcesamiento
 * 
 * Estructuración para el registro de los procesos aplicados a los materiales
 * reciclables. Esta clase permite dar seguimiento a cada etapa del
 * procesamiento (recolección y reciclaje) de materiales en el sistema.
 */
class RegistroProcesamiento {
private:
    /* 
     * Arreglo de caracteres para el almacenamiento de la fecha.
     * El tamaño de 20 caracteres permite fechas en formato:
     * "YYYY-MM-DD HH:MM:SS", con espacio final para '\0'.
     */
    char fecha[20];

    /* 
     * Arreglo de caracteres para el tipo de material procesado.
     * El tamaño de 30 caracteres permite nombres descriptivos,
     * con espacio final para '\0'.
     */
    char tipoMaterial[30];

    /* 
     * Valor numérico decimal para la cantidad de material procesado
     * en kilogramos.
     */
    float cantidadProcesada;

    /* 
     * Valor decimal entre 0.0 y 1.0 que indica el porcentaje
     * de eficiencia del proceso.
     */
    float eficiencia;

public:
    /* 
     * Constructor básico que crea un registro vacío.
     * Inicializa los strings como vacíos y los números en cero.
     */
    RegistroProcesamiento() {
        fecha[0] = '\0';
        tipoMaterial[0] = '\0';
        cantidadProcesada = 0.0;
        eficiencia = 0.0;
    }

    /* 
     * Constructor que crea un registro con toda la información.
     * El uso de strncpy evita problemas de desbordamiento al copiar los textos.
     */
    RegistroProcesamiento(const char* _fecha, const char* _tipoMaterial,
                         float _cantidadProcesada, float _eficiencia) {
        // Copia segura del texto de la fecha
        strncpy(fecha, _fecha, 19);
        fecha[19] = '\0';
        
        // Copia segura del tipo de material
        strncpy(tipoMaterial, _tipoMaterial, 29);
        tipoMaterial[29] = '\0';
        
        cantidadProcesada = _cantidadProcesada;
        // La eficiencia debe estar entre 0 y 1
        eficiencia = (_eficiencia >= 0 && _eficiencia <= 1) ? _eficiencia : 0;
    }

    /* 
     * Método para el cálculo del rendimiento efectivo del proceso.
     * Multiplica la cantidad procesada por el factor de eficiencia.
     */
    float calcularRendimiento() const {
        return cantidadProcesada * eficiencia;
    }

    /* 
     * Método para la presentación de la información del proceso
     * en la pantalla.
     */
    void mostrarDetalle() const {
        std::cout << "\n=== Detalle de Procesamiento ==="
                 << "\nFecha: " << fecha
                 << "\nMaterial: " << tipoMaterial
                 << "\nCantidad procesada: " << cantidadProcesada << " kg"
                 << "\nEficiencia: " << (eficiencia * 100) << "%"
                 << "\nRendimiento efectivo: " << calcularRendimiento() << " kg" 
                 << std::endl;
    }

    // Métodos para obtener los valores almacenados
    const char* getFecha() const { return fecha; }
    const char* getTipoMaterial() const { return tipoMaterial; }
    float getCantidadProcesada() const { return cantidadProcesada; }
    float getEficiencia() const { return eficiencia; }
};

#endif // REGISTRO_PROCESAMIENTO_H