// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// Recorre el vector accediendo solo a los datos que pueden ser picos o valles (ignora el primero y el ultimo)
// Lleva 2 contadores y escribe la solucion al final
void resolver(vector <int> datos) {

    if (datos.size() >= 3) {
        int picos = 0; int valles = 0;
        // El algoritmo ignora el primer y el ultimo valor del vector
        for (int i = 1; i < datos.size() - 1; i++)
        {
            if (datos[i - 1] > datos[i] && datos[i] < datos[i + 1])
                valles++;

            if (datos[i - 1] < datos[i] && datos[i] > datos[i + 1])
                picos++;
        }

        cout << picos << " ";
        cout << valles << "\n";
    }

    // Un vector de menor tamaño que 3 no puede tener picos ni valles
    else {
        cout << "0 ";
        cout << "0 \n";
    }

}


// Un pico de un vector es un valor cuyos vecinos son estrictamente menores
// Un vallede un vector es un valor cuyos vvecinos son estrictamente mayores
void resuelveCaso() {
    // leer los datos de la entrada

    int tamano;
    int val;
    vector <int> datos;

    cin >> tamano;

    for (int i = 0; i < tamano; i++)
    {
        cin >> val;
        datos.push_back(val);
    }

    resolver(datos);

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