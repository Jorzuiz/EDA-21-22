// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ70

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

// Comprueba si un número está en la posición correcta
// Partiendo del primero, si todos son consecutivos podemos calcular cual número
// DEBERIA de ocupar pos
//  2   4   6   7   8   10
//  2   4   6   8   10  12      La posicion 3 DEBERIA ser 8
int compruebaPos(int prim, int pos) {
	return prim + 2 * pos;
}

// Comparamos
int comp(int uno, int dos) {

	if (uno == dos) return 1;       // Si el numero es igual, 1 indica que busquemos a la derecha
	else if (uno > dos) {           // Si el numero es mayor
		if (uno % 2 > 0) {
			return 0;               // Si es impar, 0 indica que lo hemos encontrado
		}
		// De lo contrario 2 indica que busquemos a la izquierda
	}
	return 2;
}

// Función que resuelve el problema
// Se ayuda de los metods auxiliares para la claridad de código en la búsqueda 
// mediante divida y vencerás
// Complejidad de log(n) dado que descarta el vector por mitades
int resolver(const vector<int>& sec, int ini, int fin) {

	// Caso base ERROR
	if (fin - ini == 1) return sec[ini];
	// Caso base tamaño 1

	if ((fin - ini) == 2) {
		if (sec[ini] % 2 == 0) return sec[ini + 1];
		else return sec[ini];
	}

	int mid = (ini + fin) / 2;
	if (sec[mid] % 2 != 0)  return sec[mid];
	// Comparamos el número actual, con el que predecimos que debería ocuparlo
	int busqueda = comp(sec[mid], compruebaPos(sec[0], mid));
	if (busqueda == 0) {
		return sec[mid]; // Si ha devuelto 0, la posición que hemos comprobado es la que buscamos; Es impar
	}
	else if (busqueda == 1) { return resolver(sec, mid, fin); }  // Si ha devuelto uno, tenemos que buscar en la mitad derecha
	return resolver(sec, ini, mid);                       // De la contrario buscamos en la izquierda

	//return 0;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int n;
	cin >> n;
	if (n == 0) return false;
	vector<int> sec(n);
	for (int& e : sec) cin >> e;
	cout << resolver(sec, 0, n) << "\n";
	return true;
}

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