
#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>
#include <list>
#include <map>

using cancion = std::string;
using artista = std::string;

class iPud {
private:
    using Cancion = std::string;
    struct infoCancion {
        std::string artist;
        int duration;
    };

    // Base de datos de las canciones para búsqueda rápida
    std::map<Cancion, infoCancion> base;

    std::list<std::pair<Cancion, infoCancion>> lista;      // Si la sustituimos por iteradores???
    //std::list<std::map<Cancion, infoCancion>::iterator> playlist;
    std::list<std::pair<Cancion, infoCancion>> historial; // La lista no tiene repeticiones

public:
    void addSong(std::string song, std::string artista, int duracion){
        // añade a la list ERROR:: ya existe
        std::map<Cancion, infoCancion>::iterator it = base.find(song);
        if (it != base.end()) {
            infoCancion infC;
            infC.artist = artista;
            infC.duration = duracion;
            base.insert({song, infC});
        }
        else throw std::domain_error("ERROR");
    }
    void addToPlaylist(std::string song){
        // añade canción al final de la lista, si ya está no hace nada ERROR:: no existe
        std::map<Cancion, infoCancion>::iterator it = base.find(song);
        if (it == base.end()) throw std::domain_error("ERROR no existe");

        lista.push_back(make_pair(it->first, it->second));
    }
    std::string current(){
        // devuelve la primera de la lista ERROR::vacia
        if (lista.empty()) throw std::domain_error("ERROR vacía");
        return lista.front().first;
    }

    void play(){
        // ELimina la primera cancion y la marca como reproducida ERROR::vacia
        if (lista.empty()) throw std::domain_error("ERROR vacía");
        historial.emplace_back(lista.front());
        lista.pop_front();
    }

    int totalTime(){
        // Duracion de las canciones en la lista, 0 si vacía
        int time = 0;
        std::list<std::pair<Cancion, infoCancion>>::iterator it = lista.begin();
        for (auto const& i : lista)
            time += it->second.duration;
        return time;
    }
    std::list<std::pair<Cancion, infoCancion>> recent(int N){
        // devuelve las N canciones ya reproducidas con play sin repetición
        std::list<std::pair<Cancion, infoCancion>> result;
        std::list<std::pair<Cancion, infoCancion>>::iterator it = lista.begin();
        for (int i = 0; i < N; i++) {
            // Comprobar duplicadas por aqui
            result.emplace_back(*it);
            it++;
        }
        return result;
    }

    void deleteSong(std::string s){
        // Elimina todo rastro de la cancion s
        std::map<Cancion, infoCancion>::iterator it = base.find(s);
        lista.erase(it);
        historial.erase(s);
        base.erase(s);
    }
};

bool resuelve() {
    std::string operacion;
    std::cin >> operacion;
    if (!std::cin)
        return false;
    cancion tit; artista aut; int dur;
    iPud ipud;
    while (operacion != "FIN") {
        try {
            if (operacion == "addSong") {
                std::cin >> tit >> aut >> dur;
                ipud.addSong(tit, aut, dur);
            }
            else if (operacion == "addToPlaylist") {
                std::cin >> tit;
                ipud.addToPlaylist(tit);
            }
            else if (operacion == "current") {
                tit = ipud.current(); // aunque no se hace nada, puede producir error
            }
            else if (operacion == "play") {
                try {
                    std::string tocando = ipud.current(); // para saber si la lista es vacía
                    ipud.play();
                    std::cout << "Sonando " << tocando << '\n';
                }
                catch (std::invalid_argument e) {
                    std::cout << "No hay canciones en la lista\n";
                }
            }
            else if (operacion == "totalTime") {
                std::cout << "Tiempo total " << ipud.totalTime() << '\n';
            }
            else if (operacion == "recent") {
                int N;
                std::cin >> N;
                auto lista = ipud.recent(N);
                if (lista.empty())
                    std::cout << "No hay canciones recientes\n";
                else {
                    std::cout << "Las " << lista.size() << " mas recientes\n";
                    for (auto const& s : lista)
                        std::cout << "    " << s << '\n';
                }
            }
            else if (operacion == "deleteSong") {
                std::cin >> tit;
                ipud.deleteSong(tit);
            }
            else { // operacion desconocida
                assert(false);
            }
        }
        catch (std::invalid_argument e) {
            std::cout << "ERROR " << e.what() << '\n';
        }
        std::cin >> operacion;
    }
    std::cout << "---\n";
    return true;
}

int main() {
    while (resuelve());
    return 0;
}