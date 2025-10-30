#ifndef ROUTER_H
#define ROUTER_H
#include <vector>
#include <string>
#include <iostream>
class Router {
private:
    char nombre;
    std::vector<int> costos;
    bool visitado;
    int distancia;
    Router* previo;

public:
   static const int SIN_CONEXION = -1;
    Router();
    Router(char nombre, int cantidadRouters);
    char getNombre() const;
    void setNombre(char nuevoNombre);
    int getCosto(int indiceDestino) const;
    void setCosto(int indiceDestino, int costo);
    const std::vector<int>& getCostos() const;
    void setCostos(const std::vector<int>& nuevosCostos);
    void reiniciar();
    bool estaVisitado() const;
    void marcarVisitado(bool estado);
    int getDistancia() const;
    void setDistancia(int nuevaDistancia);
    Router* getPrevio() const;
    void setPrevio(Router* r);
    Router crearPorlinea(const std::string& linea);  // Crea un router desde una línea del .txt
    std::string convertirTXT() const;                        // Convierte el router a formato de archivo
    void imprimir() const;
};

#endif // ROUTER_H
