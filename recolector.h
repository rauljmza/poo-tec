#ifndef RECOLECTOR_H
#define RECOLECTOR_H

#include "material_reciclable.h"
#include "registro_recoleccion.h"

/* 
 * Constantes para la definición de límites en los arreglos.
 * Estas constantes ayudan a prevenir desbordamientos y facilitan
 * futuros cambios en los tamaños.
 */
#define MAX_MATERIALES 10
#define MAX_REGISTROS 50
#define MAX_ESPECIALIZACIONES 5

/*
 * Clase Recolector
 * 
 * Esta clase representa a una persona dedicada a la recolección
 * de materiales reciclables. Contiene toda la información necesaria
 * para el seguimiento de su trabajo y desempeño.
 */
class Recolector {
private:
    /* 
     * Arreglo de caracteres para el nombre del recolector.
     * Tamaño: 50 caracteres, incluye espacio para '\0'.
     */
    char nombre[50];

    /* 
     * Arreglo de caracteres para la zona de trabajo asignada.
     * Tamaño: 50 caracteres, incluye espacio para '\0'.
     */
    char zona[50];

    /* 
     * Matriz para el almacenamiento de los tipos de materiales
     * en los que el recolector está especializado.
     * Primera dimensión: número máximo de especializaciones.
     * Segunda dimensión: longitud máxima de cada nombre (30 caracteres).
     */
    char materialesEspecializados[MAX_ESPECIALIZACIONES][30];
    int numEspecializaciones;

    /* 
     * Valor decimal que acumula el total de kilos recolectados
     * a lo largo del tiempo.
     */
    float totalRecolectado;

    /* 
     * Valor entero para la calificación del desempeño.
     * Rango: 1 a 5, donde 5 es la mejor calificación.
     */
    int rating;

    /* 
     * Arreglo de objetos MaterialReciclable para el control
     * de los materiales actualmente en posesión del recolector.
     */
    MaterialReciclable materialesActuales[MAX_MATERIALES];
    int numMaterialesActuales;

    /* 
     * Arreglo de objetos RegistroRecoleccion para el historial
     * de todas las recolecciones realizadas.
     */
    RegistroRecoleccion historialRecolecciones[MAX_REGISTROS];
    int numRegistros;

public:
    /* 
     * Constructor que crea un nuevo recolector.
     * Inicializa todos los contadores en cero y copia de forma
     * segura los datos del nombre y zona.
     */
    Recolector(const char* _nombre = "", const char* _zona = "") {
        strncpy(nombre, _nombre, 49);
        nombre[49] = '\0';
        
        strncpy(zona, _zona, 49);
        zona[49] = '\0';
        
        totalRecolectado = 0.0;
        rating = 0;
        numEspecializaciones = 0;
        numMaterialesActuales = 0;
        numRegistros = 0;
    }

    /* 
     * Método para la adición de un nuevo material a la lista
     * de especializaciones del recolector.
     */
    bool agregarMaterialEspecializado(const char* material) {
        if (numEspecializaciones < MAX_ESPECIALIZACIONES) {
            // Copia segura del nombre del material
            strncpy(materialesEspecializados[numEspecializaciones], material, 29);
            materialesEspecializados[numEspecializaciones][29] = '\0';
            numEspecializaciones++;
            return true;
        }
        return false;
    }

    /* 
     * Método para el registro de una nueva recolección.
     * Actualiza el inventario actual y el historial.
     */
    bool registrarRecoleccion(const MaterialReciclable& material) {
        // Verificación de límites y cantidad válida
        if (material.getCantidad() > 0 && 
            numMaterialesActuales < MAX_MATERIALES &&
            numRegistros < MAX_REGISTROS) {
            
            // Agregación del material al inventario
            materialesActuales[numMaterialesActuales] = material;
            numMaterialesActuales++;
            totalRecolectado += material.getCantidad();
            
            // Creación del registro histórico
            historialRecolecciones[numRegistros] = RegistroRecoleccion(
                "Fecha actual",
                material.getNombre(),
                material.getCantidad(),
                zona
            );
            numRegistros++;
            return true;
        }
        return false;
    }

    /* 
     * Método para el cálculo de la eficiencia del recolector
     * basado en la cantidad promedio por recolección.
     */
    float calcularEficiencia() const {
        if (numRegistros == 0) return 0.0;
        return totalRecolectado / numRegistros;
    }

    /* 
     * Método para la visualización del perfil completo del recolector
     * incluyendo estadísticas y materiales actuales.
     */
    void mostrarPerfil() const {
        std::cout << "\n=== Perfil del Recolector ==="
                 << "\nNombre: " << nombre
                 << "\nZona: " << zona
                 << "\nRating: " << rating << "/5"
                 << "\nTotal recolectado: " << totalRecolectado << " kg"
                 << "\nEficiencia: " << calcularEficiencia() << " kg/recolección"
                 << "\n\nMateriales especializados:";
        
        // Listado de las especializaciones del recolector
        for (int i = 0; i < numEspecializaciones; i++) {
            std::cout << "\n- " << materialesEspecializados[i];
        }
        std::cout << std::endl;

        // Presentación del inventario actual si existe
        if (numMaterialesActuales > 0) {
            std::cout << "\nMateriales actuales:";
            for (int i = 0; i < numMaterialesActuales; i++) {
                std::cout << "\n- " << materialesActuales[i].getNombre() 
                         << ": " << materialesActuales[i].getCantidad() << " kg";
            }
            std::cout << std::endl;
        }
    }

    // Métodos para la obtención de información (getters)
    
    /* 
     * Método para la obtención del nombre del recolector.
     * Retorna: Puntero constante al arreglo de caracteres del nombre.
     */
    const char* getNombre() const { return nombre; }
    
    /* 
     * Método para la obtención de la zona asignada.
     * Retorna: Puntero constante al arreglo de caracteres de la zona.
     */
    const char* getZona() const { return zona; }
    
    /* 
     * Método para la obtención del total recolectado.
     * Retorna: Valor decimal que representa los kilogramos totales.
     */
    float getTotalRecolectado() const { return totalRecolectado; }
    
    /* 
     * Método para la obtención de la calificación.
     * Retorna: Valor entero que representa el rating actual.
     */
    int getRating() const { return rating; }

    // Métodos para la modificación de información (setters)
    
    /* 
     * Método para la modificación del nombre del recolector.
     * La implementación incluye una copia segura mediante strncpy.
     */
    void setNombre(const char* _nombre) {
        strncpy(nombre, _nombre, 49);
        nombre[49] = '\0';  // Asegura la terminación correcta del string
    }
    
    /* 
     * Método para la modificación de la zona asignada.
     * La implementación incluye una copia segura mediante strncpy.
     */
    void setZona(const char* _zona) {
        strncpy(zona, _zona, 49);
        zona[49] = '\0';  // Asegura la terminación correcta del string
    }
    
    /* 
     * Método para la modificación del rating.
     * Incluye validación para asegurar un valor entre 1 y 5.
     */
    void setRating(int _rating) {
        if (_rating >= 1 && _rating <= 5) rating = _rating;
    }
};

#endif // RECOLECTOR_H