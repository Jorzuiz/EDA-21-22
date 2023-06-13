template <class T>
class stackLL {
protected:
    struct Nodo{
        Nodo() : sig(nullptr);
        Nodo(T const& e, Nodo* s = nullptr) : elem(e), sig(s) {}
        T elem;
        Nodo* sig;
    }

    Nodo* cima;
    int nelems;

public:
    
    // constructor: pila vacía
    stackLL() : cima(nullptr) {}

    // destructor
    ~stackLL() {
        libera();
    }
    
    // constructor por copia
    stackLL(stackLL<T> const& other) {
        copia(other);
    }
    
    // operador de asignación
    stackLL<T> & operator=(stackLL<T> const& other) {
        if (this != &other) {
            libera();
            copia(other);
        }
        return *this;
    }
    
    // apilar un elemento
    void push(T const& e) {
        cima = new Nodo(e,cima);
        nelems++;
    }
    
    // consultar la cima
    T const& top() const {
        if (empty())
            throw std::domain_error("la pila vacia no tiene cima");
        return cima->elem;
    }
    
    // desapilar el elemento en la cima
    void pop() {
        if (empty())
            throw std::domain_error("desapilando de la pila vacia");
        Nodo* aux = cima;
        cima = cima->sig;
        delete aux;
        nelems--;
    }
    
    // consultar si la pila está vacía
    bool empty() const {
        return nelems == 0;
    }
    
    // consultar el tamaño de la pila
    int size() const {
        return nelems;
    }
    
protected:

    void libera() {
        while (cima != nullptr){
            Nodo* aux = cima;
            cima = cima->sig;
            delete aux;
        }
    }
    
    // this está sin inicializar
    void copia(stackLL const& other) {
        if (other.empty()){
            cima = nullptr;
            nelems = 0;
        } else {
            Nodo* ant;
            Nodo* act = other.cima;
            cima = new Nodo(act->elem);
            ant = cima;
            while (act->sig != nullptr){
                act = act->sig;
                ant->sig = new Nodo(act->elem);
                ant = ant->sig;
            }
        }
        nelems = other.nelems;
    }
};




template <class T>
class queue {
protected:
   
   /*
    Nodo que almacena internamente el elemento (de tipo T),
    y un puntero al nodo siguiente, que puede ser nullptr si
    el nodo es el último de la lista enlazada.
    */
   struct Nodo {
      Nodo() : sig(nullptr) {}
      Nodo(T const& el, Nodo * si = nullptr) : elem(el), sig(si) {}
      T elem;
      Nodo * sig;
   };

   Nodo* prim;
   Nodo* ult;
   
public:
   
   // constructor: cola vacía
   queue() : prim(nullptr), ult(nullptr) {}
   
   // destructor
   ~queue() {
      libera();
   }
   
   // constructor por copia
   queue(queue<T> const& other) {
      copia(other);
   }
   
   // operador de asignación
   queue<T> & operator=(queue<T> const& other) {
      if (this != &other) {
         libera();
         copia(other);
      }
      return *this;
   }
   
   // añadir un elemento al final de la cola
   void push(T const& elem) {
        Nodo* nuevo = new Nodo(elem);
        if (ult != nullptr)
            ult->sig = nuevo;
        ult = nuevo;
        if (prim == nullptr)
            prim = nuevo;
        ++nelems;
   }
   
   // consultar el primero de la cola
   T const& front() const {
      if (empty())
         throw std::domain_error("la cola vacia no tiene primero");
     return prim->elem;

   }
   
   // eliminar el primero de la cola
   void pop() {
        if (empty())
             throw std::domain_error("la cola vacia no tiene primero");
         Nodo* aux = prim;
        prim = prim->sig;
        if (prim == nullptr)
            ult = nullptr; 
        delete aux;
        --nelems;
   }
   
   // consultar si la cola está vacía
   bool empty() const {
      return nelems == 0;
   }
   
   // consultar el tamaño de la cola
   int size() const {
      return nelems;
   }
   
protected:
   
   void libera() {
      while (prim != nullptr) {
         Nodo * a_borrar = prim;
         prim = prim->sig;
         delete a_borrar;
      }
      ult = nullptr;
   }
   
   // this está sin inicializar
   void copia(queue const& other) {
      if (other.empty()) {
         prim = ult = nullptr;
         nelems = 0;
      } else {
         Nodo * act = other.prim; // recorre la cola original
         Nodo * ant = new Nodo(act->elem); // último nodo copiado
         prim = ant;
         while (act->sig != nullptr) {
            act = act->sig;
            ant->sig = new Nodo(act->elem);
            ant = ant->sig;
         }
         ult = ant;
         nelems = other.nelems;
      }
   }
};



template <class T>
class deque {
protected:
   /*
    Nodo que almacena internamente el elemento (de tipo T),
    y dos punteros, uno al nodo anterior y otro al nodo siguiente.
    */
   struct Nodo {
      Nodo() : ant(nullptr), sig(nullptr) {}
      Nodo(T const& elem, Nodo * ant, Nodo * sig) : elem(elem), ant(ant), sig(sig) {}
      T elem;
      Nodo * ant;
      Nodo * sig;
   };
   
   // puntero al nodo fantasma
   Nodo * fantasma;
   
   // número de elementos
   int nelems;
   
public:
   
   // constructor: cola doble vacía
   deque() : fantasma(new Nodo()), nelems(0) {
      fantasma->sig = fantasma->ant = fantasma; // circular
   }
   
   // destructor
   ~deque() {
      libera();
   }
   
   // constructor por copia
   deque(deque<T> const& other) {
      copia(other);
   }
   
   // operador de asignación
   deque<T> & operator=(deque<T> const& that) {
      if (this != &that) {
         libera();
         copia(that);
      }
      return *this;
   }
   
   // añadir un elemento por el principio
   void push_front(T const& e) {
       inserta_elem(e,fantasma,fantasma->sig);
   }
   
   // añadir un elemento por el final
   void push_back(T const& e) {
       inserta_elem(e,fantasma->ant,fantasma);
   }
   
   // consultar el primer elemento de la dcola
   T const& front() const {
      if (empty())
         throw std::domain_error("la dcola vacia no tiene primero");
     return fantasma->sig->elem;
      
   }
   
   // consultar el último elemento de la dcola
   T const& back() const {
      if (empty())
         throw std::domain_error("la dcola vacia no tiene ultimo");
       return fantasma->ant->elem;
      
   }
   
   // eliminar el primer elemento
   void pop_front() {
      if (empty())
         throw std::domain_error("eliminando el primero de una dcola vacia");
      borra_elem(fantasma->sig);
   }
   
   // elminar el último elemento
   void pop_back() {
      if (empty())
         throw std::domain_error("eliminando el ultimo de una dcola vacia");
      borra_elem(fantasma->ant);
   }
   
   // consultar si la dcola está vacía
   bool empty() const {
      return nelems == 0;
   }
   
   // consultar el tamaño de la cola doble
   int size() const {
      return nelems;
   }
   
protected:
   
   
   // insertar un nuevo nodo entre anterior y siguiente
   Nodo * inserta_elem(T const& e, Nodo * anterior, Nodo * siguiente) {
       Nodo* nuevo = new Nodo(e,anterior, siguiente);
       anterior->sig = nuevo;
       siguiente->ant = nuevo;
       ++nelems;
       return nuevo;
   }
   
   // eliminar el nodo n
   void borra_elem(Nodo* n) {
       n->ant->sig = n->sig;
       n->sig->ant = n->ant
       delete n;
       --nelems;
   }
};




template <class T>
class list : public deque<T> {
protected:
   using Nodo = typename deque<T>::Nodo;

   const T& at(unsigned int i) const {
        if (i >= numElems) throw ...
        Nodo* aux = fantasma->sig;
        for (int k = 0; k < i; k++)
            aux = aux->sig;
        return aux->elem;
   }


   class iterator {
    protected:
        Nodo* act;
        Nodo* fan;

        iterator(Nodo* n){
            act = n;
        }

    public:
        iterator operator++(){
            if (act == fan) throw ...
            act = act->sig;
            return *this; 
        }

        T& operator*(){
         if (act == fan) throw ...
         return act->elem;    
       }

       bool operator==(iterator other){
        return act == other.act && fan == other.fan;
       }

   } // end class iterator

   iterator begin(){
    return iterator(fantasma->sig);
   }

   iterator end(){
    return iterator(fantasma);
   }

   void insert(iterator it,T const& e){
    ...
    inserta_elem(e,it.act->ant,it.act);
   }

   iterator erase(iterator it){
    ...
    borra_elem(it.act);
    return ...
   }

};



int main(){
    list<int> l;
    ...

    // Coste cuadrático!!
    for (int i = 0 ; i < l.size(); ++i)
        cout << l.at(i);

    for (list::const_iterator it = l.cbegin() ; it != l.cend(); ++it){
        cout << *it;
    }

    for (int e : l)
        cout << e;


    list::iterator it = l.begin();
    ++(++it);


    list::iterator it = l.begin();
    while (*it != 10)
        ++it;

    l.erase(it);

    l.insert(it,9); // Se inserta un 9 delante del nodo apuntado por it


    for (list::const_iterator it = l.cbegin() ; it != l.cend();){
        if ((*it) % 2 == 0) it = l.erase(it);
        else ++it;
    }


}