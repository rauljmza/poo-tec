#include<string>

using namespace std;

class MaterialReciclable{

    private:
        string tipo;              // Tipo de material reciclable
        float cantidad;          // Cantidad de material reciclable en kilogramos
        bool limpiezaRequerida;   // Indica si el material requiere limpieza para ser reciclado
        float precioxKilo;       // Indica el precio por el que se compra el material por kilogramo
        int facilidadReciclaje;   // Métrica que indica en un intervalo del 1-10 qué tan fácil es reciclar este material
        int tiempoDescomposicion; // Métrica en años
        
    public:
        MaterialReciclable();
        // Constructor
        MaterialReciclable(string tipo, float cant, bool limpieza, float precio, int facilidadRec, int tiempoDesc){
            tipo = tipo;
            cantidad = cant;
            limpiezaRequerida = limpieza;
            precioxKilo = precio;
            facilidadReciclaje =  facilidadRec;
            tiempoDescomposicion = tiempoDesc;
        }

        // Getters
        string getTipo() const { 
            return tipo;
        }

        float getCantidad() const {
            return cantidad;
        }

        bool getLimpiezaRequerida() const {
            return limpiezaRequerida;
        }

        float getPrecioxKilo() const {
            return precioxKilo;
        }

        int getFacilidadReciclaje() const {
            return facilidadReciclaje;
        }

        int getTiempoDescomposicion() const {
            return tiempoDescomposicion;
        }

        // Setters

        void setTipo(string _tipo){
            tipo = _tipo;
        }

        void setCantidad(int _cantidad){
            cantidad = _cantidad;
        }

        void setLimpiezaRequerida(bool _limpiezaRequerida){
            limpiezaRequerida = _limpiezaRequerida;
        }

        void setPrecioxKilo(float _precioxKilo){
            precioxKilo = _precioxKilo;
        }

        void setFacilidadReciclaje(int _facilidadReciclaje){
            facilidadReciclaje = _facilidadReciclaje;
        }

        void setTiempoDescomposicion(int _tiempoDescomposicion){
            tiempoDescomposicion = _tiempoDescomposicion;
        }

        // Método agregado

        double valorReciclable() const {
            return cantidad * precioxKilo;
        }
};