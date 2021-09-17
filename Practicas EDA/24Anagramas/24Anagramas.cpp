// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>    // Contiene la función sort

using namespace std;

// Metodo de la libreria algorithm
string sortString(string palabra) {

    std::sort(palabra.begin(), palabra.end());
    return palabra;
}

// función que resuelve el problema
// Ordena los string usando la funcion sort de la STD
// Su coste es el de la función sort
bool resolver(string palabra_1, string palabra_2) {

    string word = sortString(palabra_1);
    string word2 = sortString(palabra_2);
    
    if (word == word2)
        return true;
    return false;

}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    string palabra_1, palabra_2;
    cin >> palabra_1;
    cin >> palabra_2;

    if (resolver(palabra_1, palabra_2))
        cout << "SI";
    else cout << "NO";

    cout << "\n";

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