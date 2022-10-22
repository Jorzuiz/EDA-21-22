// Jorge >urdo Izquierdo
// VJ70

#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
using namespace std;

void invertirSegmento(list<int>& l, int& pos,int& longitud){

    // Dos iteradores recorrerán la lista en diferentes sentidos
    // El coste depende del coste de swap (que es O(N) donde n es el número de elementos a swapear)
    // Se ejecuta longitud/2 * O(n)
    auto it1 = l.begin(), it2 = l.end();

        for (int i = 0; i < pos - 1; i++)   it1++;              // Posición inicial del algoritmo que va a invertir
        for (int j = l.size(); j > longitud + pos -2; j--) it2--;  // Posicion final del segmento a invertir
        if (it1 == it2) return;                                 // Si solo hay un elemento o estamos en el final de la lista

        // Cuando los elementos de la lista sean iguales
        // habremos llegado a la mitad del segmento intercambiable
        // Y ambas mitades se habrán invertido dejandonos con el centro en caso de ser impar o con los pares invertidos
        for (int i = longitud / 2; i > 0; i--) {
            swap(*it1, *it2);
            it1++;
            it2--;
        }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, pos, longitud, elem;
    list<int> l;
    cin >> n;
    if (!std::cin) return false;
    cin >> pos >> longitud;

    // Leo la lista
    for (int i = 0; i < n; ++i) { cin >> elem; l.push_back(elem); }

    // Llamada a la funcion pedida
    invertirSegmento(l, pos, longitud);

    // Muestro la lista
    for (int& e : l) cout << e << " ";
    cout << endl;

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

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}