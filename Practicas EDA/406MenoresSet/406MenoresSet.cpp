// VJ 70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Set.h"

using namespace std;

// El coste del algortmo es de orden n * log(K)
// El algoritmo crea un set a modo de buffer de tamaño k y va haciendo 
// comparaciones de valores para quitar cada vez el máximo por un nuevo valor menor que él
// Cada una de estas compraciones es unaa busqueda binaria sobre el tamaño K
// Vamos a ejecutar el bucle un total de N veces, tanto las primeras k veces como las siguientes hasta N
void kMenores(vector<int>& vector, int k) {
    
    Set<int> set;
    for (int i = 0; i < vector.size(); i++)
    {
        // Caso de que aun no tengamos K elementos
        // Coste de esta prte sería k * log(K)
        if (set.size() < k) 
                set.add(vector[i]); // Solo añade si no está ya dentro; esto hace una busqueda binaria log(N)

        // Coste de esta parte sería n * log(K)
        if (vector[i] < set.getMax()        // Coste constante O(1)
            && !set.contains(vector[i])) {  // Contains hace una busqueda binaria en el set log(k)
            set.removeMax();                // Conste Lineal O(n)
            set.add(vector[i]); // Add hace una busqueda binaria log(k)
        }
    }

    // Escribimos los valores en set; estarán ordenados y serán solo los menores sin repetición del vector dado
    const int* array = set.toArray();

    for (int i = 0; i < set.size(); i++)
    {
        std::cout << array[i] << " ";
    }

    cout << "\n";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    
    int n;
    cin >> n;

    if (n == 0)     // CASO ESPECIAL fin de la ejecución
        return false;
    
    int aux;
    cin >> aux;
    vector<int> vector;

    while (aux != -1) {
        vector.push_back(aux);
        cin >> aux;
    }

    kMenores(vector, n);

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

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
