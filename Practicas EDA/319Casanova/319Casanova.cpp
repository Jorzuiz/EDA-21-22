// Jorge Zurdo Izquierdo
// VJ63

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

struct Cancion {
    int duracion;
    int puntos;
    float calidad; // Puntuación por minuto
};

struct Solucion {
    // La solucion ordena las canciones en cara A (1) cara B (2) o no seleccionada (0
    vector<int> cinta;  
    int k = 0;
    int num;
    // Almacenamos la ocupación actual de cada cara
    int ocupacionA = 0;
    int ocupacionB = 0;
    // Guardamos la puntuación actual y el máximo entre las iteraciones
    int puntuacion = 0;
    int maxpuntuacion = -1;
    Solucion(int n) : cinta(vector<int>(n)), num(n) {};
};


// El vector de solución indica cada canción si va en la cara A, B o ninguna
void resolver(Solucion& sol, vector<Cancion>& canciones, int duracion, vector<int> maxPuntAcc) {
    // Intentamos insertar la canción en la cara A
    // La duracion que llevamos ocupada mas la cancion actual no puede superar el total
    if ((sol.ocupacionA + canciones[sol.k].duracion <= duracion))
    {
        sol.cinta[sol.k] = 1;                           // Asignacion 1 es cara A
        sol.ocupacionA += canciones[sol.k].duracion;    // Añadimos los minutos nuevos
        sol.puntuacion += canciones[sol.k].puntos;      // Añadimos los puntos nuevos
        
        // Si estamos en la cancion final registramos la nueva máxima puntuación
        if (sol.k == sol.num - 1) {
            if (sol.puntuacion > sol.maxpuntuacion) sol.maxpuntuacion = sol.puntuacion;
        }
        // De lo contrario llamamos reiterativamente a la iteración k + 1
        else {
            sol.k++;
            // Comparamos con la mayor puntuacion posible para evitar explorar opciones inútiles
            if(sol.puntuacion + maxPuntAcc[sol.k] > sol.maxpuntuacion)
                resolver(sol, canciones, duracion, maxPuntAcc);
            sol.k--;
        }

        // Tras las iteraciones reiniciamos
        sol.ocupacionA -= canciones[sol.k].duracion;
        sol.puntuacion -= canciones[sol.k].puntos;
    }

    // Intentamos la cara B
    if (sol.ocupacionA != sol.ocupacionB && ((sol.ocupacionB + canciones[sol.k].duracion) <= duracion)) {
        if ((sol.ocupacionB + canciones[sol.k].duracion <= duracion))
        {
            sol.cinta[sol.k] = 2;   // Asignacion 2 es cara B
            sol.ocupacionB += canciones[sol.k].duracion;
            sol.puntuacion += canciones[sol.k].puntos;
            if (sol.k == sol.num - 1) {
                if (sol.puntuacion > sol.maxpuntuacion) sol.maxpuntuacion = sol.puntuacion;
            }
            else {
                sol.k++;            
                if (sol.puntuacion + maxPuntAcc[sol.k] > sol.maxpuntuacion)
                    resolver(sol, canciones, duracion, maxPuntAcc);
                sol.k--;
            }
            sol.ocupacionB -= canciones[sol.k].duracion;
            sol.puntuacion -= canciones[sol.k].puntos;
        }
    }

    // Canción descartada (ninguna cara)
    sol.cinta[sol.k] = 0;
    if (sol.k == sol.num - 1) {
        if (sol.puntuacion > sol.maxpuntuacion) sol.maxpuntuacion = sol.puntuacion;
    }
    else {
        sol.k++;            
        if (sol.puntuacion + maxPuntAcc[sol.k] > sol.maxpuntuacion)
            resolver(sol, canciones, duracion, maxPuntAcc);
        sol.k--;
    }
}

// Usando el ultimo elemento como pivote ordena todos 
// los valores menores y coloca el pivote al final de ellos
int divide(vector<Cancion>& canciones, int ini, int fin) {
    // Pivote elegido a mano
    Cancion pivote = canciones[fin];
    
    int i = (ini - 1);    // Indice para los elementos menores
    // cuando acaba el algoritmo indica la posición correcta del pivote

    // La iteracion final no es necesaria porque es el pivote
    for (int j = ini; j <= fin - 1; j++)
    {
        //Si el elemento es menor que el pivote
        if (canciones[j].calidad > pivote.calidad)
        {
            i++;    // Marcador de pivote actual
            swap(canciones[i], canciones[j]);
        }
    }
    // Devolvemos el pivote a su posición definitiva
    swap(canciones[i + 1], canciones[fin]);
    return (i + 1);
}

// Ordena las canciones basandose en su puntuación por minuto
// Basado en quicksort
void controlDCalidad(vector<Cancion>& canciones, int ini, int fin) {
    int pivote;

    if (ini < fin) {
        pivote = divide(canciones, ini, fin);

        // Pivote ya se encuentra en su valor correcto
        controlDCalidad(canciones, ini, pivote - 1);
        controlDCalidad(canciones, pivote + 1, fin);
    }

}

// Comprueba que la tupla solución está compuesta de 2 pistas
bool esSolucion() { return true; }

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int numCanciones, duracion;
    cin >> numCanciones;
    if (numCanciones == 0) return false;
    cin >> duracion;

    vector<int> solucion(numCanciones);
    // Vector de pares Duración/Puntos
    vector<Cancion> canciones(numCanciones);
    for (int i = 0; i < numCanciones; ++i) {
        cin >> canciones[i].duracion >> canciones[i].puntos;
        canciones[i].calidad = (float)canciones[i].puntos / canciones[i].duracion;
    }
    Solucion sol(numCanciones);

    // Organizamos las canciones de mayor a menor calidad para que
    // el algoritmo sea más eficiente en la poda
    controlDCalidad(canciones, 0, canciones.size() - 1);
    //std::reverse(canciones.begin(), canciones.end());

    // Creamos un vector para calcular las calidades acumulativas
    vector<int> maxPuntAcc(numCanciones);
    maxPuntAcc[numCanciones-1] = canciones[numCanciones-1].puntos;
    for (int i = numCanciones - 2; i >= 0; i--)
        maxPuntAcc[i] = maxPuntAcc[i+1] + canciones[i].puntos;


    resolver(sol, canciones, duracion, maxPuntAcc);
    // Salida
    cout << sol.maxpuntuacion << "\n";
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
