


/* Tema 3 - Vuelta atrás

1. Un primer ejemplo: Todas las palabras posibles

2. Esquema general y variante con marcas

3. Ejemplo: Coloreado de mapa

4. Ejemplo: Las n-reinas

5. Variante esquema para obtener solo una solución (la primera)

6. Ejemplo: Laberinto

7. Versión Laberinto con Optimización. 

8. Variante esquema para obtener mejor solución

9. Ejemplo: Problema del viajante. Poda por estimación

10. Ejemplo: Problema de la mochila

*/


// 1. Un primer ejemplo: Todas las palabras posibles

void palabrasRec(vector<char>& soluc, int n, int m, int k, vector<bool>& usadas) {
	for (char c = 'a'; c < 'a' + m; ++c) {
		soluc[k] = c;
		if (!usadas[c-'a']) {
			if (k == n - 1)
				cout << soluc;
			else {
				usadas[c - 'a'] = true;
				palabrasRec(soluc, n, m, k + 1);
				usadas[c - 'a'] = false;
			}
		}
	}
}

// Función para la primera versión aún sin el marcador (vector usadas)
bool usada(...) {
	int i = 0;
	bool esta = false;
	while (!esta && i < k)
		...
}


void palabras(int n, int m) {
	vector<char> soluc(n);
	int k = 0;
	palabrasRec(soluc, n, m, k);
}


// 2. Esquema general, ya con marcas

void backtracking(vector<T>& sol, int n, int k, ...) {
	for (auto c : candidatos(k)) {
		sol[k] = c;
		if (esValida(sol, k, n, ...)) {
			if (esSolucion(sol, k, n))
				tratarSolucion(sol);
			else {
				marcar(...);
				backtracking(sol, n, k + 1, ...)
				desmarcar(...);
			}
		}
	}
}



// 3. Ejemplo: Coloreado de mapa

using Mapa = vector<vector<bool>>;

void coloreado(vector<int>& soluc, int n, int m, int k, const Mapa& mapa) {
	for (int color = 0; color < m; ++color) {
		soluc[k] = color;
		if (esValida(...)) {
			if (k == n - 1)
				cout << soluc;
			else {	
				coloreado(soluc, n, m, k + 1);
			}
		}
	}
}

bool esValida(... mapa, sol, int k) {
	bool valida = true;
	int i = 0;
	while (valida && i < k) {
		if (mapa[i][k] && sol[i] == sol[k]) valida = false;
		++i;
	}
	return valida;
}

int mainColoreado(){
	cin >> n >> m;
	Mapa mapa(n, vector<bool>(n, false));
	mapa[0][1] = true; // Lo pongo para ilustrar el hecho de que aquí se daría valores al grafo
	...
	vector<int> soluc(n);
	coloreado(soluc, n, m, 0, mapa);
}


// 4. Ejemplo: Las n-reinas
// 5. Variante esquema para obtener solo una solución (la primera)

void nreinas(vector<int>& soluc, int n, int k, bool& fin) {
	for (int i = 0; i < n && !fin; ++i) {
		soluc[k] = i;
		if (esValida(...)) {
			if (k == n - 1) {
				cout << soluc;
				fin = true;
			}
			else {
				marcar(...)
				nreinas(soluc, n, k + 1);
				desmarcar(...)
			}
		}
	}
}



// 6. Ejemplo: Laberinto

void laberinto(vector<Coord>& soluc, int n, int k, const Mapa& mapa, bool& fin, Mapa& visitadas) {
	for (int dir = 0; dir < 4 && !fin; ++dir) {
		soluc[k] = sigDir(dir,soluc[k-1]); // ver libro apuntes
		if (esValida(mapa,soluc[k],n,visitadas)) {
			if (soluc[k].fila == n - 1 && ...) {
				cout << soluc;
				fin = true;
			}
			else {
				visitadas[soluc[k].fila][soluc[k].col] = true;
				laberinto(soluc, n, k + 1,...);
				// No necesario descarcar en el caso de buscar 1ª solución
				//visitadas[soluc[k].fila][soluc[k].col] = false;
			}
		}
	}
}

int mainLaberinto() {
	cin >> n;
	Mapa mapa(n, vector<bool>(n, false));
	mapa[0][1] = true;
	...
	Mapa visitadas(n, vector<bool>(n, false));
	vector<Coord> soluc(2*n);
	soluc[0] = { 0,0 };
	laberinto(soluc, n, 1, mapa,...);
}

// Versión ya con optimización (se busca camino más corto)

void laberintoOpt(soluc, int n, int k, const Mapa& mapa, Mapa& visitadas,
	              int longitud, int& mejorLong) {
	for (int dir = 0; dir < 4; ++dir) {
		soluc[k] = sigDir(dir, soluc[k - 1]);
		if (esValida(mapa, soluc[k], n, visitadas)) {
			longitud++;
			if (soluc[k].fila == n - 1 && ...) {
				cout << soluc;
				if (longitud < mejorLong) mejorLong = longitud;
			}
			else {
				if (longitud + estimacionOptimista(...) < mejorLong) {
					visitadas[soluc[k].fila][soluc[k].col] = true;
					laberintoOpt(soluc, n, k + 1, ...);
					visitadas[soluc[k].fila][soluc[k].col] = false;
				}
			}
			longitud--;
		}
	}
}

int mainLaberintoOpt() {
	cin >> n;
	Mapa mapa(n, vector<bool>(n, false));
	mapa[0][1] = true;
	...
		Mapa visitadas(n, vector<bool>(n, false));
	vector<Coord> soluc(n*n); // Me equivoqué en clase y puse 2*n
	int mejorLong = n*n;
	soluc[0] = { 0,0 };
	laberintoOpt(soluc, n, 1, mapa, ...);
}



// 8. Variante esquema para obtener mejor solución

void backtrackingOpt(vector<T>& sol, int n, int k, ..., int coste, int mejorCoste) {
	for (auto c : candidatos(k)) {
		sol[k] = c;
		if (esValida(sol, k, n, ...)) {
			if (esSolucion(sol, k, n))
				if (coste < mejorCoste) mejorLong = longitud;
				tratarSolucion(sol);
			else {
				marcar(...);
				if (coste + estimacionOptimista(...) < mejorCoste) {
					backtrackingOpt(sol, n, k + 1, ...)
				}
				desmarcar(...);
			}
		}
	}
}


// 9. Ejemplo: Problema del viajante. Poda por estimación

using Mapa = vector<vector<int>>;

void viajante(soluc, int n, int k, const Mapa& mapa, vector<bool>& visitadas,
	int longitud, int& mejorLong, int longMIn) {
	for (int ciudad = 1; ciudad < n; ++ciudad) {
		soluc[k] = ciudad;
		if (esValida(mapa, soluc[k], n, visitadas)) {
			longitud += mapa[sol[k - 1]][ciudad];
			visitadas[ciudad] = true;
			if (k == n - 1) {
				if (mapa[sol[n-1]][0] > 0 && longitud+mapa[sol[n-1]][0] < mejorLong)
					mejorLong = longitud + mapa[sol[n-1]][0];
			}
			else {
				int estimacionOptimista = (n - k + 1) * longMin;
				if (longitud + estimacionOptimista < mejorLong) {
					viajante(soluc, n, k + 1, ...);
				}
			}
			visitadas[ciudad] = false;
			longitud -= mapa[sol[k - 1]][ciudad];
		}
	}
}

int main() {

	int longMin;
	...
	viajante(..., longMin);

}


//10. Ejemplo: Problema de la mochila

void mochila(vector<bool>& soluc, int n, int k, ...,
	         int valor, int& mejorValor, int peso) {

	// Hijo izquierdo: Se toma el elemento k-ésimo
	soluc[k] = true;
	peso += pesos[k];
	valor += valores[k];
	if (peso <= max) {
		if (k == n - 1) {
			if (valor > mejorValor) {
				mejorValor = valor;
			}
		}
		else
			if (...) mochila(sol, n, k + 1, ...);
	}
	peso -= pesos[k];
	valor -= valores[k];
	
	// Hijo derecho: No se toma el elemento k-ésimo 
	soluc[k] = false;
	//if (peso <= max) {
	if (k == n - 1) {
		if (valor > mejorValor) {
			mejorValor = valor;
		}
	}
	else
		if (...) mochila(sol, n, k + 1, ...);
}