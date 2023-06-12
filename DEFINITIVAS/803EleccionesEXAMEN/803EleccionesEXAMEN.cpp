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
    // La estructura queda tal que <NombreEstado, <(compromisarios, partidoMax, votosMax), <partido, votos>>>
public:

    void nuevo_estado(const Estado& nombre, int num_compromisarios) {
        
        Estados::iterator it = mEstados.find(nombre);
        if (it != mEstados.end()) throw std::domain_error("Estado ya existente");
        
        infoEstado infE;
        infE.compromisarios = num_compromisarios;
        mEstados.insert({ nombre, infE });
    }

    // Un mapa auxiliar ordena y almacena una lista de partidos y los compromisarios que tienen en cada momento
    // No contiene infomación de los estados
    void updateCompromisarios(Partido partido1, Partido partido2, int _compromisarios){
        auto it = compromisarios.find(partido1);
        if (it != compromisarios.end()) it->second -= _compromisarios;
        
        it = compromisarios.find(partido2);
        if (it != compromisarios.end()) it->second += _compromisarios;
        else compromisarios.insert({ partido2, _compromisarios });
    }

    // El estado guarda información de cual es el partido con más votos en todo momento
    // Aprovecha la búsqueda del partido cuando se realiza una suma para no realizar otra busqueda más adelante
    void updateMax(Estados::iterator& estado, Partidos::iterator& partido) {
        // partido->first == string partido         partido->second == int votos
        if (partido->second > estado->second.votosMax) {
            updateCompromisarios(estado->second.partidoMax, partido->first, estado->second.compromisarios);
            estado->second.partidoMax = partido->first;
            estado->second.votosMax = partido->second;
        }
    }

    // Al sumar los votos se actualizan los contadores de partidos ganadores en los estados
    // y de compromisarios de cada partido
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
        // Al ser un mapa (BST) se ordena por el primer elemento, en este caso el string (alfabéticamente)
        // Solo tenemos que comprobar que los compromisarios sean mayores que 0
        for(auto &it : compromisarios)  // El iterador por referencia evita copiar el mapa
            if (it.second > 0)
            ganadores.push_back(make_pair(it.first, it.second));

        return ganadores;
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
