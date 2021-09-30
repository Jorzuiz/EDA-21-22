// Nombre del alumno Jorge Zurdo Izquierdo
// Usuario del Juez VJ63

#include <iostream>
#include <iomanip>
#include <fstream> 

using namespace std;

int complementario(int numero) {
    
    int factor = 1;
    int digito, digito_complemento, complementario = 0, invertido;
    
    while(factor < numero){

        digito = numero / factor % 10;  // Resto
        digito_complemento = 9 - digito;
        complementario += digito_complemento;

        // Cambiamos al segundo digito en el divisor y el complementario
        factor *= 10; ;
        complementario *= 10;
        
    }

    return complementario / 10;
}

int comp(int n) {
    if (n < 10) {
        return n;
    }
    else {
        int comPre = comp(n / 10);
        int comDig = 9 - (n % 10);
        return comPre * 10 + comDig;

        // if n< 10
        // newpot = 10
        // return 9-n;

        // int comPre = comp(n/10, pot);
        // int comDig = 9 - n % 10;
        // newpot = 10 * pot;
        // return pot * comDig + comPre;

    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    // leer los datos de la entrada

    int numero;
    int size;

    cin >> numero;
    
    cout << complementario(numero) << "\n";
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