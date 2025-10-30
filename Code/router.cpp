#include "Router.h"
#include <iostream>
#include <climits>
#include <fstream>
using namespace std;
const int Router::SIN_CONEXION;
Router::Router()
    : nombre('*'), visitado(false), distancia(INT_MAX), previo(nullptr) {}
Router::Router(char nombre, int cantidadRouters)
    : nombre(nombre), costos(cantidadRouters, SIN_CONEXION),
    visitado(false), distancia(INT_MAX), previo(nullptr)
{
    int indice = nombre - 'A';
    if (indice >= 0 && indice < cantidadRouters)
        costos[indice] = 0;
}
char Router::getNombre() const { return nombre; }
void Router::setNombre(char nuevoNombre) { nombre = nuevoNombre; }
int Router::getCosto(int indiceDestino) const {
    if (indiceDestino < 0 || indiceDestino >= (int)costos.size()) {
        cout << "ese valor esta demasiado alto, eso no tiene sentido, si quieres cambia las unidades de distancia (" << indiceDestino << ")" << endl;
        return SIN_CONEXION;
    }
    return costos[indiceDestino];
}
void Router::setCosto(int indiceDestino, int costo) {
    if (indiceDestino < 0 || indiceDestino >= (int)costos.size()) {
        cout << "ese valor esta muy alto, cambialo (" << indiceDestino << ")" << endl;
        return;
    }
    costos[indiceDestino] = costo;
}
const vector<int>& Router::getCostos() const { return costos; }
void Router::setCostos(const vector<int>& nuevosCostos) {
    costos = nuevosCostos;
}
void Router::reiniciar() {
    visitado = false;
    distancia = INT_MAX;
    previo = nullptr;
}
bool Router::estaVisitado() const { return visitado; }
void Router::marcarVisitado(bool estado) { visitado = estado; }
int Router::getDistancia() const { return distancia; }
void Router::setDistancia(int nuevaDistancia) { distancia = nuevaDistancia; }
Router* Router::getPrevio() const { return previo; }
void Router::setPrevio(Router* r) { previo = r; }
Router Router::crearPorlinea(const string& linea) {
    if (linea.empty()) {
        cout << "esa linea esta vacia" << endl;
        return Router();
    }
    size_t pos = linea.find(':');
    if (pos == string::npos) {
        cout << "te falto el separador, es este :" << linea << endl;
        return Router();
    }
    char nombre = linea[0];
    string valores = linea.substr(pos + 1);
    vector<int> costos;
    string numero = "";
    for (size_t i = 0; i <= valores.size(); ++i) {
        if (i == valores.size() || valores[i] == ',') {
            if (!numero.empty()) {
                int valor = 0;
                bool error = false;
                for (char c : numero) {
                    if (c != '-' && (c < '0' || c > '9')) {
                        error = true;
                        break;
                    }
                }
                if (error) {
                    cout << "valor incorrecto, revise el txt, se le va asignar -1 " << numero << endl;
                    valor = SIN_CONEXION;
                } else {
                    valor = stoi(numero);
                }
                costos.push_back(valor);
                numero.clear();
            }
        } else {
            numero += valores[i];
        }
    }

    Router nuevo(nombre, (int)costos.size());
    nuevo.setCostos(costos);
    return nuevo;
}
string Router::convertirTXT() const {
    string resultado;
    resultado += nombre;
    resultado += ':';
    for (size_t i = 0; i < costos.size(); ++i) {
        resultado += to_string(costos[i]);
        if (i < costos.size() - 1)
            resultado += ',';
    }
    return resultado;
}
void Router::imprimir() const {
    cout << nombre << ": ";
    for (size_t i = 0; i < costos.size(); ++i) {
        cout << costos[i];
        if (i < costos.size() - 1)
            cout << ", ";
    }
    cout << endl;
}
