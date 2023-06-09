// VJ70
// Jorge Zurdo Izquierdo

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <map>

class carnet_puntos {

private:
    std::map<std::string, int> base;
    int aPuntos[16]; // Cuenta cuantas personas tienen N puntos; las posiciones son los puntos

public:
    void nuevo(const std::string& dni) {
        //std::unordered_map<std::string, int>::iterator it = base.find(dni);
        auto it = base.find(dni);
        if (it != base.end()) throw std::domain_error("Conductor duplicado");
        aPuntos[15]++;
        base.insert({ dni, 15 });
    }

    void quitar(const std::string& dni, const int& puntos) {
        //std::unordered_map<std::string, int>::iterator it = base.find(dni);
        auto it = base.find(dni);
        if (it == base.end()) throw std::domain_error("Conductor inexistente");
        aPuntos[it->second]--;
        it->second -= puntos;
        if (it->second < 0) it->second = 0;
        aPuntos[it->second]++;
    }

    int consultar(const std::string& dni) {
        //std::unordered_map<std::string, int>::iterator it = base.find(dni);
        auto it = base.find(dni);
        if (it != base.end()) return it->second;
        else throw std::domain_error("Conductor inexistente");
    }
    
    int cuantos_con_puntos(const int& puntos) {
        if (puntos < 0 || puntos >15) throw std::domain_error("Puntos no validos");
        return aPuntos[puntos];
    }
};

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;

    carnet_puntos dgt;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                std::cin >> dni;
                dgt.nuevo(dni);
            }
            else if (orden == "quitar") {
                std::cin >> dni >> punt;
                dgt.quitar(dni, punt);
            }
            else if (orden == "consultar") {
                std::cin >> dni;
                punt = dgt.consultar(dni);
                std::cout << "Puntos de " << dni << ": " << punt << '\n';
            }
            else if (orden == "cuantos_con_puntos") {
                std::cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                std::cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            }
            else
                std::cout << "OPERACION DESCONOCIDA\n";
        }
        catch (std::exception& e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {

    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("pause");
#endif
    return 0;
}
