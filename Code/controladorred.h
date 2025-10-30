#ifndef CONTROLADORRED_H
#define CONTROLADORRED_H
#include "Router.h"
#include <vector>
#include <string>
class ControladorRed {
private:
    std::vector<Router> routers;
    bool cargada;
    int buscarIndice(char nombre) const;
    void dijkstra(int indiceOrigen);
public:
    ControladorRed();
    void agregarRouter(char nombre);//para la geston
    void eliminarRouter(char nombre);
    void actualizarCosto(char origen, char destino, int nuevoCosto);
    void cargarDesdeArchivo(const std::string& rutaArchivo);
    void guardarEnArchivo(const std::string& rutaArchivo);
    void costoEnvio(char origen, char destino);
    void caminoMasCorto(char origen, char destino);
    void generarRedAleatoria(int nRouters, int costoMax, double probConexion);
    void imprimirTopologia() const;
};

#endif // CONTROLADORRED_H
