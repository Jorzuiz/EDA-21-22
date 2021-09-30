// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ63

#include <iostream>
#include <iomanip>
#include <fstream> 

using namespace std;

// Se ejecuta N veces siendo N el tamaño de la entrada
int complementario(int n) {

    // Caso base de solo 1 digito
    if (n < 10) {
        return 9 - n;
    }
    // Caso recursivo
    else {

        int comPre = complementario(n / 10);    // Reduce el numero y lo llama de manera recursiva
        int comDig = 9 - (n % 10);              // Amacena el complementario del resto; el último dígito
        return comPre * 10 + comDig;

    }
}

int complementarioInvertido(const int& n, int& newpot) {

    // Caso base
    if (n < 10) {
        newpot = 10;    // Potencia usada para la reducción
        return 9 - n;   // devuelve el caso base; El dígito complementario
    }

    else {
        int pot;

        int comPre = complementarioInvertido(n / 10, pot);
        int comDig = 9 - n % 10;    // Guardamos el complementario del dígito

        newpot = 10 * pot;  // Actualizamos la potencia
        return pot * comDig + comPre;

    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    // leer los datos de la entrada

    int numero, pot;
    int size;

    cin >> numero;

    cout << complementario(numero) << " ";
    cout << complementarioInvertido(numero, pot) << "\n";
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