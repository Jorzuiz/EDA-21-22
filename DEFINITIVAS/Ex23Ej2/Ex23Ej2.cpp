// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <fstream>
#include <climits>

#include "bintree_eda.h"

using namespace std;

void draconis(const bintree<int> &mazmorra, int & cont, int nDrag, int& mNodo)
{
    //Si el arbol no esta vacio
    if (!mazmorra.empty()){
        // Si tenemos una hoja comprobamos los dragones que había en el camino
        if (mazmorra.left().empty() && mazmorra.right().empty()) {
            // Si había menos deragones actualizamos
            if (nDrag < cont) {
                cont = nDrag;
                mNodo = mazmorra.root();
            }
        }
        else {  // Si no tenenmos una hoja solo nos queda explorar  habiendo contado los dragones
            if (mazmorra.root() == 1) nDrag++;
            draconis(mazmorra.left(), cont, nDrag, mNodo);
            draconis(mazmorra.right(), cont, nDrag, mNodo);
        }
    }
}

void resuelveCaso()
{
    bintree<int> arbol;

    arbol = leerArbol(-1);
    int salida = 3;
    int nDragones = 0, cont = INT_MAX;

    if (!arbol.empty() && arbol.root() == 0)
        draconis(arbol, cont, nDragones, salida);

    //if (salida != -1)
    cout << salida;

    cout << "\n";
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
