#include <iostream>
#include <climits>

using namespace std;

void inicializar(int tam, int **L, int **P) {
    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < tam; j++) {
            if (i == j) {
                L[i][j] = 0;
            } else {
                L[i][j] = 999; //INF
            }
            P[i][j] = 0;
        }
    }
}

void buscaCaminho(int **P, int i, int j){
    if (P[i-1][j-1] == 0) {
        cout << j << " -> ";
    } else {
        buscaCaminho(P, i, P[i-1][j-1]);
        cout << j << " -> ";
    }
}

void mostrarMatrizes(int tam, int **L, int **D, int **P) {
    int i = 0, j = 0;

    cout << "--- Matriz L: ---\n";
    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            cout.width(3);
            if (L[i][j] == INT_MAX) {
                cout << right << "INF"<< " "; 
            } else cout << right << L[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n\n--- Matriz D: ---\n";
    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            cout.width(3);
            if (D[i][j] == INT_MAX) {
                cout << right << "INF"<< " "; 
            } else cout << right << D[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n\n--- Matriz P: ---\n";
    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            cout.width(3);
            cout << right << P[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int i = 0, j = 0, k = 0, V = 0, aresta = 0, vertice = 0, valor = 0;
    bool continuar = true;

    cout << "Informe o numero de vertices: ";
    cin >> V;

	int **L = new int*[V];
    int **D = new int*[V];
    int **P = new int*[V];

	for (int i = 0; i < V; i++) {
        L[i] = new int[V];
        D[i] = new int[V];
	    P[i] = new int[V];
	}

    inicializar(V, L, P);

    cout << "Informe VERTICE | ARESTA | VALOR (EOF para encerrar):" << endl;
    while (scanf("%d" "%d" "%d", &vertice, &aresta, &valor) != EOF) {
        L[vertice-1][aresta-1] = valor;
    }

    for(i = 0; i < V; i++) { //cópia da matriz L para D
        for(j = 0; j < V; j++) {
            D[i][j] = L[i][j];
        }
    }

    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = k + 1;
                }
            }
        }
    }

    system("cls");

    //mostrarMatrizes(V, L, D, P);

    cout << "\nInforme VERTICE | VERTICE para buscar um caminho (0 | 0 para encerrar): \n";
    while (continuar == true) {
        cin >> i;
        cin >> j;

        if (i == 0 && j == 0) {
            continuar = false;
            cout << "Encerrando...";
        } else if (i > V || j > V) {
            cout << "Vertices invalidos!" << endl;
        } else if (i == j) {
            cout << "Vertices iguais!" << endl;
        } else if (P[i-1][j-1] == 0) {
            cout << "Caminho: " << i << " -> " << j << endl;
        } else {
            cout << "Caminho: " << i << " -> ";
            buscaCaminho(P, i, j);
        }
        cout << endl;
    }

    return 0;
}