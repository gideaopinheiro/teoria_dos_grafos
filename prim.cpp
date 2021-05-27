#include <vector>
#include <iostream>
#include <queue>
#include <limits>

using namespace std;

struct Adj {
    int peso, v;
};

struct Compare_Adj {
    bool operator() (const Adj &a, const Adj &b) {
        return a.peso > b.peso;
    }
};

class Grafo {
    public:
        vector<vector<Adj>> adj;

        Grafo(int n) {
            adj.resize(n);
        }

        void const exibir(int n) {
            for (int i = 0; i < n; i++) {
                cout << i << " --> ";

                for (Adj e : adj[i])
                    cout << "(" << e.v << ", peso: " << e.peso << ") ";
                cout << '\n';
            }
        }
};

Grafo prim(Grafo G, int n) {
    int pesos[n]; 
    int anteriores[n];
    int S[n];

    for (int i = 0; i < n; i++) {
        pesos[i] = INT32_MAX;
        anteriores[i] = -1;
        S[i] = 0;
    }

    anteriores[0] = 0;
    pesos[0] = 0;
    
    priority_queue < Adj, vector<Adj>, Compare_Adj > fila;

    for (int i = 0; i < n; i++) {
        Adj e {pesos[i], i};
        fila.push(e);
    }

    int cont = 0;
    while (cont < n) {
        Adj e;

        do {
            e = fila.top();
            fila.pop();
        } while (e.peso != pesos[e.v] || S[e.v] == 1);

        int v = e.v;

        S[v] = 1;
        cont++;

        for (Adj edge : G.adj[v]) {
            int u = edge.v;
            int peso = edge.peso;

            if (!S[u] && peso < pesos[u]) {
                pesos[u] = peso;
                anteriores[u] = v;

                fila.push(Adj{peso, u});
            }
        }
    }

    Grafo arvore (n);

    for (int v = 1; v < n; v++) {
        int pai = anteriores[v];

        arvore.adj[v].push_back(Adj{pesos[v], pai});
        arvore.adj[pai].push_back(Adj{pesos[v], v});
    }

    return arvore;
}

int main(void) {
    int n, m;

    cin >> n >> m;

    Grafo G (n);
    
    for (int i = 0; i < m; i++) {
        int x, y, p;
        
        cin >> x >> y >> p;

        G.adj[x].push_back(Adj {p, y});
        G.adj[y].push_back(Adj {p, x});
    }

    Grafo arvore = prim(G, n);

    arvore.exibir(n);

    return 0;
}