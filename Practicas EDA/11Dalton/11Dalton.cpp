// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// La funcion analiza los numeros de inicio a fin
// Detecta si el caso es creciente o decreciente en inicio
// si durante la ejecucion detecta un caso que rompe el algoritmo sale de el
// El coste peor es N
bool resolver(std::vector <int> caso) {

    // Si ambos tienen la misma altura no pueden ser Dalton
    if (caso[0] == caso[1])  return false;

    // Caso decreciente
    if (caso[0] > caso[1]) {
        for (int i = 0; i < caso.size() - 1; i++) {
            if (caso[i] <= caso[i + 1])  // Si nos encontramos un caso contrario no son Dalton
                return false;
        }
    }

    // Si no es decreciente tiene que ser creciente
    else {
        for (int i = 0; i < caso.size() - 1; i++) {
            if (caso[i] >= caso[i + 1])  // Si nos encontramos un caso contrario no son Dalton
                return false;
        }
    }

    return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
// Se repite ahsta detectar el caso especial que lo corta
bool resuelveCaso() {

    // leer los datos de la entrada
    int numCasos, num;
    std::vector <int> caso;

    std::cin >> numCasos;

    //Caso especial; Corte de ejecución
    if (numCasos == 0)
        return false;
    else
        for (int i = 0; i < numCasos; i++)
        {
            std::cin >> num;
            caso.push_back(num);
        }


    if (resolver(caso))
        std::cout << "DALTON \n";
    else
        std::cout << "DESCONOCIDOS \n";

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