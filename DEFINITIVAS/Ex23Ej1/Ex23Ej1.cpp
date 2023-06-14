// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <fstream>
#include <climits>

#include <vector>
using namespace std;

const int NUM_MONEDAS = 8;
const int valores[NUM_MONEDAS] = { 1,2,5,10,20,50,100,200 };

struct sSol {

};

// función que resuelve el problema
// Sol codifica las monedas usando posiciones sobre valores
// sol(0,1,0,0,0,0,0,0) es una moneda de 2 cent
void resolver(vector<int>& sol, int actual, int caso[], int objetivo, int k, bool& exito, int& resultado) {

    // Cada iteracion probará con diferentes valores de monedas siempre y cuando las haya
    for (int moneda = 0; moneda < caso[k]; moneda++) {
        if (actual <= objetivo && !exito) { // Si quedan soluciones por explorar
            actual += moneda*valores[k];      // Suma acumulador
            sol[k]++;
            resultado += moneda;// Añade moneda a solución
            if (actual == objetivo) {   // Paramos la recursión cuando alcanzamos la primera solución
                exito = true;
            }
            else {   // Posible poda de valores
                resolver(sol, actual, caso, objetivo, k + 1, exito, resultado);
            }
            actual -= moneda * valores[k];      // Suma acumulador
            resultado -= moneda;
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int precio;
    int monedas[NUM_MONEDAS];
    cin >> precio;

    for (int i = 0; i < NUM_MONEDAS; ++i)
        cin >> monedas[i];
    vector<int> soluc(NUM_MONEDAS);

    int actual = 0, res = 0; 
    bool exito = false;
    resolver(soluc, actual, monedas, precio, 0, exito, res);

    // Mostrar salida
    if (exito) {
        cout << res << "\n";
    }
    else
        cout << "IMPOSIBLE" << "\n";
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
