// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// función que resuelve el problema
// Su coste es lineal; Recorre solo una vez el vector
bool resolver(vector <int> datos, int posicion) {

    // Si la posicion está en el ultimo valor del vector siempre devolvemos true
    if (posicion >= datos.size()-1)
        return true;

    else {
        // Guardamos el maximo de los valores en el lado izquierdo
        // y el menor de los valores en el lado derecho
        int max = 0, min = 300001;

        for (int i = 0; i <= posicion; i++)
        {
            // Detecta el mayor de los valores de p a la izquierda
            if (datos[i] > max)
                max = datos[i];
        }

        for (int i = posicion + 1; i < datos.size(); i++)
        {
            if (datos[i] < min)
                min = datos[i];
        }

        // El lado izquierdo tiene que ser estrictamente menor
        if (max < min) {
            return true;
        }

    }
    return false;
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