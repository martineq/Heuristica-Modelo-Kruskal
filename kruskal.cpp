#include <iostream>
#include <vector>

#define CANT_NODOS 8	// Dimensi�n de la matriz, cantidad de nodos.
#define ALTO_VALOR 999	// Un alto valor que representa a "infinito"

using namespace std;

// Esta funci�n es la encargada de construir la matriz
// adem�s nos imprime por pantalla la matriz de adyacencia.
void CargarMatrizDeAdyacencia(vector<vector<int>> &matriz){

	//1: Veinticinco de Mayo
	//2: Roque P�rez
	//3: Saladillo
	//4: Bol�var
	//5: General Alvear
	//6: Tapalqu�
	//7: Olavarr�a
	//8: Azul

	// Matriz de adyacencia con los pesos de cada arista
	 int mda[CANT_NODOS][CANT_NODOS]=  {{0,106,48,192,0,0,0,0},
										{106,0,58,0,0,0,0,0},					{48,58,0,156,59,87,0,0},
	{192,0,156,0,253,0,103,0},
	{0,0,59,253,0,53,0,0},
	{0,0,87,0,53,0,0,54},
	{0,0,0,103,0,0,0,52},
	{0,0,0,0,0,54,52,0} };

	// Lleno con los datos y muestro la matriz
	 cout<<"Matriz De Adyacencia: \n";
	for(int i = 0;i < CANT_NODOS; i++){         
		for(int j = 0;j < CANT_NODOS; j++){            
			matriz[i][j] = mda[i][j]; 
			cout<< matriz[i][j] <<"\t";
		}
		cout<<"\n";     
		matriz[i][i] = 0; 
	} 
	cout<<"\n";
} 

//Esta funci�n comienza buscando la arista 
int comienzo(int v,vector<int> &p){      
   while( p[v] != v )  v = p[v];  
   return v; 
}

//Esta funci�n solo nos une los nodos con un orden 
//l�gico en el vector soluci�n
void union_ij(int i,int j,vector<int> &p){      
	if(j > i)
		p[j] = i;
	else
		p[i] = j;
}

//Esta es la funci�n correspondiente al algoritmo de Kruskal
void kruskal(vector<vector<int>> &matriz){

	int sum = 0;			// Costo total
	int min = ALTO_VALOR;	// M�nimo principal
	vector<int> p;			// Vector soluci�n
	vector<vector<int>> t;	// Tabla donde se guardan las aristas elegidas
	int k = 0;				// Contador de aristas elegidas

	// Inicialo
	p.resize(CANT_NODOS);
	t.resize(CANT_NODOS);
	for (int i = 0; i < CANT_NODOS; ++i) t[i].resize(2);
	for (int i = 0; i < CANT_NODOS; i++) p[i] = i;           

	// Proceso hasta (CANT_NODOS-1) aristas. Supongo grafo inicial conexo con (CANT_NODOS) nodos
	while(k < CANT_NODOS-1){    

		min = ALTO_VALOR;	// Establecemos un m�mino principal lo suficientemente grande         
		int u, v;	// Posici�n del nodo

		// Me quedo con la arista positiva de peso m�nimo
		for( int i = 0; i < CANT_NODOS; i++){             
			for( int j = 0;j < CANT_NODOS; j++){ // TODO: antes estaba "CANT_NODOS-1"
				if( (matriz[i][j] < min) && (matriz[i][j] != 0) ){
					min = matriz[i][j];     
					u = i;
					v = j;
				 }
			}         
		}

		if(min != ALTO_VALOR){
			int i = comienzo(u, p);
			int j = comienzo(v, p);
			
			// Si no forma ciclo agrego la arista
			if (i != j){
				t[k][0] = u;
				t[k][1] = v; 
				k++;
				sum += min;
				union_ij(i,j,p);
			}
			matriz[u][v] = matriz[v][u] = 0;	// Marco y dejo en cero la arista que us�
		}

	}// Fin while        

	// Muestro los resultados
	if(k != CANT_NODOS-1){
		cout<<"No existe el �rbol\n";  // En realidad no pasar�a nunca, por la hip�tesis. 
	}else{
		cout<<"Rutas a usar:\n";         
		for(k = 0; k < CANT_NODOS-1 ; k++){             
			cout<< " ("<< (t[k][0])+1 << "-" << (t[k][1])+1 << ") "; // El +1 es porque los vectores empiezan en 0 y los nodos en 1
		}
		cout<<"\nCosto total = "<< sum <<" \n";
		cout<< "\nCiudades:\n";
		cout<< "1: Veinticinco de Mayo, 2: Roque P�rez, 3: Saladillo\n";
		cout<< "4: Bol�var, 5: General Alvear, 6: Tapalqu�\n";
		cout<< "7: Olavarr�a, 8: Azul\n";
	}

}

int main(int argc, char* argv[]) {

	// Creo la matriz, inicialo y cargo los datos.
	vector<vector<int>> matriz;
	matriz.resize(CANT_NODOS);
	for (int i = 0; i < CANT_NODOS; ++i) matriz[i].resize(CANT_NODOS);
	CargarMatrizDeAdyacencia(matriz);

	// Aplico la heur�stica
	kruskal(matriz);

	system("pause");
	return 0;
}
