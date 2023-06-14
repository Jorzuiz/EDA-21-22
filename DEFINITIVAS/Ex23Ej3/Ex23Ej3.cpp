// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <fstream>
#include <algorithm> // Sort
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

using namespace std;


struct problema {   // El nombre está guardado clave clave en el mapa
    string veredicto;
    int fallos;
};

// Estructura personalizada para ordenar el vector posteriormente
struct sResultados {
    int resueltos;
    int tiempoGlobal;
    string nombre;    

    bool operator>(const sResultados& b) const {
        return (resueltos > b.resueltos) ||   // Si tiene más casos
            (resueltos == b.resueltos) && (tiempoGlobal < b.tiempoGlobal) ||   // Si tienen igual pero el tiempo es mejor
            (resueltos == b.resueltos) && (tiempoGlobal == b.tiempoGlobal) && (nombre < b.nombre);    // Alfabéticamente por defecto
    };
};

struct sEquipo{     // El nombre está guardado clave clave en el mapa
    int resueltos;
    int tiempoGlobal;
    unordered_map<string, problema> problemas;  // No es necesario ordenar por nombre
};

class clasificacion {
private:
    unordered_map<string, sEquipo> equipos;
public:

    // 2 find y un insert, constante
    void nuevoCaso(string equipo, string problema, int tiempo, string veredicto) {
        auto itE = equipos.find(equipo);

        int fallos = 0, aciertos = 0;
        if (veredicto == "AC") aciertos = 1;
        if (veredicto != "AC") fallos = 1;

        if (itE != equipos.end()) { // Equipo Encontrado

            if (veredicto == "AC") {    // Un problema resuelto suma a la puntuación
                itE->second.resueltos++;
                itE->second.tiempoGlobal += tiempo;
            }

            auto itP = itE->second.problemas.find(problema);

            if (itP != itE->second.problemas.end()) {   // Problema encontrado
                if (itP->second.veredicto != "AC") {    // Si NO estaba resuelto
                    if (veredicto == "AC") {   // Lo marca como resuelto y suma al equipo
                        itP->second.veredicto = veredicto;
                        itE->second.tiempoGlobal += 20 * itP->second.fallos;    // Suma cada fallo anterior
                    }
                    else // incrementa el contador de fallos si el intento no ha tenido éxito
                        itP->second.fallos++;
                }   // Si estaba resuelto no hace nada
            }
            else { // Problema NO encontrado
                itE->second.problemas.insert({ problema, {veredicto, fallos} });
            }
        }
        else { // Equipo NO encontrado
            equipos.insert({ equipo, {aciertos, tiempo * aciertos, {}}});                                  // Crea el equipo y le inserta un acierto con su tiempo
            equipos.find(equipo)->second.problemas.insert({ problema,{veredicto, fallos} });
        }
    }

    // Crea clasificación, ordena con custom coparator
    // Coste de insercion en bucle de N = numero de equipos
    // Coste de ordenación de N logN
    vector<sResultados> clasifica() {

        vector<sResultados> resultados;
        auto it = equipos.begin();

        while (it != equipos.end()) {
            sResultados temp;
            temp.resueltos = it->second.resueltos;
            temp.tiempoGlobal = it->second.tiempoGlobal;
            temp.nombre = it->first;
            resultados.push_back(temp);
            it++;
        }

        // Contiene una sobrecarga customizada para >
        // Según los parámetros del programa
        std::sort(resultados.begin(), resultados.end(), greater<sResultados>());

        return resultados;
    };

};

void procesaEnvios(clasificacion& resultados) {
    string equipo, problema, veredicto;
    int minuto;

    cin >> equipo;
    while (equipo != "FIN") {
        cin >> problema >> minuto >> veredicto;

        resultados.nuevoCaso(equipo, problema, minuto, veredicto);

        cin >> equipo;
    }

    
}

void resuelveCaso()
{
    clasificacion resultados;

    procesaEnvios(resultados);

    vector<sResultados> ordenados = resultados.clasifica();
    for (int i = 0; i < ordenados.size(); i++)
        cout << ordenados[i].nombre << " " << ordenados[i].resueltos << " " << ordenados[i].tiempoGlobal << "\n";

    // Se imprime la salida
    cout << "---\n";
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
    //system("PAUSE");
#endif

    return 0;
}