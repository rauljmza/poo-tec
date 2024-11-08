#include<string>
#include<iostream>

using namespace std;

class Recolector{

    private:
        string nombre;            // Nombre del recolector
        string zonaTrabajo;       // Zona en la que recolecta
        string materialPrincipal; // Material que mejor le conviene recolectar
        float totalRecolectado;   // Total de material reciclable recolectado en kilogramos
        int rating;               // Calificacion del recolector en un rango de 1-5 estrellas

    public:
        Recolector();
        // Constructor
        Recolector(string nombre, string zona, string materialPri){
            nombre = nombre;
            zonaTrabajo =  zona;
            materialPrincipal = materialPri;
            totalRecolectado = 0;
            rating = 0; //5
        }

        // Getters

        string getNombre() const {
            return nombre;
        }

        string getZonaTrabajo() const {
            return zonaTrabajo;
        }

        string getMaterialPrincipal() const {
            return materialPrincipal;
        }

        float getTotalRecolectado() const {
            return totalRecolectado;
        }

        int getRating() const {
            return rating;
        }

        // Setters

        void setNombre(string _nombre){
            nombre = _nombre;
        }

        void setZonaTrabajo(string _zonaTrabajo){
            zonaTrabajo = _zonaTrabajo;
        }

        void setMaterialPrincipal(string _materialPrincipal){
            materialPrincipal = _materialPrincipal;
        }

        void setRating(int _rating){
            if (_rating >= 1 && _rating<=5){
                rating = _rating;
            }
        }

        // Método agregado

        void registrarRecoleccion(float cantidad){
            if (cantidad>0){
                totalRecolectado += cantidad;
            }
        }

        void mostrarPerfil() const{
            cout << "Recolector (reciclador): " << nombre << "\n"
                 << "Zona en la que trabaja: " << zonaTrabajo << "\n"
                 << "Material principal que recolecta: " << materialPrincipal << "\n"
                 << "Rating (1-5 estrellas): " << rating << "\n"
                 << "Cantidad total que ha recolectado: " << totalRecolectado << "kg\n";
        }

};