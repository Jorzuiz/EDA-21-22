/*
Nombre completo:    Jorge Zurdo IZquierdo
DNI:                12344685X
Usuario del juez:   VJ70
Puesto de laboratorio:  Pto0219
Qué has conseguido hacer y qué no:
implementado el metodo con algoritmo, falta depurar los enlaces de los nodos creados tras una eliminacion
Si evaluo la cola en la liea 77 me dice que está bien, pero al darle la vuelta la representa mal
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
#include <vector>
using namespace std;

template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;

public:

    void replicaElems(const vector<int> mult) {

        if (this->empty()) {             // Devuelve cola vacia
            return;
        }
        else {
            Nodo* actual = this->prim;                 // Nodo primero
            Nodo* prev = nullptr;

            // El coste de este bucle en principio es de N donde N es el tamaño del vector de multiplicidades
            // Sin embargo dentro existe un for que se ejecutará una vez por cada multiplicidad - 1
            // El coste total es de orden O(N) con valor (M-N) * N donde la M es el valor de la suma de las multiplicidades restandole N
            for (int i = 0; i < mult.size(); i++) {
                // Si la multiplicidad es 0 se ejecutará esto antes de pasar al siguiente valor del bucle
                if (mult[i] == 0) {                     
                    Nodo* aux = actual;
                    if (prev == nullptr) {            // Si es el primer caso
                        this->prim = actual->sig;     // Apuntamos el primero al siguiente
                    }
                    else {
                        prev->sig = actual->sig;        // Como no es el primero tenemos que actualizar el nodo que apunta al previo
                    }
                    actual = actual->sig;               // Sea el primero o no, lo avanzamos
                    delete aux;                         // Borramos el nodo despues de avanzar el actual
                    this->nelems--;
                }
                else {
                    // Si la multiplicidad es Mayor que 0 se ejecutará M - 1 donde M es el valor guardado en el vector
                    for (int j = 0; j < (mult[i] - 1); j++)
                    {
                        Nodo* nuevo = new Nodo(actual->elem);       // Nodos para crear
                        nuevo->sig = actual->sig;                   // Apuntamos nuevo al sugiente      10
                        actual->sig = nuevo;                        // Apuntamos el primero al nuevo    23
                        actual = actual->sig;
                        this->nelems++;
                    }
                    // Esto se ejecutará al final, dado que solo tenemeos que crear M - 1 nodos y podemos reusar el que ya estaba
                    prev = actual;
                    actual = actual->sig;
                }
            }
            this->ult = prev;
        }
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n;
    queue_plus<int> q;

    cin >> n;
    vector<int> mult(n);
    vector<int> aux(n); // Para darle la vuelta a la secuencia de entrada

    // Leemos la secuencia invertida para q y le damos la vuelta
    for (int i = n - 1; i >= 0; --i) cin >> aux[i];
    for (int e : aux) q.push(e);

    // Leemos la secuencia invertida para mult
    for (int i = n - 1; i >= 0; --i) cin >> mult[i];

    // llamada al metodo
    q.replicaElems(mult);

    // escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
    for (int i = 0; i < q.size(); ++i) {
        n = q.front();
        q.pop();
        q.push(n);
    }

    // Ahora imprimimos la cola y de paso la dejamos vacía (tb para probar su consistencia)
    cout << "[";
    if (!q.empty()) {
        cout << q.front();
        q.pop();
    }
    while (!q.empty()) {
        cout << ", " << q.front();
        q.pop();
    }
    cout << "]" << endl;
    return true;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input1.txt");
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
