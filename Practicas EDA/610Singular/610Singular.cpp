// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;


// El algoritmo recorre todos los nodos comprobando uno a uno sus hijos
// Su orden de complejidad es de O(n)
template <class T>
int singulares(bintree<T> const& tree, int acu, int& cont) {
    
    // El árbol vacío no tiene valor
    if (tree.empty())
        return 0;

    // Llamamos a los hijos recursivos para sacar sus valores
    // El valor del acumulador se va actualizando con la raíz actual para que pueda comprobar si los valores son iguales
    int left = singulares(tree.left(), acu + tree.root(), cont);
    int right = singulares(tree.right(), acu + tree.root(), cont);

    // Si la suma de los hijos, es igual a las raíces sobre nosotros, el nodo es singular
    if (left + right == acu)
        cont++;

    // Sumamos los nodos para la llamada recursiva
    return left + right + tree.root();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);
    // Incializamos el valor del acumulador y los nodos a 0
    int cont = 0;
    singulares(tree, 0, cont);  
    // El método devuelve la suma de todos los nodos, pero nosostros queremos el contador de singulares
    cout << cont << "\n";
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
