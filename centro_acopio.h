#ifndef CENTRO_ACOPIO_H
#define CENTRO_ACOPIO_H

#include "material_reciclable.h"
#include "registro_procesamiento.h"
#include "recolector.h"

/* 
 * Constantes para la definición de los límites máximos en el centro.
 * Estas constantes son fundamentales para la prevención de desbordamientos
 * y el control de recursos del centro de acopio.
 */
#define MAX_INVENTARIO 100      // Capacidad máxima de materiales diferentes
#define MAX_RECOLECTORES 20     // Número máximo de recolectores asignados
#define MAX_PROCESAMIENTOS 200  // Límite de registros históricos

/*
 * Clase CentroAcopio
 * 
 * Esta clase representa un centro físico para el acopio y procesamiento
 * de materiales reciclables. El centro actúa como un punto central 
 * donde los recolectores entregan materiales y estos son procesados
 * para su reciclaje posterior.
 */
class CentroAcopio {
private:
    /* 
     * Arreglo de caracteres para el nombre del centro.
     * El nombre facilita la identificación única del centro
     * dentro del sistema de reciclaje.
     */
    char nombre[50];

    /* 
     * Arreglo de caracteres para la dirección física del centro.
     * La ubicación es esencial para la logística de recolección
     * y entrega de materiales.
     */
    char ubicacion[50];

    /* 
     * Valor decimal que establece el límite máximo de almacenamiento
     * en kilogramos que el centro puede manejar.
     */
    float capacidadMaxima;

    /* 
     * Valor decimal que registra la cantidad actual de material
     * almacenado en kilogramos. Nunca debe superar la capacidadMaxima.
     */
    float capacidadActual;

    /* 
     * Arreglo de caracteres para el registro del horario de operación.
     * El formato recomendado es "Día-Día: HH:MM-HH:MM".
     */
    char horario[30];

    /* 
     * Arreglo de objetos MaterialReciclable para el control
     * del inventario actual del centro. Cada posición representa
     * un tipo diferente de material almacenado.
     */
    MaterialReciclable inventario[MAX_INVENTARIO];
    int numInventario;

    /* 
     * Arreglo de objetos Recolector para el control de personal
     * asignado al centro. Permite dar seguimiento a quiénes pueden
     * entregar material.
     */
    Recolector recolectoresAsignados[MAX_RECOLECTORES];
    int numRecolectores;

    /* 
     * Arreglo de objetos RegistroProcesamiento para el seguimiento
     * histórico de todos los procesamientos realizados en el centro.
     */
    RegistroProcesamiento historialProcesamientos[MAX_PROCESAMIENTOS];
    int numProcesamientos;

public:
    /* 
     * Constructor que establece las características iniciales del centro.
     * Todos los arreglos comienzan vacíos y los contadores en cero.
     */
    CentroAcopio(const char* _nombre = "", const char* _ubicacion = "",
                 float _capacidadMaxima = 0.0, const char* _horario = "") {
        // Copia segura del nombre con límite de 49 caracteres
        strncpy(nombre, _nombre, 49);
        nombre[49] = '\0';
        
        // Copia segura de la ubicación con límite de 49 caracteres
        strncpy(ubicacion, _ubicacion, 49);
        ubicacion[49] = '\0';
        
        capacidadMaxima = _capacidadMaxima;
        capacidadActual = 0.0;
        
        // Copia segura del horario con límite de 29 caracteres
        strncpy(horario, _horario, 29);
        horario[29] = '\0';
        
        // Inicialización de contadores
        numInventario = 0;
        numRecolectores = 0;
        numProcesamientos = 0;
    }

    /* 
     * Método para la recepción de nuevos materiales en el centro.
     * Este método realiza múltiples validaciones para garantizar
     * que el centro puede recibir el material de forma segura:
     * 1. Verifica que haya espacio en el inventario
     * 2. Confirma que no se exceda la capacidad máxima
     */
    bool recibirMaterial(const MaterialReciclable& material) {
        // Verificación del espacio disponible en el arreglo de inventario
        if (numInventario < MAX_INVENTARIO) {
            // Cálculo de la nueva capacidad después de recibir el material
            float nuevaCantidad = capacidadActual + material.getCantidad();
            
            // Verificación de que no se exceda la capacidad máxima
            if (nuevaCantidad <= capacidadMaxima) {
                inventario[numInventario] = material;
                numInventario++;
                capacidadActual = nuevaCantidad;
                return true;
            }
        }
        return false;
    }

    /* 
     * Método para el procesamiento de un lote específico de material.
     * Este proceso implica:
     * 1. La búsqueda del material en el inventario
     * 2. La reducción de la cantidad procesada
     * 3. El registro del procesamiento en el historial
     */
    bool procesarLote(const char* tipoMaterial, float cantidad) {
        // Validación inicial de la cantidad
        if (cantidad <= 0) return false;

        float cantidadProcesada = 0;
        
        // Búsqueda del material específico en el inventario
        for (int i = 0; i < numInventario; i++) {
            if (strcmp(inventario[i].getNombre(), tipoMaterial) == 0) {
                float cantidadDisponible = inventario[i].getCantidad();
                if (cantidadDisponible >= cantidad) {
                    // Actualización del inventario después del procesamiento
                    inventario[i].setCantidad(cantidadDisponible - cantidad);
                    cantidadProcesada = cantidad;
                    capacidadActual -= cantidad;
                    break;
                }
            }
        }

        // Registro del procesamiento si fue exitoso
        if (cantidadProcesada > 0 && numProcesamientos < MAX_PROCESAMIENTOS) {
            historialProcesamientos[numProcesamientos] = RegistroProcesamiento(
                "Fecha actual",
                tipoMaterial,
                cantidadProcesada,
                0.9  // Eficiencia estándar del proceso
            );
            numProcesamientos++;
            return true;
        }
        return false;
    }

    /* 
     * Método para la asignación de un nuevo recolector al centro.
     * La asignación permite al recolector entregar materiales
     * en este centro específico.
     */
    bool asignarRecolector(const Recolector& recolector) {
        if (numRecolectores < MAX_RECOLECTORES) {
            recolectoresAsignados[numRecolectores] = recolector;
            numRecolectores++;
            return true;
        }
        return false;
    }

    /* 
     * Método para la presentación del estado actual del centro.
     * Muestra información detallada sobre:
     * - Datos generales del centro
     * - Estado de capacidad
     * - Cantidad de recolectores
     * - Eficiencia de procesamiento
     * - Inventario actual
     */
    void mostrarInformacion() const {
        std::cout << "\n=== Información del Centro de Acopio ==="
                 << "\nNombre: " << nombre
                 << "\nUbicación: " << ubicacion
                 << "\nHorario: " << horario
                 << "\nCapacidad: " << capacidadActual << "/" 
                 << capacidadMaxima << " kg"
                 << "\nRecolectores asignados: " << numRecolectores
                 << "\nEficiencia de procesamiento: " 
                 << (calcularEficienciaProcesamiento() * 100) << "%"
                 << std::endl;

        // Presentación del inventario si existe
        if (numInventario > 0) {
            std::cout << "\nInventario actual:";
            for (int i = 0; i < numInventario; i++) {
                std::cout << "\n- " << inventario[i].getNombre() 
                         << ": " << inventario[i].getCantidad() << " kg";
            }
            std::cout << std::endl;
        }
    }

    /* 
     * Método para el cálculo de la eficiencia promedio
     * de todos los procesamientos realizados en el centro.
     */
    float calcularEficienciaProcesamiento() const {
        if (numProcesamientos == 0) return 0.0;
        
        float eficienciaTotal = 0.0;
        for (int i = 0; i < numProcesamientos; i++) {
            eficienciaTotal += historialProcesamientos[i].getEficiencia();
        }
        return eficienciaTotal / numProcesamientos;
    }

    // Métodos para la obtención de información (getters)
    const char* getNombre() const { return nombre; }
    const char* getUbicacion() const { return ubicacion; }
    float getCapacidadMaxima() const { return capacidadMaxima; }
    float getCapacidadActual() const { return capacidadActual; }
    const char* getHorario() const { return horario; }
};

#endif // CENTRO_ACOPIO_H