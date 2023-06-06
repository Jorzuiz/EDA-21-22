// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <fstream>
#include <algorithm>

#include <string>
#include <vector>
#include <unordered_map>

#include <exception>
#include <stdexcept>

using Estado = std::string;
using Partido = std::string;

class ConteoVotos {

private:

    using Partidos = std::unordered_map<std::string, int>;

    struct infoEstado {  // Cada valor de estado tiene la info de los compromisarios y un mapa con los partidos
        int compromisarios;
        //std::unordered_map<std::string, infoPartido> partidos;
        Partidos partidos;
    };

    using Estados = std::unordered_map<Estado, infoEstado>;
    //std::unordered_map<Estado, infoEstado> estados; // Mapa de los estados
    Estados estados;

    // La estructura queda tal que <NombreEstado, <compromisarios, <partido, votos>>>
public:

    // Insert del estado
    void nuevo_estado(const Estado& nombre, int num_compromisarios) {
        Estados::iterator it = estados.find(nombre);
        if (it == estados.end()) {
            infoEstado infE;
            infE.compromisarios = num_compromisarios;
            estados.insert({ nombre, infE });
        }
        else throw std::domain_error("Estado ya existente");
    }

    void sumar_votos(const Estado& estado, const Partido& partido, int num_votos) {
        Estados::iterator itE = estados.find(estado);
        if (itE != estados.end()) {
            std::unordered_map<std::string, int>::iterator itP = itE->second.partidos.find(partido);

            // Si el partido existe le suma los votos, de lo contrario lo crea
            if (itP != itE->second.partidos.end()) itP->second += num_votos;
            else itE->second.partidos.insert({ partido, num_votos });
        }
        else throw std::domain_error("Estado no encontrado");
    }

    Partido ganador_en(const Estado& estado) const {
        Partido ganador;
        Estados::const_iterator itE = estados.find(estado);
        if (itE != estados.end()) {
            int maxVotos = 0;
            Partidos::const_iterator itP = itE->second.partidos.begin();
            while (itP != itE->second.partidos.end()) {
                if (itP->second > maxVotos) {
                    maxVotos = itP->second;
                    ganador = itP->first;
                }
                itP++;
            }

        }
        else throw std::domain_error("Estado no encontrado");
        return ganador;
    }

    std::vector<std::pair<Partido, int>> resultados() const {
        std::vector<std::pair<Partido, int>> ganadores;
        Estados::const_iterator itE = estados.begin();
        while (itE != estados.end()) {
            ganadores.push_back(make_pair(ganador_en(itE->first), itE->second.compromisarios));
            itE++;
        }
        // El vector contiene los partidos por orden alfabético y los compromisarios en cada estado
        std::sort(ganadores.begin(), ganadores.end());
        // Resta sumar los compromisarios de cada partido
        std::vector<std::pair<Partido, int>>::const_iterator itG = ganadores.begin();
        std::vector<std::pair<Partido, int>> totales;
        Partido aux = itG->first;
        int totalCompromisarios = itG->second;
        itG++;

        while (itG != ganadores.end()) {
            if (aux == itG->first) {
                // Sumamos los compromisarios del mismo estado
                totalCompromisarios += itG->second;
            }
            else {
                // Cargamos y actualizamos al estado siguiente
                totales.push_back(make_pair(aux, totalCompromisarios));
                aux = itG->first;
                totalCompromisarios = itG->second;
            }
            itG++;
        }
        totales.push_back(make_pair(aux, totalCompromisarios));

        return totales;
    }

};


bool resuelveCaso() {
    std::string comando;
    std::cin >> comando;
    if (!std::cin) return false;

    ConteoVotos elecciones;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                Estado estado;
                int num_compromisarios;
                std::cin >> estado >> num_compromisarios;
                elecciones.nuevo_estado(estado, num_compromisarios);
            }
            else if (comando == "sumar_votos") {
                Estado estado;
                Partido partido;
                int num_votos;
                std::cin >> estado >> partido >> num_votos;
                elecciones.sumar_votos(estado, partido, num_votos);
            }
            else if (comando == "ganador_en") {
                Estado estado;
                std::cin >> estado;
                Partido ganador = elecciones.ganador_en(estado);
                std::cout << "Ganador en " << estado << ": " << ganador << "\n";
            }
            else if (comando == "resultados") {
                for (const auto& par : elecciones.resultados()) {
                    std::cout << par.first << " " << par.second << "\n";
                }
            }
        }
        catch (std::exception& e) {
            std::cout << e.what() << "\n";
        }
        std::cin >> comando;
    }

    std::cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso()) {}

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
