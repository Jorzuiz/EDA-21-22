// VJ 70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

// Una solución solo puede ser válida si no se eligen más de 3 productos en un mismo supermercado
bool esValida(const vector<vector<int>>& precios, int n, int m, int k, const vector<vector<bool>>& comprados) {

    vector<int> productos(m, 0);    // Starts the vector at 0
    for (int i = 0; i < k; i++)     // Podamos los cálculos de productos no llegados aún
        for (int j = 0; j < m; j++) {
            if (comprados[i][j]) productos[i] += 1;
            if (productos[i] >= 3)   return false;  // Finds a market with more than 3 products; invalid
        }
    return true;
}

// Asigna una nueva tabla con los posibles ahorros maximos
vector<vector<int>> creaDiff(vector<vector<int>>& precios, int m, int n) {

    vector<vector <int>> diff(m, vector<int> (n));
    int min = INT_MAX;

    for (int i = 0; i < n; i++) {
        
        // Busca el valor minimo en el producto
        for (int j = 0; j < m; j++) 
            if (min > precios[j][i]) min = precios[j][i];
        // Resta el minimo para calcular el posible ahorro acumulado
        // 1143 1200 1760 1000
        //  143  200  760    0
        for (int j = 0; j < m; j++)
            diff[j][i] = precios[j][i] - min;
    }

    return diff;
}


// Función que resuelve el problema
void resolver(vector<vector<int>>& precios, int k, int n, int m, int precioAcumulado, vector<vector<bool>>& comprados, int& mejorGasto,
    vector<vector<int>>& diff) {

    for (int i = 0; i < n; i++)
    {
        for (int j = k; j < m; j++) {

            if (esValida(precios, n, m, k, comprados)) {
                precioAcumulado += precios[j][i];
                comprados[j][i] = true;
                if (k == m - 1) {
                    if (precioAcumulado < mejorGasto) mejorGasto = precioAcumulado;
                }
                else {
                    if (precioAcumulado + diff[j][i] < mejorGasto)
                        resolver(precios, k + 1, n, m, precioAcumulado, comprados, mejorGasto, diff);
                }
                precioAcumulado -= precios[j][i];
                comprados[j][i] = false;
            }
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m, mejorGasto = INT_MAX, k;
    cin >> m >> n;
    vector<vector<int>> precios(m, vector<int>(n));
    vector<vector<bool>> comprados(m, vector<bool>(n));

    // Lectura de datos
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> precios[i][j];

    vector<vector<int>> diff = creaDiff(precios, m, n);

    resolver(precios, 0, n, m, 0, comprados, mejorGasto, diff);
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