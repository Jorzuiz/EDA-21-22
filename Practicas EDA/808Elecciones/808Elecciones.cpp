// VJ63
// Jorge Zurdo Izquierdo

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

typedef string Estado;
typedef string Partido;

class ConteoVotos {


private:    // C++ presupone como private cualquier variable que no sea publica o protected

    struct EstadoInfo {                 // Estado que se compone de
        int compromisarios;             // Número de Compromisarios que concede
        map<Partido, int> Resultados;   // Mapa que contiene los partidos y sus votos
    };

    // Conjunto de estados y su información interna
    map<Estado, EstadoInfo> EstadosUnidos;

public:

    // Coste n log(n); El coste de la operación insert
    void nuevo_estado(const Estado& nombre, int numCompromisarios) {

        if (EstadosUnidos.count(nombre))   // Count devuelve 1 si al menos existe un estado
            throw domain_error("Estado ya existente.");

        else {  // Insertamos un estado y asignamos un número de compromisarios
            EstadoInfo estado;
            estado.compromisarios = numCompromisarios;
            EstadosUnidos.insert({ nombre, estado });
        }

    };

    // Coste n log(n); El coste de la operación insert
    void sumar_votos(const Estado& estado, const Partido& partido, int numVotos) {

        if (!EstadosUnidos.count(estado))   // Count devuelve 1 si al menos existe un estado
            throw domain_error("Estado no existente.");
        
        else {
            // Si el partido existe dentro del estado, suma los votos
            if (EstadosUnidos.at(estado).Resultados.count(partido)) {
                EstadosUnidos.at(estado).Resultados.at(partido) += numVotos;
            }
            // Si no existe, crea el partido y los asigna
            else{
                EstadoInfo estado;
                estado.Resultados.insert({ partido, numVotos });
            }
        }
    };

    string ganador_en(const string& estado) const {
 
        // Control de error
        if (!EstadosUnidos.count(estado)) {
            throw std::domain_error("Estado NO encontrado.");
        }

        else {
            map<string, int> partidos = EstadosUnidos.at(estado).Resultados;
            pair<string, int> ganador {"", 0};

            for (map<Partido, int>::iterator it = partidos.begin(); it != partidos.end(); it++)
            {
                if (it->second > ganador.second)
                {
                    ganador.second = it->second;
                    ganador.first = it->first;
                }
            }
            return ganador.first;
        }
    }

    // Devuelve una lista que contiene cada partido y sus votos recibidos en total
    vector<pair<Partido, int>> resultados() const {

        map<Partido, int> ordenados;
        vector<pair<Partido, int>> listaComp;
        string ganador;

        for (const auto& it : EstadosUnidos)
        {
            int compromisarios = it.second.compromisarios;
            ganador = ganador_en(it.first);


            if (ordenados.count(ganador)) {
                ordenados.at(ganador) += compromisarios;
            }
            else {
                // Insertamos en el mapa
                ordenados.insert({ ganador, compromisarios });
            }
        }
        // Cargamos en la lista; No es muy eficiente pero estoy cansado ya
        for (const auto& it : ordenados) {
            listaComp.push_back(it);
        }
        return listaComp;
    };

};


bool resuelveCaso() {

    string comando;
    cin >> comando;
    if (!cin) return false;

    ConteoVotos elecciones;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                Estado estado;  int num_compromisarios;
                cin >> estado >> num_compromisarios;
                elecciones.nuevo_estado(estado, num_compromisarios);
            }
            else if (comando == "sumar_votos") {
                Estado estado;  Partido partido;    int num_votos;
                cin >> estado >> partido >> num_votos;
                elecciones.sumar_votos(estado, partido, num_votos);
            }
            else if (comando == "ganador_en") {
                Estado estado;
                cin >> estado;
                Partido ganador = elecciones.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << "\n";
            }
            else if (comando == "resultados") {
                for (const auto& par : elecciones.resultados()) {
                    cout << par.first << " " << par.second << "\n";
                }
            }
        }
        catch (std::exception& e) {
            cout << e.what() << "\n";
        }
        cin >> comando;
    }

    cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
