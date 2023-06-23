/*
Nombre completo:    Jorge Zurdo Izquierdo
DNI:                12344685X
Usuario del juez:   VJ70
Puesto de laboratorio:  Pto0219
Qué has conseguido hacer y qué no:
Diseñado el TAD y las operaciones, indicados los costes.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <map>
#include <queue>

using namespace std;


class Fecha {
    int _dia, _mes, _anio;

public:
    Fecha(int d = 0, int m = 0, int a = 0) : _dia(d), _mes(m), _anio(a) {}
    int dia() const { return _dia; }
    int mes() const { return _mes; }
    int anio() const { return _anio; }
    bool operator<(Fecha const& other) const {
        return _anio < other._anio ||
            (_anio == other._anio && _mes < other._mes) ||
            (_anio == other._anio && _mes == other._mes && _dia < other._dia);
    }
};

inline std::istream& operator>>(std::istream& entrada, Fecha& h) {
    int d, m, a; char c;
    std::cin >> d >> c >> m >> c >> a;
    h = Fecha(d, m, a);
    return entrada;
}

inline std::ostream& operator<<(std::ostream& salida, Fecha const& f) {
    salida << std::setfill('0') << std::setw(2) << f.dia() << '/';
    salida << std::setfill('0') << std::setw(2) << f.mes() << '/';
    salida << std::setfill('0') << std::setw(2) << f.anio();
    return salida;
}

using Codigo = string;
using Cliente = string;

struct infoProducto {
    // Cuando localizamos un producto nuevo vemos la cola que hay esperando para evitar hacer inserciones innecesarias
    std::queue<Cliente> cola;
    //int tamCola;  // Cola ya tiene un tamaño interno, DUH!!
    std::map<Fecha, int> almacen;
    int stock;
};

class Tienda {
private:
    // Pedidos y colas ordenadas por clave de producto
    std::map<Codigo, infoProducto> pedidos;

public:

    // Insertar requiere buscar primero en la lista de productos por la clave O(logN) donde N es el numero de productos
    // Si el producto existe se intenta vender iterando cola.size() veces o cant veces
    // Si quedan unidades sin vender se busca en el segundo mapa para introducir la fecha O(logM) donde M es el numero de fechas
    // En caso de no existir el producto o la fecha el coste de insertar es O(logN) o O(logM)
    vector<Cliente> adquirir(Codigo const& cod, Fecha const& f, int cant) {

        // Primero intenta servir a los clientes y los carga en el vector de salida
        vector<Cliente> servidos;

        auto itProducto = pedidos.find(cod);                            // Localiza el producto
        if (itProducto != pedidos.end()) {                              // SI EXISTE EL PRODUCTO
            while (itProducto->second.cola.size() > 0 && cant > 0) {    // Intenta venderlo antes de almacenarlo
                servidos.push_back(itProducto->second.cola.front());
                itProducto->second.cola.pop();
                cant--;
            }                                                      
            if (cant > 0) {                                             // Si quedan productos que no se han vendido
                auto itStock = itProducto->second.almacen.find(f); {    // Busca la fecha para añadir
                    if (itStock != itProducto->second.almacen.end()) {  // Si la fecha ya existe
                        itStock->second += cant;
                    }
                    else {                                              // Si no existe la fecha
                        itProducto->second.almacen.insert({ f,cant });  // La añade al almacen
                    }
                    itProducto->second.stock += cant;                   // En ambos casos suma el stock
                }
            }
        }
        else { // SI NO EXISTE EL PRODUCTO, tampoco existe la cola, asique lo crea y mete en stock
            infoProducto nuevo;
            nuevo.stock = cant;
            nuevo.almacen.insert({ f, cant });  // Ambos insert tienen coste de insertar en un mapa vacío
            pedidos.insert({cod ,nuevo});
        }

        return servidos; // Devuelve los clientes que han sido servidos de haberlos
    }

    // Coste de O(LogN) en la busqueda de de N productos
    // En caso de venderse y agotarse un producto el coste de erase es O(logM) donde M es el número de fechas
    pair<bool, Fecha> vender(Codigo const& cod, Cliente const& cli) {

        pair<bool, Fecha> exito;
        exito.first = false;

        auto itProducto = pedidos.find(cod);
        if (itProducto != pedidos.end()) {          // En caso de existir el producto O(logN)
            if (itProducto->second.stock > 0) {     // Si el stock está por encima de 0 tenemos al menos un producto 
                exito.first = true;
                auto primeraFecha = itProducto->second.almacen.begin();
                exito.second = primeraFecha->first;
                itProducto->second.stock--; 
                primeraFecha->second--;
                if (primeraFecha->second == 0)                  // Si se ha agotado el producto elimina la fecha
                    itProducto->second.almacen.erase(primeraFecha);     // El coste de erase es 0(logN)
            }
            else {                                  //  Si el stock está en 0 tenemos que poner al cliente a esperar 
                itProducto->second.cola.push(cli);
            }
        }
        else {                                      // Si el producto no existe crea una cola
            infoProducto nuevo;
            nuevo.stock = 0;
            nuevo.cola.push({ cli });
            pedidos.insert({ cod ,nuevo });
        }
        return exito;
    }

    // Coste es find (log N) donde N es el tamaño del mapa pedidos
    // El valor de totales ya se ha actualizado al guardarlo, el acceso es constante
    int cuantos(Codigo const& cod) const {
        int cant = 0;
        auto it = pedidos.find(cod);
        if (it != pedidos.end())  cant = it->second.stock;
        return cant;
    }

    // Coste es find (log N) donde N es el tamaño del mapa pedidos
    // Al guardarse en un cola, comprobar el tamaño es un acceso constante
    bool hay_esperando(Codigo const& cod) const {

        auto itProducto = pedidos.find(cod);
        if (itProducto == pedidos.end())   return false;       // Producto no existe

        if (itProducto->second.cola.size() > 0) return true;
        return false;   // No hay cola para el producto
    }
};

bool resuelveCaso() {
    std::string operacion, cod, cli;
    Fecha f;
    int cant;
    std::cin >> operacion;
    if (!std::cin)
        return false;

    Tienda tienda;

    while (operacion != "FIN") {
        if (operacion == "adquirir") {
            cin >> cod >> f >> cant;
            vector<Cliente> clientes = tienda.adquirir(cod, f, cant);
            cout << "PRODUCTO ADQUIRIDO";
            for (auto c : clientes)
                cout << ' ' << c;
            cout << '\n';
        }
        else if (operacion == "vender") {
            cin >> cod >> cli;
            pair<bool, Fecha> venta = tienda.vender(cod, cli);
            if (venta.first) {
                cout << "VENDIDO " << venta.second << '\n';
            }
            else
                cout << "EN ESPERA\n";
        }
        else if (operacion == "cuantos") {
            cin >> cod;
            cout << tienda.cuantos(cod) << '\n';
        }
        else if (operacion == "hay_esperando") {
            cin >> cod;
            if (tienda.hay_esperando(cod))
                cout << "SI\n";
            else
                cout << "NO\n";
        }

        std::cin >> operacion;
    }
    std::cout << "---\n";
    return true;
}


//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("input3.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}