#include "ControladorRed.h"
#include <iostream>
#include <fstream>
#include <random>
#include <climits>
#include <algorithm>
using namespace std;
ControladorRed::ControladorRed() : cargada(false) {}
int ControladorRed::buscarIndice(char nombre) const {
    for (size_t i = 0; i < routers.size(); ++i)
        if (routers[i].getNombre() == nombre)
            return (int)i;
    return -1;
}
void ControladorRed::agregarRouter(char nombre) {
    if (buscarIndice(nombre) != -1) {
        cout << "ese router " << nombre << " es imposible agregar, acuerdese solo char" << endl;
        return;
    }
    int n = routers.size() + 1;
    for (auto& r : routers) {
        auto costos = r.getCostos();
        costos.push_back(r.SIN_CONEXION);
        r.setCostos(costos);
    }
    Router nuevo(nombre, n);
    routers.push_back(nuevo);
    vector<int> nuevosCostos(n, Router().SIN_CONEXION);
    nuevosCostos[n - 1] = 0;
    routers[n - 1].setCostos(nuevosCostos);
    cout << "el router" << nombre << " se agrego bien." << endl;
}
void ControladorRed::eliminarRouter(char nombre) {
    int idx = buscarIndice(nombre);
    if (idx == -1) {
        cout << "el router " << nombre << " no existe " << endl;
        return;
    }
    routers.erase(routers.begin() + idx);
    for (auto& r : routers) {
        auto costos = r.getCostos();
        if (idx < (int)costos.size()) {
            costos.erase(costos.begin() + idx);
        }
        r.setCostos(costos);
    }
    cout << "el router " << nombre << " se elimino bien" << endl;
}

void ControladorRed::actualizarCosto(char origen, char destino, int nuevoCosto) {
    int i = buscarIndice(origen);
    int j = buscarIndice(destino);
    if (i == -1 || j == -1) {
        cout << "error, algun router de esos no existe " << endl;
        return;
    }
    routers[i].setCosto(j, nuevoCosto);
    routers[j].setCosto(i, nuevoCosto);
    cout << "se actualizo el costo entre  " << origen << " y " << destino << " a " << nuevoCosto << endl;
}
void ControladorRed::cargarDesdeArchivo(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "no se pudo abrir el archivo: " << rutaArchivo << endl;
        return;
    }
    routers.clear();
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        Router r;
        r = r.crearPorlinea(linea);
        routers.push_back(r);
    }
    archivo.close();
    cargada = true;
    cout << "se cargo bien la red " << rutaArchivo << endl;
}
void ControladorRed::guardarEnArchivo(const string& rutaArchivo) {
    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "no se pudo guardar la informacion en el archivo  " << rutaArchivo << endl;
        return;
    }
    for (const auto& r : routers) {
        archivo << r.convertirTXT() << endl;
    }
    archivo.close();
    cout << " se guardo en el archivo " << rutaArchivo << endl;
}
void ControladorRed::dijkstra(int indiceOrigen) {
    for (auto& r : routers) r.reiniciar();
    routers[indiceOrigen].setDistancia(0);
    for (size_t i = 0; i < routers.size(); ++i) {
        int idxMin = -1;
        int minDist = INT_MAX;
        for (size_t j = 0; j < routers.size(); ++j) {
            if (!routers[j].estaVisitado() && routers[j].getDistancia() < minDist) {
                minDist = routers[j].getDistancia();
                idxMin = (int)j;
            }
        }
        if (idxMin == -1) break;
        routers[idxMin].marcarVisitado(true);
        for (size_t k = 0; k < routers.size(); ++k) {
            int costo = routers[idxMin].getCosto((int)k);
            if (costo != routers[idxMin].SIN_CONEXION && !routers[k].estaVisitado()) {
                int nuevaDist = routers[idxMin].getDistancia() + costo;
                if (nuevaDist < routers[k].getDistancia()) {
                    routers[k].setDistancia(nuevaDist);
                    routers[k].setPrevio(&routers[idxMin]);
                }
            }
        }
    }
}

void ControladorRed::costoEnvio(char origen, char destino) {
    int i = buscarIndice(origen);
    int j = buscarIndice(destino);
    if (i == -1 || j == -1) {
        cout << "router no encontrado" << endl;
        return;
    }
    dijkstra(i);
    int costo = routers[j].getDistancia();
    if (costo == INT_MAX)
        cout << "no hay un camino fijo entre  " << origen << " y " << destino << endl;
    else
        cout << "el costo de  " << origen << " a " << destino << " es: " << costo << endl;
}

void ControladorRed::caminoMasCorto(char origen, char destino) {
    int i = buscarIndice(origen);
    int j = buscarIndice(destino);
    if (i == -1 || j == -1) {
        cout << "no se pudo encontrar los routers" << endl;
        return;
    }
    dijkstra(i);
    if (routers[j].getDistancia() == INT_MAX) {
        cout << "no existe un camino entre  " << origen << " y " << destino << endl;
        return;
    }
    vector<char> camino;
    Router* actual = &routers[j];
    while (actual != nullptr) {
        camino.push_back(actual->getNombre());
        actual = actual->getPrevio();
    }
    reverse(camino.begin(), camino.end());

    cout << "el camino mas corto de " << origen << " a " << destino << ": ";
    for (size_t i = 0; i < camino.size(); ++i) {
        cout << camino[i];
        if (i < camino.size() - 1) cout << " -> ";
    }
    cout << endl;
}
void ControladorRed::generarRedAleatoria(int nRouters, int costoMax, double probConexion) {
    routers.clear();
    if (nRouters <= 0) {
        cout << "esa cantidad no se puede, ponga mayor de 0" << endl;
        return;
    }
    for (int i = 0; i < nRouters; ++i) {
        char nombre = 'A' + i;
        Router r(nombre, nRouters);
        routers.push_back(r);
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> prob(0.0, 1.0);
    uniform_int_distribution<> costo(1, costoMax);
    for (int i = 0; i < nRouters; ++i) {
        for (int j = i + 1; j < nRouters; ++j) {
            if (prob(gen) <= probConexion) {
                int c = costo(gen);
                routers[i].setCosto(j, c);
                routers[j].setCosto(i, c);
            }
        }
    }
    cargada = true;
    cout << "se genero correctamente la red con  " << nRouters << " routers" << endl;
}

void ControladorRed::imprimirTopologia() const {
    cout << "la topologia de la red es: " << endl;
    for (const auto& r : routers)
        r.imprimir();
}
