// Jorge Zurdo Izquierdo
// VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

struct Solucion {
    int artistas;
    int ganancias = -1;
    int maxGanancias = -1;
    vector<vector<int>> beneficios;
    vector<vector<bool>> consentimientos;

    Solucion(int n) :
    beneficios(vector<vector<int>>(n)),
    consentimientos(vector<vector<bool>>(n)),
    artistas(n) {}
};


// función que resuelve el problema
// n es numero de artistas
//int resolver(vector<vector<int>>& beneficios, vector<vector<bool>>& consentimientos, int artist, int val, const int& size, int maxval) {
int resolver(Solucion& sol, int k) {

    // vector<int>& soluc, int k, int n, int ingresos, int& mejoresIngresos, vector<bool>& elegidos,
    // const vector<vector<int>>&beneficios, const vector<vector<bool>>& consentimientos, const vector <int> mejoresBeneficios 

    int n = 0;
    for (int i = 0; i < n; i++)
    {
        soluc[k] = i;
        if(esvalida(soluc,k,elegidos,consentimientos)){
            ingresos+= beneficios[i][k];
            elegidos[i] = true;
            if(k == n-1){
                if(ingresos > mejoresIngresos) mejoresIngesos = ingresos;
            }else{
                resolver(sol, k+1);
            }
            ingresos -= beneficios[i][k];
            elegidos[i] = false;
        }
    }
    


    //return maxval;
}

bool esvalida(const vector<int>& soluc, int k, const vector<int> elegidos, const vector<vector<bool>>& consentimientos)
{
    return (!elegidos[soluc[k]] && (k==0 || consentimientos[soluc[k]][soluc[k-1]]));
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

    // Recorre filas y columnas de beneficios 
    // buscando el maximo income posible
    vector<int> maxBenefs(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(beneficios[i][j]>maxBenefs[i]) 
            maxBenefs[i]==beneficios[i][j];
        }
    }
    
    // Calcula el maximo beneficio posible restante en cada columna
    vector<int> maxBenefsDesde(n);
    maxBenefsDesde[n-1] = maxBenefs[n-1];
    for (int i = n-2; i >= 0; i--)
    {
        maxBenefsDesde[i] += maxBenefsDesde[i+1];
    }


    vector<int> soluc(n);
    int k = 0;
    int ingresos = 0;
    int mejoresIngresos =-1;
    vector<bool> elegidos(n);
    //resolver(soluc, k, n, ingteos, mejoresIngresos, elegidos, beneficios, consentimientos,mejoresBeneficios);
    if(mejoresIngresos == -1) cout << "NEGOCIA CON LOS ARTISTAS\n";
    else cout << mejoresIngresos << endl;
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

