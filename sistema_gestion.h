#ifndef SISTEMA_GESTION_H
#define SISTEMA_GESTION_H

#include <string>
#include <vector>
#include "centro_acopio.h"
#include "recolector.h"
#include "material_reciclable.h"

class SistemaGestion {
private:
    std::vector<CentroAcopio> centros;              // Centros de acopio registrados
    std::vector<Recolector> recolectores;           // Recolectores registrados
    std::vector<MaterialReciclable> catalogoMateriales;  // Catálogo de materiales

public:
    // Constructor que inicializa el catálogo con materiales básicos
    SistemaGestion() {
        // Inicializar catálogo con materiales básicos
        catalogoMateriales.push_back(
            MaterialReciclable("PET", 0, 15.50, true, "Plástico", 450, 0.1));
        catalogoMateriales.push_back(
            MaterialReciclable("Vidrio", 0, 8.75, true, "Vidrio", 4000, 0.15));
        catalogoMateriales.push_back(
            MaterialReciclable("Papel", 0, 5.25, false, "Papel", 1, 0.05));
    }

    // Método para agregar un nuevo centro de acopio
    void agregarCentroAcopio(const CentroAcopio& centro) {
        centros.push_back(centro);
        std::cout << "Centro de acopio agregado: " << centro.getNombre() << std::endl;
    }

    // Método para registrar un nuevo recolector
    void registrarRecolector(const Recolector& recolector) {
        recolectores.push_back(recolector);
        std::cout << "Recolector registrado: " << recolector.getNombre() << std::endl;
    }

    // Método para asignar un recolector a un centro
    bool asignarRecolectorACentro(const std::string& nombreRecolector, const std::string& nombreCentro) {
        for (auto& centro : centros) {
            if (centro.getNombre() == nombreCentro) {
                for (const auto& recolector : recolectores) {
                    if (recolector.getNombre() == nombreRecolector) {
                        return centro.asignarRecolector(recolector);
                    }
                }
            }
        }
        return false;
    }

    // Método para buscar el centro más cercano
    CentroAcopio* buscarCentroMasCercano(const std::string& ubicacion) {
        // Versión simplificada: retorna el primer centro disponible
        if (!centros.empty()) {
            return &centros[0];
        }
        return nullptr;
    }

    // Método para generar reporte global
    std::string generarReporteGlobal() const {
        std::string reporte = "\n====== REPORTE GLOBAL DEL SISTEMA ======\n";

        // Resumen de centros de acopio
        reporte += "\nCENTROS DE ACOPIO (" + std::to_string(centros.size()) + ")";
        reporte += "\n----------------------------------";
        for (const auto& centro : centros) {
            reporte += "\n\nCentro: " + centro.getNombre();
            reporte += "\nUbicación: " + centro.getUbicacion();
            reporte += "\nCapacidad utilizada: " + 
                      std::to_string((centro.getCapacidadActual() / 
                                    centro.getCapacidadMaxima()) * 100) + "%";
        }

        // Resumen de recolectores
        reporte += "\n\nRECOLECTORES (" + std::to_string(recolectores.size()) + ")";
        reporte += "\n----------------------------------";
        for (const auto& recolector : recolectores) {
            reporte += "\n\nNombre: " + recolector.getNombre();
            reporte += "\nZona: " + recolector.getZona();
            reporte += "\nTotal recolectado: " + 
                      std::to_string(recolector.getTotalRecolectado()) + " kg";
        }

        return reporte;
    }

    // Método para calcular estadísticas generales
    void calcularEstadisticasGenerales() const {
        float totalMaterialRecolectado = 0;
        float capacidadTotalSistema = 0;
        float capacidadUtilizada = 0;

        // Calcular totales
        for (const auto& recolector : recolectores) {
            totalMaterialRecolectado += recolector.getTotalRecolectado();
        }

        for (const auto& centro : centros) {
            capacidadTotalSistema += centro.getCapacidadMaxima();
            capacidadUtilizada += centro.getCapacidadActual();
        }

        // Mostrar estadísticas
        std::cout << "\n=== Estadísticas Generales del Sistema ==="
                 << "\nTotal de centros de acopio: " << centros.size()
                 << "\nTotal de recolectores: " << recolectores.size()
                 << "\nTotal material recolectado: " << totalMaterialRecolectado << " kg"
                 << "\nCapacidad total del sistema: " << capacidadTotalSistema << " kg"
                 << "\nCapacidad utilizada: " << capacidadUtilizada << " kg"
                 << "\nPorcentaje de utilización: " 
                 << (capacidadTotalSistema > 0 ? 
                     (capacidadUtilizada / capacidadTotalSistema * 100) : 0) 
                 << "%" << std::endl;
    }

    // Método para mostrar catálogo de materiales
    void mostrarCatalogoMateriales() const {
        std::cout << "\n=== Catálogo de Materiales ==="
                 << "\nMateriales disponibles:" << std::endl;
        
        for (const auto& material : catalogoMateriales) {
            material.mostrarDatos();
        }
    }

    // Getters para estadísticas básicas
    size_t getTotalCentros() const { return centros.size(); }
    size_t getTotalRecolectores() const { return recolectores.size(); }
    size_t getTotalMaterialesCatalogo() const { return catalogoMateriales.size(); }
};

#endif // SISTEMA_GESTION_H