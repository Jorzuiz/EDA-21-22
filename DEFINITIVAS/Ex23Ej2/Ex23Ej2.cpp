// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <fstream>
#include <climits>

#include "bintree_eda.h"

using namespace std;

void resolver(bintree<int> arbol, int& nDragones, int& salida)
{
    //Si el arbol no esta vacio
    if (!arbol.empty())
    {
        //Comprobamos si estamos en una de las hojas, debido a que son 
        //las cifras superiores a 2 (1 es dragon, 2 es vacio)
        if (arbol.root() > 2)
            salida = arbol.root();

        //Si no lo estamos
        else
        {
            int dragonesIzq = 0;
            int dragonesDer = 0;

            int nodoIzq = -1;
            int nodoDer = -1;

            //Continuamos por el lado izquierdo del arbol
            if (!arbol.left().empty())
                resolver(arbol.left(), dragonesIzq, nodoIzq);

            //Continuamos por el lado derecho del arbol
            if (!arbol.right().empty())
                resolver(arbol.right(), dragonesDer, nodoDer);

            //Si ambas salidas tienen un nodo...
            if (nodoIzq != -1 && nodoDer != -1)
            {
                //Comprobamos si hay menos o igual numero de dragones izquierdos, para
                //extraer la salida izquierda
                if (dragonesIzq <= dragonesDer)
                {
                    salida = nodoIzq;
                    nDragones += dragonesIzq;
                }

                //Si no, lo mismo pero en el lado derecho
                else
                {
                    salida = nodoDer;
                    nDragones += dragonesDer;
                }
            }

            //Si solo hay nodo derecho, devolvemos el lado derecho
            else if (nodoIzq == -1)
            {
                salida = nodoDer;
                nDragones += dragonesDer;
            }

            //Si solo hay un nodo izquierdo, devolvemos el lado izquierdo
            else if (nodoDer == -1)
            {
                salida = nodoIzq;
                nDragones += dragonesIzq;
            }

            //Si la raiz es 2, hay un dragon 
            if (arbol.root() == 1)
                nDragones++;
        }
    }
}

void resuelveCaso()
{
    bintree<int> arbol;

    arbol = leerArbol(-1);

    int salida = -1;
    int nDragones = 0;

    if (!arbol.empty() && arbol.root() == 0)
        resolver(arbol, nDragones, salida);

    if (salida != -1)
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
