#include <vector>
#include <iostream>
#include <cstdint>
#include <limits>
#include <queue>
using namespace std;

struct Adj {
    int peso, v;
};

struct Comparar_Adj {
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

        void const exibirGrafo(int n) {
            for (int i = 0; i < n; i++) {
                cout << i << " --> ";

                for (Adj e : adj[i])
                    cout << "(" << e.v << ", peso: " << e.peso << ") ";
                cout << '\n';
            }
        }
};

Grafo dijkstra(Grafo G, int n, int v) {
    int custo[n];    
    int anterior[n];    
    int S[n];       

    for (int i = 0; i < n; i++) {
        custo[i] = INT32_MAX;
        anterior[i] = -1;
        S[i] = 0;
    }

    custo[v] = 0; 

    
    priority_queue <Adj, vector<Adj>, Comparar_Adj> fila;

    
    for (int i = 0; i < n; i++) {
        Adj e {custo[i], i};
        fila.push(e);
    }

    int count = 0;
    while (count < n) {
        Adj e;

        do {
            e = fila.top();
            fila.pop();
        } while (e.peso != custo[e.v] || S[e.v]);

        S[e.v] = 1;
        count++;

        for (Adj a : G.adj[e.v]) {
            if (a.peso + custo[e.v] < custo[a.v]) {
                custo[a.v] = a.peso + custo[e.v];
                anterior[a.v] = e.v;    

                fila.push(Adj {custo[a.v], a.v});
            }
        }
    }

    Grafo Dtree (n);

    for (int u = 1; u < n; u++) {
        int pai = anterior[u];
        int peso = custo[u] - custo[pai];

        Dtree.adj[u].push_back(Adj {peso, pai});
        Dtree.adj[pai].push_back(Adj {peso, u});
    }

    return Dtree;
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

    Grafo Dtree = dijkstra(G, n, 0);

    Dtree.exibirGrafo(n);

    return 0;
}