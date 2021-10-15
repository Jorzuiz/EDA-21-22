// Jorge Zurdo Izquierdo
// VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


// función que resuelve el problema
// n es numero de artistas
int resolver(vector<vector<int>>& beneficios, vector<vector<bool>>& consentimientos, int artist, int val, const int& size, int maxval) {

    // Condicion final
    if (artist >= 2) {
        if (val > maxval)   
            maxval = val;
        return maxval;
    }
    else
    {
        // una ejecucion por cada artista
        for (int i = 0; i < size; i++)
        {
            // Comprobamos si el artista puede tocar despues de artista I
            if (consentimientos[artist][i]) {
                // Llamada recursiva y sumamos el dinero
                resolver(beneficios, consentimientos, artist + 1, val + beneficios[artist][i], size, maxval);
            }

            // De lo contrario continuamos con el siguiente artista
        }
    }

    return maxval;
}




void resuelveCaso() {

    int n;
    cin >> n;

    // vector con las posibles ganancias segun el orden
    vector<vector<int>> beneficios(n, vector<int>(n));
    // Vector con el orden en el que los grupos admiten tocar
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

    // index 0 inicia la cuenta del algoritmo
    int val = resolver(beneficios, consentimientos, 0, 0, n, 0);

    if (val > 0)    std::cout << val << "\n";
    else            std::cout << "NEGOCIA CON LOS ARTISTAS" << "\n";

}


//#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}

