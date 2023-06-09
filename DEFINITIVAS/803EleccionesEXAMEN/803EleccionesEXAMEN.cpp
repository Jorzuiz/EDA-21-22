// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <fstream>
#include <algorithm>

#include <string>
#include <vector>
#include <map>
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
        std::string partidoMax;
        int votosMax;

        Partidos partidos;
    };

    // Se necesitan metodos para actualizar los numeros de compromisarios por partido
    std::map<Partido, int> compromisarios;
    using Estados = std::unordered_map<Estado, infoEstado>;
    Estados mEstados;

    // La estructura queda tal que <NombreEstado, <compromisarios, <partido, votos>>>
public:

    void nuevo_estado(const Estado& nombre, int num_compromisarios) {
        Estados::iterator it = mEstados.find(nombre);
        if (it == mEstados.end()) {
            infoEstado infE;
            infE.compromisarios = num_compromisarios;
            mEstados.insert({ nombre, infE });
        }
        else throw std::domain_error("Estado ya existente");
    }

    void updateCompromisarios(Partido partido1, Partido partido2, int _compromisarios){
        auto it = compromisarios.find(partido1);
        if (it != compromisarios.end()) compromisarios.at(partido1) -= _compromisarios;
        
        it = compromisarios.find(partido2);
        if (it != compromisarios.end()) compromisarios.at(partido2) += _compromisarios;
        else compromisarios.insert({ partido2, _compromisarios });
        return;
    }

    // Actualiza el partido más votado del estado si procede
    void updateMax(Estados::iterator& estado, Partidos::iterator& partido) {
        // partido->first == string         partido->second == votos
        if (partido->second > estado->second.votosMax) {
            updateCompromisarios(estado->second.partidoMax, partido->first, estado->second.compromisarios);
            estado->second.partidoMax = partido->first;
            estado->second.votosMax = partido->second;
        }
    }

    void sumar_votos(const Estado& estado, const Partido& partido, int num_votos) {

        Estados::iterator itE = mEstados.find(estado);
        if (itE == mEstados.end()) throw std::domain_error("Estado no encontrado");

        std::unordered_map<std::string, int>::iterator itP = itE->second.partidos.find(partido);
        // Si el partido existe le suma los votos, de lo contrario lo crea
        if (itP != itE->second.partidos.end()) itP->second += num_votos;
        // El insert devuelve un pair con informacion del iterador donde se guarda y un bool que dice si ha sido exitoso
        else itP = itE->second.partidos.insert({ partido, num_votos }).first;
        updateMax(itE, itP);
    }

    Partido ganador_en(const Estado& estado) const {
        Estados::const_iterator itE = mEstados.find(estado);
        if (itE == mEstados.end())  throw std::domain_error("Estado no encontrado");
        return itE->second.partidoMax;
    }

    std::vector<std::pair<Partido, int>> resultados() const {

        std::vector<std::pair<Partido, int>> ganadores;
        Estados::const_iterator itE = mEstados.begin();
        while (itE != mEstados.end()) {
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

        auto it = compromisarios.begin();
        for(const &auto it : compromisarios)
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
