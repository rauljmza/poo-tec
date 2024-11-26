#ifndef RECOLECTOR_H
#define RECOLECTOR_H

#include <string>
#include <vector>
#include "material_reciclable.h"
#include "registro_recoleccion.h"

// Forward declaration para evitar dependencia circular
class CentroAcopio;

class Recolector {
private:
    std::string nombre;                                    // Nombre del recolector
    std::string zona;                                      // Zona de trabajo asignada
    std::vector<std::string> materialesEspecializados;     // Materiales en los que está especializado
    float totalRecolectado;                               // Total en kg recolectados
    int rating;                                           // Calificación del recolector (1-5)
    std::vector<MaterialReciclable> materialesActuales;    // Materiales en posesión
    std::vector<RegistroRecoleccion> historialRecolecciones; // Historial de recolecciones

public:
    // Constructor
    Recolector(std::string _nombre, std::string _zona) 
        : nombre(_nombre), zona(_zona), totalRecolectado(0.0), rating(0) {}

    // Método para agregar un material especializado
    void agregarMaterialEspecializado(const std::string& material) {
        materialesEspecializados.push_back(material);
    }

    // Método para registrar una nueva recolección
    bool registrarRecoleccion(const MaterialReciclable& material) {
        if (material.getCantidad() > 0) {
            materialesActuales.push_back(material);
            totalRecolectado += material.getCantidad();
            
            // Crear y guardar el registro
            RegistroRecoleccion registro(
                "Fecha actual", // En sistema real sería fecha actual
                material.getNombre(),
                material.getCantidad(),
                zona
            );
            historialRecolecciones.push_back(registro);
            return true;
        }
        return false;
    }

    // Método para transferir materiales a un centro de acopio
    bool transferirMaterialACentro(CentroAcopio& centro);  // Declaración adelantada

    // Método para calcular la eficiencia del recolector
    float calcularEficiencia() const {
        if (historialRecolecciones.empty()) {
            return 0.0;
        }
        return totalRecolectado / historialRecolecciones.size();
    }

    // Método para generar reporte de actividad
    std::string generarReporteActividad() const {
        std::string reporte = "\n=== Reporte de Actividad ===";
        reporte += "\nRecolector: " + nombre;
        reporte += "\nZona: " + zona;
        reporte += "\nRating: " + std::to_string(rating) + "/5";
        reporte += "\nTotal recolectado: " + std::to_string(totalRecolectado) + " kg";
        reporte += "\nEficiencia: " + std::to_string(calcularEficiencia()) + " kg/recolección";

        reporte += "\n\nMateriales especializados:";
        for (const auto& material : materialesEspecializados) {
            reporte += "\n- " + material;
        }

        reporte += "\n\nMateriales actuales:";
        for (const auto& material : materialesActuales) {
            reporte += "\n- " + material.getNombre() + ": " + 
                      std::to_string(material.getCantidad()) + " kg";
        }

        return reporte;
    }

    // Método para mostrar el perfil del recolector
    void mostrarPerfil() const {
        std::cout << "\n=== Perfil del Recolector ==="
                 << "\nNombre: " << nombre
                 << "\nZona: " << zona
                 << "\nRating: " << rating << "/5"
                 << "\nTotal recolectado: " << totalRecolectado << " kg"
                 << "\nEficiencia: " << calcularEficiencia() << " kg/recolección"
                 << "\n\nMateriales especializados:";
        
        for (const auto& material : materialesEspecializados) {
            std::cout << "\n- " << material;
        }
        std::cout << std::endl;
    }

    // Getters
    std::string getNombre() const { return nombre; }
    std::string getZona() const { return zona; }
    float getTotalRecolectado() const { return totalRecolectado; }
    int getRating() const { return rating; }

    // Setters con validación
    void setNombre(const std::string& _nombre) { nombre = _nombre; }
    void setZona(const std::string& _zona) { zona = _zona; }
    void setRating(int _rating) {
        if (_rating >= 1 && _rating <= 5) {
            rating = _rating;
        }
    }
};

// La implementación de transferirMaterialACentro se hará en el archivo .cpp
// o después de la definición de CentroAcopio para evitar dependencias circulares

#endif // RECOLECTOR_H