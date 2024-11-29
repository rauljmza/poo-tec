#ifndef RECOLECTOR_H
#define RECOLECTOR_H

#include "material_reciclable.h"
#include "registro_recoleccion.h"

#define MAX_MATERIALES 10
#define MAX_REGISTROS 50
#define MAX_ESPECIALIZACIONES 5

class Recolector {
private:
    char nombre[50];
    char zona[50];
    char materialesEspecializados[MAX_ESPECIALIZACIONES][30];
    int numEspecializaciones;
    float totalRecolectado;
    int rating;
    MaterialReciclable materialesActuales[MAX_MATERIALES];
    int numMaterialesActuales;
    RegistroRecoleccion historialRecolecciones[MAX_REGISTROS];
    int numRegistros;

public:
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

    bool agregarMaterialEspecializado(const char* material) {
        if (numEspecializaciones < MAX_ESPECIALIZACIONES) {
            strncpy(materialesEspecializados[numEspecializaciones], material, 29);
            materialesEspecializados[numEspecializaciones][29] = '\0';
            numEspecializaciones++;
            return true;
        }
        return false;
    }

    bool registrarRecoleccion(const MaterialReciclable& material) {
        if (material.getCantidad() > 0 && 
            numMaterialesActuales < MAX_MATERIALES &&
            numRegistros < MAX_REGISTROS) {
            
            materialesActuales[numMaterialesActuales] = material;
            numMaterialesActuales++;
            totalRecolectado += material.getCantidad();
            
            // Usando constructor con parámetros de RegistroRecoleccion
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

    float calcularEficiencia() const {
        if (numRegistros == 0) return 0.0;
        return totalRecolectado / numRegistros;
    }

    void mostrarPerfil() const {
        std::cout << "\n=== Perfil del Recolector ==="
                 << "\nNombre: " << nombre
                 << "\nZona: " << zona
                 << "\nRating: " << rating << "/5"
                 << "\nTotal recolectado: " << totalRecolectado << " kg"
                 << "\nEficiencia: " << calcularEficiencia() << " kg/recolección"
                 << "\n\nMateriales especializados:";
        
        for (int i = 0; i < numEspecializaciones; i++) {
            std::cout << "\n- " << materialesEspecializados[i];
        }
        std::cout << std::endl;

        // Mostrar materiales actuales
        if (numMaterialesActuales > 0) {
            std::cout << "\nMateriales actuales:";
            for (int i = 0; i < numMaterialesActuales; i++) {
                std::cout << "\n- " << materialesActuales[i].getNombre() 
                         << ": " << materialesActuales[i].getCantidad() << " kg";
            }
            std::cout << std::endl;
        }
    }

    // Getters
    const char* getNombre() const { return nombre; }
    const char* getZona() const { return zona; }
    float getTotalRecolectado() const { return totalRecolectado; }
    int getRating() const { return rating; }

    // Setters
    void setNombre(const char* _nombre) {
        strncpy(nombre, _nombre, 49);
        nombre[49] = '\0';
    }
    
    void setZona(const char* _zona) {
        strncpy(zona, _zona, 49);
        zona[49] = '\0';
    }
    
    void setRating(int _rating) {
        if (_rating >= 1 && _rating <= 5) rating = _rating;
    }
};

#endif