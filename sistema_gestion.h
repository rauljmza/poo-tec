#ifndef SISTEMA_GESTION_H
#define SISTEMA_GESTION_H

#include "centro_acopio.h"
#include "recolector.h"
#include "material_reciclable.h"

/* Límites máximos del sistema */
#define MAX_CENTROS 10
#define MAX_RECOLECTORES 20
#define MAX_MATERIALES_CATALOGO 30

/* 
 * Clase SistemaGestion
 * Sistema central que coordina centros de acopio, recolectores 
 * y el catálogo de materiales reciclables.
 */
class SistemaGestion {
private:
    CentroAcopio centros[MAX_CENTROS];
    int numCentros;
    Recolector recolectores[MAX_RECOLECTORES];
    int numRecolectores;
    MaterialReciclable catalogoMateriales[MAX_MATERIALES_CATALOGO];
    int numMaterialesCatalogo;

public:
    /* Constructor: inicializa el sistema con materiales básicos */
    SistemaGestion() {
        numCentros = 0;
        numRecolectores = 0;
        numMaterialesCatalogo = 0;
        
        agregarMaterialCatalogo(MaterialReciclable("PET", 0, 15.50, true, "Plástico", 450, 0.1));
        agregarMaterialCatalogo(MaterialReciclable("Vidrio", 0, 8.75, true, "Vidrio", 4000, 0.15));
        agregarMaterialCatalogo(MaterialReciclable("Papel", 0, 5.25, false, "Papel", 1, 0.05));
    }

    /* Métodos principales del sistema */
    bool agregarCentroAcopio(const CentroAcopio& centro) {
        if (numCentros < MAX_CENTROS) {
            centros[numCentros] = centro;
            numCentros++;
            std::cout << "Centro de acopio agregado: " << centro.getNombre() << std::endl;
            return true;
        }
        return false;
    }

    bool registrarRecolector(const Recolector& recolector) {
        if (numRecolectores < MAX_RECOLECTORES) {
            recolectores[numRecolectores] = recolector;
            numRecolectores++;
            std::cout << "Recolector registrado: " << recolector.getNombre() << std::endl;
            return true;
        }
        return false;
    }

    bool agregarMaterialCatalogo(const MaterialReciclable& material) {
        if (numMaterialesCatalogo < MAX_MATERIALES_CATALOGO) {
            catalogoMateriales[numMaterialesCatalogo] = material;
            numMaterialesCatalogo++;
            return true;
        }
        return false;
    }

    bool asignarRecolectorACentro(const char* nombreRecolector, const char* nombreCentro) {
        for (int i = 0; i < numCentros; i++) {
            if (strcmp(centros[i].getNombre(), nombreCentro) == 0) {
                for (int j = 0; j < numRecolectores; j++) {
                    if (strcmp(recolectores[j].getNombre(), nombreRecolector) == 0) {
                        return centros[i].asignarRecolector(recolectores[j]);
                    }
                }
            }
        }
        return false;
    }

    /* Métodos para reportes y estadísticas */
    void calcularEstadisticasGenerales() const;
    void mostrarCatalogoMateriales() const;

    /* Métodos de acceso */
    size_t getTotalCentros() const { return numCentros; }
    size_t getTotalRecolectores() const { return numRecolectores; }
    size_t getTotalMaterialesCatalogo() const { return numMaterialesCatalogo; }
};

#endif