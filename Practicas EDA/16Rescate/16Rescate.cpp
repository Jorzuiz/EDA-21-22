// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ70

#include <iostream>
#include <iomanip>
#include <fstream> 
#include <vector>

using namespace std;


// El coste es lineal O(n)
// Recorremos el vector hasta el final y devolvemos el tramo máximo
int rescate(int altura, vector<int> v){

    int ini = 0, maxini = 0, maxfin = 0;
    int max = 0, actual = 0;
    if (altura == 0) { cout << 0 << " "; return v.size(); }

    for (int i = 0; i < v.size()-1; i++)
    {
        // Cada vez que superemos la altura tenemos que comprobar 
        // si estamos en racha o acabamos de iniciar
        if (v[i] > altura) {
            if(actual > 0){     // Ampliamos la secuencia
                actual += 1;
            }
            else {              // Iniciamos la secuencia
                ini = i;
                actual = 1;
            }
        }
        // Si la altura no es menor tenemos que comprobar si hemos acabado la secuencia
        else {  
            // Guardamos la secuencia si es la mayor

            // Acabamos la secuencia y reiniciamos para el próximo bucle
            if (actual > 0) {   
                if (actual > max){ // Si la secuencia es la mayor hasta el momento la guardamos
                    max = actual;
                    maxini = ini;
                    maxfin = i - 1;     // Al acabar la secuencia el fin ha sido el número anterior
                }

                // De lo contrario la reiniciamos
                actual = 0;
            }            
        }
    }

    cout << maxini << " ";
    return maxfin;
}

int casoRescate(int numero) {

    vector <int> v;
    int altura, aux;

    cin >> altura;
    for (int i = 0; i < numero; i++)
    {
        cin >> aux;
        v.push_back(aux);
    }

    int devuelve = rescate(altura, v);
    return devuelve;     
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    // leer los datos de la entrada

    int numero;
    cin >> numero;
    cout << casoRescate(numero) << "\n";
    // escribir sol

}

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
    system("PAUSE");
#endif

    return 0;
}