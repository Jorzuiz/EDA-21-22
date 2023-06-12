// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
using namespace std;

int min_cost = INT_MAX;

void calculaOptimista(int n, int m, vector<vector<int>>& precio, vector<int>& optimista){
    int minimo = INT_MAX;
    for (int i = 0; i < n; i++) {
        minimo = INT_MAX;
        for (int j = 0; j < m; j++)
        {
            minimo = min(minimo, precio[j][i]);
        }
        optimista[i] = minimo;
    }
    return;
}

void calculaHasta(vector<int>& optimista, vector<int>& optimistaHasta) {

    //optimistaHasta[0] = optimista[0];
    optimistaHasta[optimista.size() - 1] = optimista[optimista.size()-1];
    //for (int i = 1; i < optimista.size(); i++)
    for (int i = optimista.size()-2; i >= 0; i--)
    {
        //optimistaHasta[i] = optimista[i] + optimistaHasta[i - 1];
        optimistaHasta[i] = optimista[i] + optimistaHasta[i + 1];
    }
    return;
}

// K profundidad, N productos, M supermercados
void resolver(vector<int>& soluc, int k, int n, int m, vector<vector<int>>& precios, int current, int& mejorgasto, vector<int>& compras, vector<int>& optimistaHasta) {

    // Siendo k el producto actual a elegir
    for (int j = 0; j < m; j++) {       // Genera cada posible compra en supermercado
        if (compras[j] < 3 && k < n) {  // Si puede comprar en el supermercado

            soluc[k] = precios[j][k];   // Para comprobar en debug luego
            current += precios[j][k];
            compras[j]++;               // Marcaje; Compras realizadas en el supermercado j

            if (k == n - 1) {
                mejorgasto = min(mejorgasto, current);  // Trata el final de la solución                
            }
            // Poda valores si no van a ser mejores que la solución actual
            else {
                //if (current + optimistaHasta[k] < mejorgasto) {
                    resolver(soluc, k + 1, n, m, precios, current, mejorgasto, compras, optimistaHasta);
                //}
            }
            compras[j]--;
            current -= precios[j][k];
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m, mejorGasto = min_cost;
    cin >> m >> n;

    vector<vector<int>> precios(m, vector<int>(n));
    vector<int> optimista(n);
    vector<int> optimistaHasta(n);
    vector<int> soluc(n);
    vector<int> compras(m); // comprueba cuantas compras hay en cada super
    
    for (int i = 0; i < m; i++) {   // Mercado
        for (int j = 0; j < n; j++) // Producto
        {
            cin >> precios[i][j];
        }
    }
    
    calculaOptimista(n,m,precios, optimista);   // Vector con los minimos valores de cada producto
    calculaHasta(optimista, optimistaHasta);    // Cola de la compra con los minimos valores posibles acumulados

    resolver(soluc, 0, n, m, precios, 0, mejorGasto, compras, optimistaHasta);
    cout << mejorGasto << endl;
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
