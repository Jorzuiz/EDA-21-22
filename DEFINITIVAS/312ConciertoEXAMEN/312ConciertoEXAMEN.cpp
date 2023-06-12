// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// Comprueba que estamos en K maximo y es una solucion posible
bool esSolucion(vector<vector<bool>>& consentimientos, vector<vector<bool>>& marcaje){
    
}

// Crea un vector temporal que avanza con el recorrido haciendo estimaciones de la mejor solución
bool poda(vector<vector<int>> &beneficios, vector<vector<int>> &consentimientos){}

// función que resuelve el problema
// k es le nivel actual de recorrido, n es el nivel máximo
// El marcaje es la solucion actual que va evolucionando sobre beneficios
void resolver(int k, int n, vector<vector<int>> &beneficios, vector<vector<bool>> &consentimientos, vector<vector<bool>> &marcaje) {
    // artista i, consentimiento j
    int i, int j;
    while (k != n)
        // prueba solucion
        if (esSolucion(consentimientos, marcaje))
        for (i = k; i < n; i++) {
            if (esSolucion(consentimientos)) return;
            else {
                marcaje[i][j] = true;
                resolver(k + 1, n, beneficios, consentimientos, marcaje);
                marcaje[i][j] = false;
            }
        }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<vector<int>> beneficios(n, vector<int>(n));
    vector<vector<bool>> consentimientos(n, vector<bool>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> beneficios[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int b;
            cin >> b;
            consentimientos[i][j] = b;
        }

    vector<vector<bool>> marcaje(n, vector<bool>(n));
    resolver(0, n, beneficios, consentimientos, marcaje);
    // salida
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGEx
    std::ifstream in("input3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
