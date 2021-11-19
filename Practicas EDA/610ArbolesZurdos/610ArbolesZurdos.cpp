// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

using namespace std;

// función que resuelve el problema
// El objetivo es un coste lineal, teniendo que recorrer solo una vez el árbol recursivamente
// comprobando los diferentes casos bases hasta que se rompa o no se puedan comparar más

bool resolver(const bintree<char>& datos, int& acc) {

    // Caso base Árbol vacio siempre es Zurdo
    if (datos.empty()) { acc = 0; return true; }    // Un árbol vacío no aporta nodos
    if (datos.left().empty() && datos.right().empty()) { acc = 1; return true; }    // Un árbol sin hijos se aporta a sí mismo

    // Cuentas de nodos para los hijos recursivos izquierdos y derechos
    int nodosIZ = 0, nodosDER = 0;

    bool left = resolver(datos.left(), nodosIZ);    // Llamada izquierda con el contador de su rama
    bool right = resolver(datos.right(), nodosDER);  // Llamada derecha con el contador de su rama

    acc = nodosIZ + nodosDER + 1;    // Sumamos ambos hijos y el nodo propio al acumulador recursivo

    // La cantidad de nodos en la ziquierda tiene que ser estrictamente mayor que la mitad del total
    return (nodosIZ > (nodosDER + nodosIZ) / 2) && left && right;

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    // Método EXTREMADAMENTE conveniente
    bintree<char> arbol = leerArbol('.');

    int nodos = 0;
    bool sol = resolver(arbol, nodos);

    // escribir sol
    if (sol)
        cout << "SI\n";
    else
        cout << "NO\n";

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
    system("PAUSE");
#endif

    return 0;
}