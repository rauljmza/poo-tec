#ifndef MATERIAL_H
#define MATERIAL_H

#include <string.h>  // Necesario para funciones de manejo de strings como strncpy
#include <iostream>

/*
 * Clase Material
 * 
 * Representa un material genérico en el sistema de reciclaje.
 * Implementa la funcionalidad básica para manejar materiales,
 * incluyendo su identificación, cantidad y precio. Sirve como clase base
 * para tipos más específicos de materiales como los reciclables.
 */
class Material {
protected:
    /* 
     * Arreglo de caracteres que almacena el nombre del material.
     * Se usa un arreglo fijo de 50 caracteres en lugar de std::string 
     * para mantener compatibilidad con sistemas legacy y evitar problemas
     * de memoria dinámica. El último carácter (índice 49) se reserva 
     * para el terminador nulo '\0'.
     */
    char nombre[50];    
    
    /* 
     * Almacena la cantidad del material en kilogramos.
     * Se usa float para permitir fracciones de kilogramo.
     */
    float cantidad;     
    
    /* 
     * Define el precio por kilogramo del material.
     * Se usa float para manejar valores decimales en la moneda.
     */
    float precioBase;   
    
public:
    /* 
     * Constructor que inicializa un nuevo material.
     * 
     * El parámetro _nombre es un puntero constante a char (const char*) 
     * que representa una cadena de caracteres. Se usa este tipo en lugar
     * de string para mejor compatibilidad y rendimiento.
     * 
     * strncpy se usa para copiar de forma segura el string de entrada,
     * limitando la copia a 49 caracteres para dejar espacio para el
     * terminador nulo. Esto previene desbordamientos de buffer.
     */
    Material(const char* _nombre = "", float _cantidad = 0.0, float _precioBase = 0.0) {
        // Copia hasta 49 caracteres del nombre, dejando espacio para el terminador nulo
        strncpy(nombre, _nombre, 49);
        nombre[49] = '\0';  // Garantiza que el string esté terminado correctamente
        
        cantidad = _cantidad;
        precioBase = _precioBase;
    }
    
    /* 
     * Calcula y retorna el valor total del material.
     * El calificador virtual permite que las clases derivadas
     * sobreescriban este método con su propia implementación.
     */
    virtual float calcularValor() const {
        return cantidad * precioBase;
    }
    
    /* 
     * Muestra en consola la información completa del material.
     * El calificador virtual permite personalizar la visualización
     * en clases derivadas.
     */
    virtual void mostrarDatos() const {
        std::cout << "\nInformación del Material"
                 << "\nNombre: " << nombre     // nombre se imprime como un C-string
                 << "\nCantidad: " << cantidad << " kg"
                 << "\nPrecio base: $" << precioBase << "/kg"
                 << "\nValor total: $" << calcularValor() << std::endl;
    }
    
    /* 
     * Retorna un puntero constante (const char*) al arreglo nombre.
     * El calificador const después del paréntesis indica que este método
     * no modificará ningún miembro de la clase.
     * 
     * Se retorna un puntero constante para:
     * 1. Evitar modificaciones accidentales al string original
     * 2. Permitir acceso de solo lectura al nombre
     * 3. Mantener la eficiencia al no copiar el string
     */
    const char* getNombre() const { return nombre; }
    
    /* 
     * Retorna la cantidad actual en kilogramos.
     * El calificador const garantiza que el método es de solo lectura.
     */
    float getCantidad() const { return cantidad; }
    
    /* 
     * Retorna el precio base por kilogramo.
     * El calificador const garantiza que el método es de solo lectura.
     */
    float getPrecioBase() const { return precioBase; }
    
    /* 
     * Actualización del nombre del material de forma segura.
     * 
     * El parámetro es un puntero constante a char (const char*) que
     * representa el nuevo nombre. La constancia del puntero asegura
     * que no se modifique el string original.
     * 
     * strncpy es ysadi para prevenir desbordamientos de buffer:
     * - Copia como máximo 49 caracteres
     * - El destino (nombre) tiene espacio para 50 caracteres
     * - El último carácter se reserva para el terminador nulo
     */
    void setNombre(const char* _nombre) {
        strncpy(nombre, _nombre, 49);  // Copia segura limitada
        nombre[49] = '\0';             // Garantiza terminación correcta del string
    }
    
    /* 
     * Actualiza la cantidad del material.
     * Incluye validación para evitar cantidades negativas.
     */
    void setCantidad(float _cantidad) {
        if (_cantidad >= 0) cantidad = _cantidad;
    }
    
    /* 
     * Actualiza el precio base por kilogramo.
     * Incluye validación para evitar precios negativos.
     */
    void setPrecioBase(float _precio) {
        if (_precio >= 0) precioBase = _precio;
    }
};

#endif // MATERIAL_H