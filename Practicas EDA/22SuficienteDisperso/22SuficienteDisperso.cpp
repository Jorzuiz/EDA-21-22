// Nombre del alumno Jorge Zurdo Izquierdo 
// Usuario del Juez VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

// función que resuelve el problema
bool suficiente_disperso(vector <int> & datos, int dispersion, int ini, int fin) {

    // Caso Base. Diferencia del primer y último valor mayor o igual a K
    if (fin - ini == 1) {
        if (abs(datos[ini] - datos[fin]) >= dispersion)
            return true;
        else return false;
    }

    bool half = suficiente_disperso(datos, dispersion, ini, fin / 2);
    bool second_half = suficiente_disperso(datos, dispersion, fin / 2 + 1, fin);

    return half && second_half;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    vector <int> datos;
    int dispersion, size, aux;

    cin >> size;

    if (!std::cin)
        return false;

    cin >> dispersion;
    for (int i = 0; i < size; i++)
    {
        cin >> aux;
        datos.push_back(aux);

    }


    if (suficiente_disperso(datos, dispersion, 0, size-1))
        // escribir sol
        cout << "SI" << "\n";
    else 
        cout << "NO" << "\n";

    return true;

}

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
    system("PAUSE");
#endif

    return 0;
}