// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ70

// CUESTION: Si no fuesen ordenados no habría manera de recorrerlos con el algoritmo, 
// habría que hacer comparaciones individuales desde el principio de los vectores siempre
// dejando un coste de N^2
// Se puede ordenar facilmente con la funcion sort dejando su conste en N + 2 *( N * log(N))
// y dejando un coste real de N * log(N)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Función que resuelve el problema
// Coste Lineal o(N) con N siendo el tamaño del vector mayor
// solo recorre una vez los vectores añadiendo en las respuestas correspondientes
void comparaListados(vector<string> const& eda, vector<string> const& tpv,
    vector<string>& comunes, vector<string>& soloEda, vector<string>& soloTpv) {

    // EL algoritmo recorre solo una vez el
    int i = 0, j = 0;
    while (i < eda.size() && j < tpv.size()) {

        // Comparamos mayores y menores para saber cual de los dos pseudo-iteradores avanzamos
        // y lo añadimos a cada uno de los vectore correspondientes
        if (eda[i] < tpv[j]) {
            soloEda.push_back(eda[i]);
            i++;
        }
        else if (eda[i] > tpv[j]) {
            soloTpv.push_back(tpv[j]);
            j++;
        }
        else {
            comunes.push_back(eda[i]);
            i++; j++;
        }
    }

    // Cuando hemos acabado uno de los dos vectores tenemos que añadir lo restante del
    // otro al array de solo su asignatura correspondiente
    while (i < eda.size()) {
        soloEda.push_back(eda[i]);
        i++;
    }
    while (j < tpv.size()) {
        soloTpv.push_back(tpv[j]);
        j++;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<string> comunes;
    vector<string> soloEda;
    vector<string> soloTpv;

    // Lectura caso 1
    vector<string> eda(n);
    for (string& e : eda) cin >> e; 
    
    // Lectura caso 2
    cin >> n;
    vector<string> tpv(n);
    for (string& e : tpv) cin >> e;
        // Procesamiento del problema
        comparaListados(eda, tpv, comunes, soloEda, soloTpv);
    
    for (string& e : comunes) cout << e << " ";
        cout << "\n";
    for (string& e : soloEda) cout << e << " ";
        cout << "\n";
    for (string& e : soloTpv) cout << e << " ";
        cout << "\n";

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