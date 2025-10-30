#include "ControladorRed.h"
#include <iostream>
using namespace std;

void mostrarMenu() {
    cout << "menu de la red:" << endl;
    cout << "1. para cargar la red del txt" << endl;
    cout << "2. para guardar la nueva red en el txt" << endl;
    cout << "3. para ver como va tu distribucion de la red" << endl;
    cout << "4. para agregar router" << endl;
    cout << "5. para eliminar router" << endl;
    cout << "6. para actualizar costos entre routers" << endl;
    cout << "7. para ver el costo minimo de envio" << endl;
    cout << "8. para ver el camino mas corto a seguir" << endl;
    cout << "9. para generar una red aleatoria" << endl;
    cout << "0. para terminar de ejecutar" << endl;
}

int main() {
    ControladorRed red;
    int opcion = -1;
    while (opcion != 0) {
        mostrarMenu();
        cin >> opcion;
        if (opcion == 1) {
            string archivo;
            cout << "ingrese el nombre del txt ";
            cin >> archivo;
            red.cargarDesdeArchivo(archivo);
        } else if (opcion == 2) {
            string archivo;
            cout << "ingrese el nombre del txt donde quiera guardar, tenga en cuenta que debe estar creado ";
            cin >> archivo;
            red.guardarEnArchivo(archivo);
        } else if (opcion == 3) {
            red.imprimirTopologia();
        } else if (opcion == 4) {
            char nombre;
            cout << "ingrese el nombre del nuevo router, debe ser un char";
            cin >> nombre;
            red.agregarRouter(nombre);
        } else if (opcion == 5) {
            char nombre;
            cout << "ingrese el nombre del router que quiera eliminar";
            cin >> nombre;
            red.eliminarRouter(nombre);
        } else if (opcion == 6) {
            char origen, destino;
            int costo;
            cout << "router origen: ";
            cin >> origen;
            cout << "router destino: ";
            cin >> destino;
            cout << "nuevo costo: ";
            cin >> costo;
            red.actualizarCosto(origen, destino, costo);
        } else if (opcion == 7) {
            char origen, destino;
            cout << "router origen: ";
            cin >> origen;
            cout << "router destino: ";
            cin >> destino;
            red.costoEnvio(origen, destino);
        } else if (opcion == 8) {
            char origen, destino;
            cout << "router origen: ";
            cin >> origen;
            cout << "router destino: ";
            cin >> destino;
            red.caminoMasCorto(origen, destino);
        } else if (opcion == 9) {
            int n, maxCosto;
            double prob;
            cout << "cantidad de routers: ";
            cin >> n;
            cout << "costo maximo: ";
            cin >> maxCosto;
            cout << "probabilidad de conexion (0 a 1): ";
            cin >> prob;
            red.generarRedAleatoria(n, maxCosto, prob);
        }
        else if (opcion == 0) {
            cout << "muy bien hecho" << endl;
        } else {
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    }

    return 0;
}
