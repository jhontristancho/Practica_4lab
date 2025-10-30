#include "ControladorRed.h"
#include <iostream>
using namespace std;

void mostrarMenu() {
    cout << "\n===== MENU CONTROLADOR DE RED =====" << endl;
    cout << "1. Cargar red desde archivo" << endl;
    cout << "2. Guardar red en archivo" << endl;
    cout << "3. Ver topologia de la red" << endl;
    cout << "4. Agregar router" << endl;
    cout << "5. Eliminar router" << endl;
    cout << "6. Actualizar costo entre routers" << endl;
    cout << "7. Ver costo minimo de envio" << endl;
    cout << "8. Ver camino mas corto" << endl;
    cout << "9. Generar red aleatoria" << endl;
    cout << "0. Salir" << endl;
    cout << "===================================" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    ControladorRed red;
    int opcion = -1;

    while (opcion != 0) {
        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {
            string archivo;
            cout << "Ingrese nombre del archivo (.txt): ";
            cin >> archivo;
            red.cargarDesdeArchivo(archivo);

        } else if (opcion == 2) {
            string archivo;
            cout << "Ingrese nombre del archivo para guardar (.txt): ";
            cin >> archivo;
            red.guardarEnArchivo(archivo);

        } else if (opcion == 3) {
            red.imprimirTopologia();

        } else if (opcion == 4) {
            char nombre;
            cout << "Ingrese nombre del nuevo router (letra): ";
            cin >> nombre;
            red.agregarRouter(nombre);

        } else if (opcion == 5) {
            char nombre;
            cout << "Ingrese nombre del router a eliminar: ";
            cin >> nombre;
            red.eliminarRouter(nombre);

        } else if (opcion == 6) {
            char origen, destino;
            int costo;
            cout << "Ingrese router origen: ";
            cin >> origen;
            cout << "Ingrese router destino: ";
            cin >> destino;
            cout << "Ingrese nuevo costo: ";
            cin >> costo;
            red.actualizarCosto(origen, destino, costo);

        } else if (opcion == 7) {
            char origen, destino;
            cout << "Router origen: ";
            cin >> origen;
            cout << "Router destino: ";
            cin >> destino;
            red.costoEnvio(origen, destino);

        } else if (opcion == 8) {
            char origen, destino;
            cout << "Router origen: ";
            cin >> origen;
            cout << "Router destino: ";
            cin >> destino;
            red.caminoMasCorto(origen, destino);

        } else if (opcion == 9) {
            int n, maxCosto;
            double prob;
            cout << "Cantidad de routers: ";
            cin >> n;
            cout << "Costo maximo: ";
            cin >> maxCosto;
            cout << "Probabilidad de conexion (0 a 1): ";
            cin >> prob;
            red.generarRedAleatoria(n, maxCosto, prob);
        }

        else if (opcion == 0) {
            cout << "Saliendo del programa..." << endl;
        } else {
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    }

    return 0;
}
