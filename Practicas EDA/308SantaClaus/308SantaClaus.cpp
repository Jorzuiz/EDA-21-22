// Jorge Zurdo Izquierdo
// VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    
    // leer los datos de la entrada
    int numJuguetes, numNiños;
    cin >> numJuguetes;
    cin >> numNiños;
    
    vector<string> juguetes;
    for (int i = 0; i < numJuguetes; i++)
    {
        cin >> juguetes[i];
    }
    
    //cin >> m >> consumoMax;
    //vector<int> consumosPorColor(m);
    //for (int& e : consumosPorColor) cin >> e;
    //vector<int> soluc(n);
    //int k = 0;
    //vector<int> totalesPorColor(m, 0);
    //resolver();
    
    // Salida
    return true;
}

void resolver(vector<string> juguetes){}

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
    //system("PAUSE");
#endif

    return 0;
}