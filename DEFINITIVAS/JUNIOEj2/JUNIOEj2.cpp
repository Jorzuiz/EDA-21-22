/*
Nombre completo:    Jorge Zurdo IZquierdo
DNI:                12344685X
Usuario del juez:   VJ70
Puesto de laboratorio:  Pto0219
Qué has conseguido hacer y qué no:
Identificado algoritmo de busqueda binaria, los chars se comportan como int ordenados, solo hay que buscar el numero que falta
La recursion da un algoritmo log N sobre el tamaño
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
// Busqueda binaria entre el valor del primer y ultimo char
// Se buscan el valor que no corresponda a su posicion
// Coste O(log N) al estar ordenados sabemos que tenemos que ir buscando en mitades progresivamente más pequeñas

// El valor num sirve para transformar los char en posiciones
// Cuando un vector empieza por a (99) si le restamos num == 99 nos da la posicion 0 
// Si tenemos c (101) y le restamos 99 nos da la posicion 2
char resolver(const vector<char>& sec, int ini, int fin, int num) {

    if (ini == fin) {                   // Caso base, estamos al lado del valor
        if ((sec[ini] - num) != ini)    // El valor está a la izquierda 
            return sec[ini]-1;
        else                            // El valor está a la derecha
            return sec[ini]+1;
    }
    else{
        int mitad = ini + (fin - ini) / 2;
        if ((sec[mitad] - num) > mitad)                     // Si el valor en la mitad es mayor al valor que DEBERIA estar en la mitad
            return resolver(sec, ini, mitad, num);          // Exploramos mitad izquierda
        else                                                // Si el valor es igual tenemos que buscar por la derecha
            return resolver(sec, mitad + 1, fin, num);      // Exploramos mitad derecha
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    char prim, ult, n;
    cin >> prim >> ult;
    n = ult - prim;
    int cod = prim;             // Valor que convierte char en ascii
    vector<char> sec(n);
    for (char& e : sec) cin >> e;
    // prim sirve para seleccionar el valor absoluto en codificacion ascii
    cout << resolver(sec, 0, n-1, cod) << endl;
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input2.txt");
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