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

void densidad(vector<Cancion> &canciones, vector<int> &den){
    for (int i = 0; i < canciones.size(); i++)
    {
        den[i] = canciones[i].duracion / canciones[i].puntos;
    }
    return;
}

void resolver(int k, int n, int duracion, int cara, vector<int>& soluc, int pActuales, int dActuales, vector<Cancion>& canciones, int &maxPuntos) {

    // Añade la cancion a la cara solo si no está en una cara
    if (soluc[k] == 0) {
        // Marcado de solucion
        soluc[k] = cara;
        pActuales += canciones[k].puntos;
        dActuales += canciones[k].duracion;
        if (dActuales <= duracion) {               // Esvalida
            if (k == n-1) {    // Es solucion
                maxPuntos = max(maxPuntos, pActuales);  // Trata solucion
            }
            // Posible poda aqui
            // if (current + optimista[k] < maxPuntos)
            else resolver(k + 1, n, duracion, cara, soluc, pActuales, dActuales, canciones, maxPuntos);
        }
        pActuales -= canciones[k].puntos;
        dActuales -= canciones[k].duracion;
    }

    // Si la canción ya está en la otra cara o se ha desmaracado
    else {
        soluc[k] = 0;
        if (k == n - 1) {    // Es solucion
            maxPuntos = max(maxPuntos, pActuales);  // Trata solucion
        }
        // Posible poda aqui
        // if (current + optimista[k] < maxPuntos)
        else resolver(k + 1, n, duracion, cara, soluc, pActuales, dActuales, canciones, maxPuntos);
    }

}

void resolverB(int k, int n, int cara, vector<int> soluc, vector<Cancion> canciones, int maxPuntos){}

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
    densidad(canciones, den);

    int puntosA=0, puntosB=0;
    resolver(0, n, duracion, 1, soluc, 0, 0, canciones, puntosA);    // Calcula los maximos puntos posibles en la primera cara
    resolver(0, n, duracion, 2, soluc, 0, 0, canciones, puntosB);    // Lo mismo apara la segunda

    // Salida
    cout << puntosA + puntosB;
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
