// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;


struct Cancion {
    int duracion;
    int puntos;
};

void estimacion(vector<Cancion>& canciones, vector<int>& den) {
    den[canciones.size() - 1] = canciones[canciones.size() - 1].puntos;
    for (int i = canciones.size() - 2; i >= 0; i--)
    {
        den[i] = canciones[i].puntos + den[i + 1];
    }
    return;
}

void resolver(int k, int n, int duracion, vector<int>& soluc, int pActuales, int dActuales, int pBctuales, int dBctuales, vector<Cancion>& canciones, int& maxPuntos, vector<int> & optimista) {


    // Marcado de cara 1
    soluc[k] = 1;
    pActuales += canciones[k].puntos;
    dActuales += canciones[k].duracion;
    if (dActuales <= duracion) {               // Esvalida
        if (k == n - 1) {    // Es solucion
            maxPuntos = max(maxPuntos, pActuales+pBctuales);  // Trata solucion
        }
        // Posible poda aqui
        //else if (pActuales + optimista[k+1] < maxPuntos)
        else resolver(k + 1, n, duracion, soluc, pActuales, dActuales, pBctuales, dBctuales, canciones, maxPuntos, optimista);
    }
    pActuales -= canciones[k].puntos;
    dActuales -= canciones[k].duracion;

    // Marcado de cara 2
    soluc[k] = 2;
    pBctuales += canciones[k].puntos;
    dBctuales += canciones[k].duracion;
    if (dBctuales <= duracion) {               // Esvalida
        if (k == n - 1) {    // Es solucion
            maxPuntos = max(maxPuntos, pActuales + pBctuales);  // Trata solucion
        }
        // Posible poda aqui
        //else if (pBctuales + optimista[k+1] < maxPuntos)
        else resolver(k + 1, n, duracion, soluc, pActuales, dActuales, pBctuales, dBctuales, canciones, maxPuntos, optimista);
    }
    pBctuales -= canciones[k].puntos;
    dBctuales -= canciones[k].duracion;

    // Solución sin marcado
    soluc[k] = 0;
    if (k == n - 1) {    // Es solucion
        maxPuntos = max(maxPuntos, pActuales+pBctuales);  // Trata solucion
    }
    else resolver(k + 1, n, duracion, soluc, pActuales, dActuales, pBctuales, dBctuales, canciones, maxPuntos, optimista);

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, duracion;
    cin >> n;
    if (n == 0) return false;
    cin >> duracion;
    
    vector<int> soluc(n);           // 0 = no está; 1 = cara A; 2 = cara b
    vector<Cancion> canciones(n);
    for (int i = 0; i < n; ++i)
        cin >> canciones[i].duracion >> canciones[i].puntos;
    
    // Posible poda por estimación optimmista
    vector<int> den(n);
    estimacion(canciones, den);

    int puntos=0;
    resolver(0, n, duracion, soluc, 0, 0, 0, 0, canciones, puntos, den);    // Calcula los maximos puntos posibles en la primera cara

    // Salida
    cout << puntos;
    return true;
}

//#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}
