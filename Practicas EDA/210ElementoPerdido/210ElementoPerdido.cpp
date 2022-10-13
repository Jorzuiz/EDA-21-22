// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ63

#include <iostream>
#include <iomanip>
#include <fstream>

#include <vector>

using namespace std;

// Función que resuelve el problema
// Un algoritmo de busqueda que recorre el vector discriminando las mitades que no contienen el elemento
// COSTE: log (N) siendo N el tamaño del vector dada que una mitad siempre se quedará sin procesar
int resolver(vector <int> datos1, vector <int> datos2, int ini, int fin) {
    
    // Caso base de tamaño 2 devolvemos el diferente de los 2 que no está en el vector 2
    if (fin - ini == 1) {
        if (datos1[ini] == datos2[ini]) { return datos1[fin]; }
        else {  return datos1[ini]; }
    }

    // comprobamos si el elemento está en la itad derecha o izquierda antes de avanzar
    if (datos1[(ini + fin)/2] == datos2[(ini+fin)/2])     resolver(datos1, datos2, fin / 2, fin);
    else    resolver(datos1, datos2, ini, fin / 2);


    return datos1[ini];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    int size, aux;
    vector <int> datos1, datos2;

    // leer los datos de la entrada
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        cin >> aux;
        datos1.push_back(aux);
    }

    for (int i = 0; i < size-1; i++)
    {
        cin >> aux;
        datos2.push_back(aux);
    }

    cout << resolver(datos1, datos2, 0, size);
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