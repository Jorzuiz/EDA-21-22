// Jorge Zurdo Izquierdo
// VJ 63

#include <iostream>
#include <fstream>
#include "bintree_eda.h"

using namespace std;


// Variable int devuelve el caudal, cuando acaba el programa devuelve el número de tramos navegables
// El coste es Lineal, el algoritmo llama recursivamente una vez a cada elemento y finalmente suma todos los valores
int calculaNavegables(const bintree<int>& root, int& caudal) {

    int navegables = 0;
    if (root.empty()) { caudal = 0; return 0; } // El origen del rio no proviene de ningun otro rio
    // Me he atascado aqui más de una hora porque puse em ambos lados root.left :_)
    if (root.left().empty() && root.right().empty()) {   caudal = 1; return 0;   }   // Caso origen del río

    //Sumamos los ríos que nos desembocan
    int caudalDer = 0, caudalIzq = 0;
    navegables += calculaNavegables(root.left(), caudalDer);
    navegables += calculaNavegables(root.right(), caudalIzq);

    // El caudal es la suma de caudales y la resta del embalse; Nunca puede ser menor que 0
    caudal = max((caudalDer + caudalIzq - root.root()), 0);

    // Si el caudal actual es mayor o igual de 3m/s es navegable
    if (caudalDer >= 3) navegables++;
    if (caudalIzq >= 3) navegables++;

    return navegables;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    bintree<int> arb;
    arb = leerArbol(-1); // -1 es la repr. de arbol vacio

    int caudal = 0;
    
    int navegables = calculaNavegables(arb, caudal);
    cout << navegables << "\n";

}

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

