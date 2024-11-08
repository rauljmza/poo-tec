#include<string>
#include<iostream>

using namespace std;

class CentroAcopio{

    private:
        string domicilio;      // Domicilio en el que se encuentra el punto de acopio
        float capacidadActual; // La capacidad actual de materiales reciclables que puede recibir el centro de acopio en kilogramos
        float capacidadMaxima; // Capacidad máxima de materiales reciclables que puede recibir el centro de acopio en kilogramos
        string horarioGeneral; // El horario en el que se reciben los materiales reciclables

    public:
        //PuntoAcopio();
        // Constructor
        CentroAcopio(string domi, float capacidadMax){
            domicilio = domi;
            capacidadActual = 0;
            capacidadMaxima = capacidadMax;
        }

        // Getters

        string getDomicilio() const {
            return domicilio;
        }

        float getCapacidadActual() const {
            return capacidadActual;
        }

        float getCapacidadMaxima() const {
            return capacidadMaxima;
        }

        string getHorarioGeneral() const {
            return horarioGeneral;
        }

        // Setters

        void setDomicilio(string _domicilio){
            domicilio = _domicilio;
        }

        void setCapacidadMaxima(float _capacidadMaxima){
            if (_capacidadMaxima >= capacidadActual){
                capacidadMaxima = _capacidadMaxima;
            }
        }

        void setHorarioGeneral(string _horarioGeneral){
            horarioGeneral = _horarioGeneral;
        }

        // Método agregado

        bool recibirMaterial(float cantidad){
            if (cantidad > 0 && capacidadActual + cantidad <= capacidadMaxima){
                capacidadActual += cantidad;
                return true;
            }
            return false;
        }

        void mostrarInformacion() const{
            cout << "\n"
                 << "El centro de acopio está en el domicilio: " << domicilio << "\n"
                 << "La capacidad actual de este centro de acopio es de: " << capacidadActual << "kg\n"
                 << "La capacidad máxima de este centro de acopio es de: " << capacidadMaxima << "kg\n"
                 << "El horario de este centro de acopio es: " << horarioGeneral << "\n";
        }

};