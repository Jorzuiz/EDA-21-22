template <class T>
class bintree {
protected:
   /*
    Nodo que almacena internamente el elemento (de tipo T),
    y punteros al hijo izquierdo y derecho, que pueden ser
    nullptr si el hijo es vacío (no existe).
    */
   using Link = TreeNode*;
   struct TreeNode {
      TreeNode(Link const& l, T const& e, Link const& r) : elem(e), left(l), right(r) {};
      T elem;
      Link left, right;
   };
   
   Link raiz;
   
   bintree(Link const& r) : raiz(r) {r->addRef();} 

public:
   // árbol vacío
   bintree() : raiz(nullptr) {}

   bintree(const& T e) : raiz(new TreeNode(e)) {raiz->addRef();}

   bintree(bintree l, const& T e, bintree r) ...
   
   ~bintree(){
      libera(raiz);
   }

   T& root(){
      if (...) throw ...
      return raiz->elem;
   } 

   bintree<T>& left(){
      if (...) throw
      return bintree((raiz->left));
   }

   bool operator==(bintree<T> const& other){
      return compara(this->raiz, other.raiz);
   }

   vector<T> preorder() const {
      vector<T> ac;
      preorder(raiz,ac);
      return ac;
   }

   vector<T> niveles() const {
      vector<T> res;
      stack<Link> pendientes;
      if (!empty()){
         pendientes.push(raiz);
         while (!pendientes.empty()){
            Link act = pendientes.front();
            pendientes.pop();
            res.push_back(act->elem);
            if (act->left != nullptr) pendientes.push(act->left);
            if (act->right != nullptr) pendientes.push(act->right);
        }
      }
      return res;
   }

protected:
   vector<T> preorderMalo(Link n) const{
      vector<T> res;
      if (n != nullptr){
         res.push_back(n->elem);
         vector<T> hi = preorder(n->left);
         vector<T> hd = preorder(n->right);
         concatena(res,hi);
         concatena(res,hd);
      }
      return res;
   }

   vector<T> preorder(Link n, vector<T>& ac) const{
      if (n != nullptr){
         ac.push_back(n->elem);
         preorder(n->left,ac);
         preorder(n->right,ac);
      }
   }


   void libera(Link r);
      if (r != nullptr){
         libera(r->left);
         libera(r->right);
         delete r;
      }
   }

   bool compara(Link r1, Link r2){
      if (r1 == r2) return true;
      if (r1 == nullptr) || (r2 == nullptr) return false;
      return r1->elem == r2->elem && compara(r1->left, r2->left) 
             && compara(r1->right, r2->right);
   }

   Link copia(Link r){
      if (r == nullptr) return nullptr;
      return new TreeNode(copia(r->left), r->elem, copia(r->right));
   }

}




int numHojas(bintree<T>& b){
   if (b.empty()) return 0;
   if (esHoja(b)) return 1;
   int hojasIz = numHojas(b.left());
   int hojasDr = numHojas(b.right());
   return hojasIz + hojasDr;
}



int main(){
   bintree<char> b('b'); 
   bintree<char> d('d');
   bintree<char> c(bintree<char>(), 'c', d);
   bintree<char> a(b,'a',c);
   bintree<char> l = a.left();
   //cout << l.root(); 
   //bintree<char> copia = a;
}

template <class T>
bintree<T> leerArbol(T vacio){
   T raiz;
   cin >> raiz;
   if (raiz == vacio) return bintree();
   bintree<T> hi = leerArbol(vacio);
   bintree<T> hd = leerArbol(vacio);
   return bintree(hi,raiz,hd);  
}


int hojas(bintree<int> const& a){
   if (a.empty()) return 0;
   else if (esHoja(a)) return 1; 
   else { 
      int hojasIz = hojas(a.left());
      int hojasDr = hojas(a.right());
      return hojasIz + hojasDr;   
   }
}

void hojasParam(bintree<int> const& a, int& numHojas){
   if (a.empty()) numHojas = 0;
   else if (esHoja(a)) numHojas = 1; 
   else {
      int hojasIz, hojasDr; 
      hojasParam(a.left(), hojasIz);
      hojasParam(a.right(),hojasDr);
      numHojas = hojasIz + hojasDr;   
   }
}


void hojasAcu(bintree<int> const& a, int& acu){
   if (a.empty()) return;
   else if (esHoja(a)) ++acu; 
   else { 
      hojasAcu(a.left(),acu);
      hojasAcu(a.right(),acu);
   }
}



int altura(bintree<int> const& a){
   if (a.empty()) return 0;
   else { 
      int alturaIz = altura(a.left());
      int alturaDr = altura(a.right());
      return return max(alturaDr,alturaIz) + 1;   
   }
}


void alturaAcu(bintree<int> const& a, int prof, int& altura){
   if (a.empty()) if (prof > altura) altura = prof;
   else { 
      alturaAcu(a.left(),prof+1,acu);
      alturaAcu(a.right(),prof+1,acu);
   }
}


bool esOrdenado(const bintree<int>& a, int& minimo, int& maximo) {
    if (a.empty()) {
        minimo = INT_MAX;
        maximo = INT_MIN;
        return true;
    }
    /* En lugar de devolver INT_MAX e INT_MIN se puede evitar generar llamadas
    a árboles vacíos. Para ello lo más seguro es plantear casos para árbol hoja, 
    árbol con solo hijo izqdo y árbol con solo hijo dcho. Es decir, faltarían estos:
    else if (esHoja()) ...
    else if (...) //solo tengo hijo izq
    else if (...) // solo tengo hijo derecho   
    */
    int minIz, minDr, maxIz, maxDr;
    bool ordenadoIz = esOrdenado(a.left(), minIz, maxIz);
    bool ordenadoDr = esOrdenado(a.right(), minDr, maxDr);
    minimo = min(minIz,a.root());
    maximo = max(maxDr,a.root());
    return ordenadoIz && ordenadoDr && a.root() > maxIz && a.root() < minDr;
}

bool esOrdenadoCasiFin(const bintree<int>& a, int inf, int sup){
    if (a.empty()) return true;
    return a.root() > inf && a.root() < sup &&
           esOrdenadoCasiFin(a.left(),inf,a.root()) && esOrdenadoCasiFin(a.right(), a.root(), sup);
}

void esOrdenadoFin(bintree<int> const& a, int inf, int sup, bool& esArbus){
    if (a.empty()) return ;
    if (a.root() <= inf || a.root() >= sup) esArbus = false;
    if (esArbus) esOrdenadoFin(a.left(), inf, a.root(), esArbus);
    if (esArbus) esOrdenadoFin(a.right(), a.root(),sup, esArbus);
}

// función que resuelve el problema
bool esOrdenado(const bintree<int>& a) {
    int min, max;
    return esOrdenado(a, min, max);
}



/* 

Árboles Binarios de Búsqueda
----------------------------
 
 - Definición: Árboles binarios ordenados tal que
   * raiz mayor que todos los nodos el hijo izquierdo,
   * raiz menor que todos los nodos del hijo derecho, y
   * los dos hijos también son binarios de búsqueda

- Ejemplo:

           20
         /    \
        12     31
       /  \   /  \
      7   17 26  43
              \
              28 

- Aplicación: Rep. interna de TADs Set y Map con búsqueda, 
inserción y eliminación O(logn) y tb recorrido ordenado.

- Implementación:
*/

template <class T, class Comparator = std::less<T>>
class set {

   using Link = TreeNode*;
   struct TreeNode {
      TreeNode(Link const& l, T const& e, Link const& r) : elem(e), left(l), right(r) {};
      T elem;
      Link left, right;
   };
   
   Link raiz;
   int nelems;
   
   // objeto función que compara elementos (orden total estricto)
   Comparator menor;
   
   
public:
   int count(const& T e){
      return pertenece(e,raiz);
   }

   void insert(const& T e){
      inserta(e,raiz);
   }

   void erase(const& T e){
      borra(e,raiz);
   }

protected:
   bool pertenece(const& T e, Link a){
      if (a == nullptr) return false;
      if (menor(e,a->elem)) return pertenece(e,a->iz);
      else if (menor(a->elem,e)) return pertenece(e,a->dr);
      else {// e == a->elem)
         return true;
      }
   }

   bool inserta(const& T e, Link& a){
      if (a == nullptr) {
         a = new TreeNode(e);
         ++nelems;
         return true;
      }
      if (menor(e,a->elem)) return inserta(e,a->iz);
      else if (menor(a->elem,e)) return inserta(e,a->dr);
      else // e == a->elem)
         return false;
   }

   bool borra(const& T e, Link& a){
      if (a == nullptr) return false;
      if (menor(e,a->elem)) return borra(e,a->iz);
      else if (menor(a->elem,e)) return borra(e,a->dr);
      else {// e == a->elem)
         if (a->iz == nullptr || a->dr == nullptr){
            Link aux = a;
            a = (a->iz == nullptr) ? a->dr : a->iz;
            delete aux;
            --nelems
         }
         else { // tengo los dos hijos
            subirMenorHD(a);
            --nelems;
         }
      } 

}




int main(){
   set<int> s;
   s.insert(20);
   s.insert(31);
   s.insert(12);
   s.insert(7);
   ...
   s.erase(17);
   set<int,...> s2;

}









