#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"       // Visto en clase; C0ntiene extensión

using namespace std;


template <class T>
class queue_plus : public List<T> {
    using Nodo = typename queue<T>::Nodo;

public:
    void elimina() {
        // Ojo que para acceder a prim o ult hay que escribir this->prim o this->ult
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    
    int el;                     // Elemento a eliminar
    list<int> myLista;
    auto it = myLista->begin();
    cin >> n;

    if (!cin) return false;
    while (n != -1) {
        myLista.push_back(n);
        cin >> n;
    }

    // llamada a metodo
    myLista.elimina(int el);

    // escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
    for (it = list.cbegin(); it != list.cend(); ++it) {
        n = list.front();
        cout << n << " ";
    }

    cout << "\n";
    return true;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
