// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
// Su coste es lineal; Recorre solo una vez el vector
bool parcialOrdenado(vector <int>& const datos, int ini, int fin, int& min, int& max) {

    int n = datos.size();
    if (n == 1)
        min = v[ini];
        return true;

    bool ordIz, ordDer;
    int mitad = datos.size() / 2;
    int minIz, minDer, maxIz, maxDer;

    ordIz = parcialOrdenado(datos, ini, mitad);
    ordDer = parcialOrdenado(datos, mitad, fin);
    min = (minIz, minDr);
    max = max(maxIz, maxDer);

    return ordIz && ordDer && minIz <= minDr && maxDr >= maxIz;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    vector <int> datos;
    int size, posicion, val;

    // El caso contiene un entero con el tamaño de los datos (1 n) y otro con la posicion a evaluar(0 n-1)
    cin >> size;
    cin >> posicion;


    for (int i = 0; i < size; i++)
    {
        cin >> val;
        datos.push_back(val);
    }


    if (resolver(datos, posicion))
        cout << "SI" << "\n";
    else cout << "NO" << "\n";
    // escribir sol


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