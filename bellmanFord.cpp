#include <iostream>
#include <vector>
using namespace std;

#define INF 9999

typedef struct aresta {
  int origem;
  int destino;
  int peso;
} aresta;


void exibirVetor(int vet[], int len) {
  cout << "{";
  int i;
  for (i = 0; i < len - 1; i++)
    cout << vet[i] << ", ";
  cout << vet[i] << "}" << endl;
}


bool bellmanFord(vector<vector<int>> G, int ordem, int s, int *custo) {
  aresta* A = NULL;
  A = new aresta[ordem * ordem];

  int nArestas = 0;
  for (int i = 0; i < ordem; i++) {
    for (int j = 0; j < ordem; j++) {
      if (G[i][j]) {
        A[nArestas].origem = i;
        A[nArestas].destino = j;
        A[nArestas].peso = G[i][j];
        nArestas++;
      }
    }
  }

  for (int i = 0; i < ordem; i++) {
    custo[i] = INF;
  }

  custo[s] = 0;

  bool troca;

  for(int i = 0; i < ordem; i++) {
    troca = false;
    for (int j = 0; j < nArestas; j++) {
      if (custo[A[j].destino] > custo[A[j].origem] + A[j].peso) {
        custo[A[j].destino] = custo[A[j].origem] + A[j].peso;
        troca = true;
      }
    }
    if (!troca) break;
  }

  for (int i = 0; i < nArestas; i++) {
    if (custo[A[i].destino] > custo[A[i].origem] + A[i].peso) {
      return false;
    }
    return true;
  }
}

int main() {
  int n;
  cin >> n;

  int custo[n];
  bool grafo;


  auto G = vector<vector<int>>(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      G[i][j] = 0;
    }
  }
  
  for (int i = 0; i < n; i++) {
    int x, y, p;
    cin >> x >> y >> p;

    G[x][y] = p;
    G[y][x] = p;
  }

  
  grafo = bellmanFord(G, n, 0, custo);

  cout << "Vetor Custo do grafo: ";
  exibirVetor(custo, n);

  if (!grafo)
      cout << "Existe ciclo negativo no grafo" << endl;
  else
      cout << "Nao existe ciclo negativo no grafo" << endl;

  cout << "\n";
  return 0;
}
