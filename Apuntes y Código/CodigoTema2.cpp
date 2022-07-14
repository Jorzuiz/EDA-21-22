




int fact(int n){
	if (n == 0) return 1;
	return fact(n-1)*n;
}

// Versión devolviendo resultado en parámetro de salida
void fact(int n, int& res) {
	if (n == 0) res = 1;
	else {
		int aux;
		fact(n - 1, aux);
		res = aux*n;
	}
}


// Versión final con parámetro acumulador
int fact(int n, int& ac){
	if (n == 0) return ac;
	return fact(n-1,n*ac);
}


int sumaIt(vector<int> const&){
	int result = 0;
	for (int e : v) result += e;
	return result;
}

int sumaRec(vector<int> const& v){
	if (v.size() == 0) return 0;
	else {
		vector<int> resto(v.size()-1);
		for (...) resto[i] = v[i];
		int aux = sumaRec(resto);
		return aux + v[ini];
	}
}

int sumaDiv(vector<int> const& v, int ini, int fin){
	int n = fin-ini;
	if (n <= 1) return (n == 0 ? 0 : v[ini]);
	else {
		int mitad = (ini+fin)/2;
		int sumaIzq = sumaDiv(v,ini,mitad);
		int sumaDer = sumaDiv(v,mitad,fin);
		return sumaIzq + sumaDer;
	}
}

void sumaDivAc(vector<int> const& v, int ini, int fin, int& ac){
	int n = fin-ini;
	if (n == 0) true;
	else if (n == 1) ac += v[ini];
	else {
		int mitad = (ini+fin)/2;
		sumaDivAc(v,ini,mitad,ac);
		sumaDivAc(v,mitad,fin,ac);
	}
}


int suma(vector<int> const& v){
	int res = 0;
	sumaDivAc(v,0,v.size(),res);
	return res;
}


int fib(int n){
	if (n == 0) return 1;
	if (n == 1) return 1;
	return fib(n-1) + fib(n-2);
}

bool member(vector<int> const& v, int ini, int fin, int e){
	int n = fin-ini; 
	if (n == 0) return false;
	else {
		return (v[ini] == e) || member(v,ini+1,fin,e));
	}
}


bool memberDiv(vector<int> const& v, int ini, int fin, int e){
	int n = fin-ini; 
	if (n == 0) return false;
	if (n == 1) return v[ini] == e;
	else {
		int mitad = ...
		bool estaIzq = memberDiv(v,ini,mitad,e);
		bool estaDer = memberDiv(v,mitad,fin,e);
		return (estaIzq || estaDer);
	}
}


bool memberOrd(vector<int> const& v, int ini, int fin, int e){
	int n = fin-ini; 
	if (n == 0) return false;
	if (n == 1) return v[ini] == e;
	else {
		int mitad = ...
		if (e < v[mitad]) return memberOrd(v,ini,mitad,e);
		else return memberOrd(v,mitad,fin,e);
	}
}




void sort(vector<int>& v){
	sort(v,0,v.size());
}

void sort(vector<int>& v, int ini, int fin){
	int n = fin-ini;
	if (n > 1){
		int mitad = ...
		sort(v,ini,mitad);
		sort(v,mitad,fin);
		merge(...);
	}
}




bool parcialmenteOrdenado(vector<int>& const v, int ini, int fin, int& min, int& max) {
	int n = ...
		if (n == 1) {
			min = v[ini]; ...
			return true;
		}
	bool ordIz, ordDr;
	int mitad = ...
	int minIz, minDr, maxIz, maxDr;
	ordIz = parcialmenteOrdenado(v, ini, mitad, minIz, maxIz);
	ordDr = parcialmenteOrdenado(v, mitad, fin, minDr, MaxDr);
	min = min(minIz, minDr);
	max = max(maxIz, maxDr);
	return ordIz && ordDr && minIz <= minDr && maxDr >= maxIz;
}
