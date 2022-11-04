// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>
#include "bintree_eda.h"
using namespace std;

// El algoritmo busca entre todos los nodos hasta que acaba o encuentra un valor que incumple la condición
// Nos deja por lo tanto con un coste de orden O(n) donde n es el número de nodos del árbol
template <class T>
bool esBinario(bintree<T> const& tree, int MIN, int MAX) {
    
    // Un árbol vacío está equilibrado
    if (tree.empty())
        return true;
    // La raíz tiene que se estrictamente menor o mayor que TODOS los hijos de un lado
    if (tree.root() < MIN || tree.root() > MAX)
        return false;

    // La llamada recursiva contiene una comparación de todos sus hijos de manera recursiva
    // conque solo uno de ellos sea falso, todo el árbol será falso
    // Los valores MIN y MAX se usan como marcadores que indican el valor de la raíz a la hora de comprobar los hijos
    // El -1 y el +1 evita que la raíz pueda ser igual
    return (esBinario(tree.left(), MIN, tree.root() - 1) 
        && esBinario(tree.right(), tree.root() + 1, MAX));
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);   // Bendito método de lectura
    int MIN = INT_MIN, MAX = INT_MAX;

    if (esBinario(tree, MIN, MAX))
        cout << "SI\n";
    else
        cout << "NO\n";
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