template <class Clave, class Valor, class Comparator = std::less<T>>
class map {

   using clave_valor = pair<Clave,Valor>;
   using Link = TreeNode*;
   struct TreeNode {
      TreeNode(Link const& l, T const& e, Link const& r) : elem(e), left(l), right(r) {};
      clave_valor cv;
      Link left, right;
   };
   
   Link raiz;
   int nelems;
   
   // objeto función que compara elementos (orden total estricto)
   Comparator menor;

public:
   int count(const& Clave e){
      return busca(e,raiz);
   }

   Valor 

   void insert(const& clave_valor cv){
      inserta(cv,raiz);
   }

   void erase(const& T e){
      borra(e,raiz);
   }

   protected:
   bool busca(const& Clave c, Link a){
      if (a == nullptr) return false;
      if (menor(c,a->cv.first)) return busca(c,a->iz);
      else if (menor(a->cv.first,c)) return busca(c,a->dr);
      else {// e == a->elem)
         return true;
      }
   }

   bool inserta(const& clave_valor cv, Link& a){
      if (a == nullptr) {
         a = new TreeNode(cv);
         ++nelems;
         return true;
      }
      if (menor(cv.clave,a->cv.first)) return inserta(e,a->iz);
      else if (menor(a->cv.first,cv.clave)) return inserta(e,a->dr);
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

   void subirMenorHD(Link& a){
      Link b = a->dr;
      Link padre = nullptr;
      while (b->iz != nullptr){
         padre = b;
         b = b->iz;
      }

      if (padre != nullptr){
         padre->iz = b->dr;
         b->dr = a->dr;
      }
      b->iz = a->iz;
      delete a;
      a = b;
   }

}






template <class Clave, class Valor,
          class Hash = std::hash<Clave>,
          class Pred = std::equal_to<Clave>>
class unordered_map {
public:
   // parejas <clave, valor>
   using clave_valor = std::pair<const Clave, Valor>;

protected:
   using umap_t = unordered_map<Clave, Valor, Hash, Pred>;
   
   /*
    Clase nodo que almacena internamente la pareja <clave, valor>
    y un puntero al siguiente.
    */
   struct ListNode;
   using Link = ListNode *;
   struct ListNode {
      clave_valor cv;
      Link sig;
      ListNode(clave_valor const& e, Link s = nullptr) : cv(e), sig(s) {}
   };
   
   // vector de listas (el tamaño se ajustará a la carga)
   std::vector<Link> array;
   
   static const int TAM_INICIAL = 17; // tamaño inicial de la tabla
   static const int MAX_CARGA = 75;   // máxima ocupación permitida 75 %
   
   // número de parejas <clave, valor>
   int nelems;
   
   // objeto función para hacer el hash de las claves
   Hash hash;
   
   // objeto función para comparar claves
   Pred pred;
   
public:
   
   // constructor
   unordered_map(int n = TAM_INICIAL, Hash h = Hash(), Pred p = Pred()) :
       array(n, nullptr), nelems(0), hash(h), pred(p) {}

   int count(const& Clave c){
      int i = hash(c)%array.size();
      Link ant, pos = array[i];
      return localizar(c,ant,pos);
   }

   void insert(const& Clave c){

   }

   bool erase(const& Clave c){
      int i = hash(c)%array.size();
      Link ant, pos = array[i];
      if (localizar(c,ant,pos)){
         if (ant == nullptr)
            array[i] = pos->sig;
         else
            ant->sig = pos->sig;
         delete pos;
         --nelems;
         return true;
      } else 
         return false;

   }

   Valor const& at(Clave const& c) const {

   }
   
   Valor & operator[](Clave const& c) {
   
   }

protected:

   bool localizar(Clave const& c, Link & ant, Link & pos) const {
      ant = nullptr;
      while (pos != nullptr) {
         if (pred(c, pos->cv.first))
            return true;
         else {
            ant = pos; pos = pos->sig;
         }
      }
      return false;
   }

}





void calcularApariciones(){
   map<string,int> apariciones;
   string palabra;
   cin >> palabra:
   while (!cin.fail()){
      
      /* Versión con count + [] (búsquedas redundantes) 
      if (!apariciones.count(palabra)){
         //apariciones.insert({palabra,1});
         apariciones[palabra] = 1;      
      
      } else {
         //int n = apariciones.at(palabra);
         //apariciones[palabra] = n+1;
         
         //int& n = apariciones[palabra];
         //n++;

         apariciones[palabra]++;
      }
      */

      /* Versión con solo una búsqueda 
      (aprovecha que el entero por defecto que se inserta es 0)
      apariciones[palabra]++;
      */

      /* Versión con solo una búsqueda aprovechando resultado del insert
      pair<iterator,bool> res = apariciones.insert({palabra,1});
      if (!res.second) res.first->second++; 
      */

      // Versión con find (una búsqueda redundante en caso de palabra nueva)
      auto itPalabra = apariciones.find(palabra);
      if (itPalabra == apariciones.end())
         apariciones[palabra] = 1;
      else 
         itPalabra->second++;
      
      cin >> palabra;
   }

   // Recorrido del map para imprimir
   for (auto it = apariciones.begin(); it != apariciones.end(); ++it){
      cout << it->first << " " << it->second << endl;
   }

   for (auto par : apariciones) 
      cout << par.first << " " << par.second << endl;

   for (auto [word,reps] : apariciones) 
      cout << word << " " << reps << endl;

}


int main(){

   map<string, Alumno> alumnos;

   map<string, Texture*> textures;

   textures.at("Ball");

}
