
# BioWay - Sistema de Gestión de Reciclables

Este proyecto en C++ es parte de BioWay, una empresa dedicada a la recolección de reciclables a domicilio con el objetivo de dignificar la labor de los recolectores y mejorar la gestión de residuos. Este programa permite instanciar varios tipos de materiales reciclables, asignarlos a recolectores específicos y proporcionarles las direcciones de los centros de acopio, incluyendo horarios y capacidades.

## Funcionalidades

El sistema permite:
- Crear y gestionar **materiales reciclables**, incluyendo detalles como tipo, cantidad, si requieren limpieza, precio por kilo, facilidad de reciclaje y tiempo de descomposición.
- Registrar **recolectores** con especialización en tipos específicos de materiales, y sus registros de recolección y calificaciones.
- Administrar **centros de acopio**, incluyendo su ubicación, capacidad y horarios de operación.


## Requisitos

- El proyecto está desarrollado en **C++ estándar**, por lo que es compatible con cualquier sistema operativo que tenga un compilador C++.

## Instrucciones de Compilación y Ejecución

Para compilar y ejecutar el programa en la consola:

1. **Compilar**: Ejecuta el siguiente comando en la terminal para compilar el programa.
   ```bash
   g++ empleado.h empresa.h main.cpp -o programa
   ```

2. **Ejecutar**:
   - En **Linux**:
     ```bash
     ./programa
     ```
   - En **Windows**:
     ```cmd
     programa.exe
     ```

## Para qué sirve

Este programa sirve para:
- Identificar y clasificar tipos de materiales reciclables y recolectores que los manejan.
- Proveer a los recolectores información de centros de acopio, incluyendo dirección y horario.
- Mejorar la gestión de residuos y apoyar la recolección responsable.

## Limitaciones

Este programa **no está diseñado para**:
- Funcionar con una interfaz gráfica, ya que solo corre en la consola.
- Integrarse directamente con sistemas externos o bases de datos, dado que es una aplicación básica en C++ sin conexión a servicios externos.
- Operaciones en tiempo real ni monitoreo automático de recolectores y centros de acopio.

## Estado de Desarrollo

Actualmente, el proyecto está en **desarrollo temprano**. La primera versión incluye la creación de las clases para materiales reciclables, recolectores y centros de acopio. En versiones futuras, se espera añadir más funcionalidades y optimizaciones.
