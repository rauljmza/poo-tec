#include<iostream>

#include "material.h"
#include "recolector.h"
#include "centroacopio.h"

int main(){
    MaterialReciclable plastico("PET",5.5,true,15.50,7,1000);
    plastico.mostrarDatos();
    std::cout << "\n";

    // Objeto Recolector
    Recolector recolector1("Esteban García","Centro","Plástico PET");
    recolector1.registrarRecoleccion(100.5);
    recolector1.setRating(4);
    recolector1.mostrarPerfil();
    std::cout << "\n";

    // Objeto Centro de Acopio
    CentroAcopio centroAcopio1("Av. 20 de Noviembre 156",1000.0);
    centroAcopio1.setHorarioGeneral("Lunes a Sábados: 8:00 - 17:00");
    centroAcopio1.recibirMaterial(500.0);
    centroAcopio1.mostrarInformacion();

    return 0;

}