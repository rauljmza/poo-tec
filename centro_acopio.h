#ifndef CENTRO_ACOPIO_H
#define CENTRO_ACOPIO_H

#include <string>
#include <vector>
#include <map>
#include "material_reciclable.h"
#include "registro_procesamiento.h"
#include "recolector.h"

class CentroAcopio {
private:
    std::string nombre;                                    // Nombre del centro
    std::string ubicacion;                                 // Ubicación del centro
    float capacidadMaxima;                                // Capacidad máxima en kg
    float capacidadActual;                                // Capacidad actual en kg
    std::string horario;                                  // Horario de operación
    std::vector<MaterialReciclable> inventario;           // Inventario de materiales
    std::vector<Recolector> recolectoresAsignados;        // Recolectores asignados
    std::vector<RegistroProcesamiento> historialProcesamientos; // Historial de procesamientos

public:
    // Constructor con lista de inicialización
    CentroAcopio(std::string _nombre, std::string _ubicacion,
                 float _capacidadMaxima, std::string _horario)
        : nombre(_nombre), ubicacion(_ubicacion), 
          capacidadMaxima(_capacidadMaxima), capacidadActual(0.0),
          horario(_horario) {}

    // Método para recibir material
    bool recibirMaterial(const MaterialReciclable& material) {
        float nuevaCantidad = capacidadActual + material.getCantidad();
        if (nuevaCantidad <= capacidadMaxima) {
            inventario.push_back(material);
            capacidadActual = nuevaCantidad;
            return true;
        }
        return false;
    }

    // Método para procesar un lote de material
    bool procesarLote(const std::string& tipoMaterial, float cantidad) {
        if (cantidad <= 0) {
            return false;
        }

        float cantidadProcesada = 0;
        for (auto& material : inventario) {
            if (material.getNombre() == tipoMaterial) {
                float cantidadDisponible = material.getCantidad();
                if (cantidadDisponible >= cantidad) {
                    material.setCantidad(cantidadDisponible - cantidad);
                    cantidadProcesada = cantidad;
                    capacidadActual -= cantidad;
                    break;
                }
            }
        }

        if (cantidadProcesada > 0) {
            RegistroProcesamiento registro(
                "Fecha actual",  // En sistema real: fecha actual
                tipoMaterial,
                cantidadProcesada,
                0.9  // Eficiencia ejemplo
            );
            historialProcesamientos.push_back(registro);
            return true;
        }
        return false;
    }

    // Método para asignar un recolector
    bool asignarRecolector(const Recolector& recolector) {
        recolectoresAsignados.push_back(recolector);
        return true;
    }

    // Método para generar reporte de inventario
    std::string generarReporteInventario() const {
        std::string reporte = "\n=== Reporte de Inventario ===";
        reporte += "\nCentro: " + nombre;
        reporte += "\nUbicación: " + ubicacion;
        reporte += "\nCapacidad: " + std::to_string(capacidadActual) + "/" + 
                  std::to_string(capacidadMaxima) + " kg";
        reporte += "\nHorario: " + horario;

        // Agrupamos los materiales por tipo
        std::map<std::string, float> resumenInventario;
        for (const auto& material : inventario) {
            resumenInventario[material.getNombre()] += material.getCantidad();
        }

        reporte += "\n\nInventario actual:";
        for (const auto& item : resumenInventario) {
            reporte += "\n- " + item.first + ": " + 
                      std::to_string(item.second) + " kg";
        }

        return reporte;
    }

    // Método para calcular eficiencia de procesamiento
    float calcularEficienciaProcesamiento() const {
        if (historialProcesamientos.empty()) {
            return 0.0;
        }

        float eficienciaTotal = 0.0;
        for (const auto& proceso : historialProcesamientos) {
            eficienciaTotal += proceso.getEficiencia();
        }
        return eficienciaTotal / historialProcesamientos.size();
    }

    // Método para mostrar información del centro
    void mostrarInformacion() const {
        std::cout << "\n=== Información del Centro de Acopio ==="
                 << "\nNombre: " << nombre
                 << "\nUbicación: " << ubicacion
                 << "\nHorario: " << horario
                 << "\nCapacidad: " << capacidadActual << "/" << capacidadMaxima << " kg"
                 << "\nRecolectores asignados: " << recolectoresAsignados.size()
                 << "\nEficiencia de procesamiento: " 
                 << (calcularEficienciaProcesamiento() * 100) << "%"
                 << std::endl;

        std::cout << "\nInventario actual:";
        for (const auto& material : inventario) {
            std::cout << "\n- " << material.getNombre() << ": " 
                     << material.getCantidad() << " kg";
        }
        std::cout << std::endl;
    }

    // Getters
    std::string getNombre() const { return nombre; }
    std::string getUbicacion() const { return ubicacion; }
    float getCapacidadMaxima() const { return capacidadMaxima; }
    float getCapacidadActual() const { return capacidadActual; }
    std::string getHorario() const { return horario; }

    // Setters con validación
    void setNombre(const std::string& _nombre) { nombre = _nombre; }
    void setUbicacion(const std::string& _ubicacion) { ubicacion = _ubicacion; }
    void setCapacidadMaxima(float _capacidad) {
        if (_capacidad >= capacidadActual) {
            capacidadMaxima = _capacidad;
        }
    }
    void setHorario(const std::string& _horario) { horario = _horario; }
};

#endif // CENTRO_ACOPIO_H