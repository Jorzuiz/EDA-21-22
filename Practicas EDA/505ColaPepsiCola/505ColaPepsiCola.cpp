#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
using namespace std;

// Extensión de clase definida en Queue_eda.h
template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;   // Definimos Nodo como node DEL PADRE

public:
    void cuela(const T& a, const T& b) {
        // Ojo que para acceder a prim o ult hay que escribir this->prim o this->ult
        // Debido a que this en el scope actual hace referencia a la clase padre
        Nodo* act = this->prim;

        while (act != this->ult && act->elem != a) {
            act = act->sig;
        }
        if (act == nullptr) return; // No se ha encontrado el elemento a

        Nodo* aux = act;
        while (act != this->ult && act->elem != b) {
            this->ult->sig = act;
            act = act->sig;
            aux->sig = act;
            aux = act;
        }
        if (act == nullptr) return; // No se ha encontrado el elemento a

    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, a, b;
    queue_plus<int> q;
    cin >> n;
    if (n == -1) return false;
    while (n != -1) {
        q.push(n);
        cin >> n;
    }
    cin >> a >> b;

    // llamada a metodo
    q.cuela(a, b);

    // escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
    for (int i = 0; i < q.size(); ++i) {
        n = q.front();
        q.pop();
        q.push(n);
    }
    // Ahora imprimimos la cola y de paso la dejamos vacía
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
    return true;
};

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