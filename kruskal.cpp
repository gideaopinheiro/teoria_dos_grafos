#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

struct Aresta {
    int origem, dest, peso;
};

struct Comparar_Arestas {
    bool operator() (const Aresta &a, const Aresta &b) {
        return a.peso < b.peso;
    }
};

struct SubConj {
    int pai, rank;
};

class Grafo {
    public:
        int N, M;
        vector<vector<Aresta>> adj;

        Grafo(int n) {
            adj.resize(n);
            N = n;
        }

        void add_aresta(Aresta e) {
            if (e.origem > N || e.origem < 0 || e.dest > N || e.dest < 0)
                return;

            Aresta k {e.dest, e.origem, e.peso};

            adj[e.origem].push_back(e);
            adj[e.dest].push_back(k);
            M++;
        }

        void const exibir() {
            for (int i = 0; i < N; i++) {
                cout << i  << " --> ";

                for (Aresta e : adj[i])
                    cout << "(" << e.dest   << ", peso: "
                                << e.peso << ") ";
              cout << '\n';
            }
        }
};

int Encontrar(SubConj S[], int x) {
    if (S[x].pai != x)
        S[x].pai = Encontrar(S, S[x].pai);

    return S[x].pai;
}

void Uniao(SubConj S[], int x, int y) {

    if (S[x].rank > S[y].rank)
        S[y].pai = x;
    else if (S[x].rank < S[y].rank)
        S[x].pai = y;

    else {
        S[y].pai = x;
        S[x].rank++;
    }
}

Grafo kruskal(Grafo G) {
    SubConj subconjs[G.N];

    for (int i = 0; i < G.N ;i++) {
        subconjs[i].pai = i;
        subconjs[i].rank = 0;
    }

    vector<Aresta> arestas;
    vector<Aresta> S;

    for (auto adj : G.adj) { 
        for (Aresta e : adj) {
            if (e.origem < e.dest)     
                arestas.push_back(e);
        }
    }

    std::sort(arestas.begin(), arestas.end(), Comparar_Arestas{});

    for (Aresta e : arestas) {
        if (Encontrar(subconjs, e.origem) == Encontrar(subconjs, e.dest))
            continue;

        S.push_back(e); 
        Uniao(subconjs, Encontrar(subconjs, e.origem) ,Encontrar(subconjs, e.dest));
    }

    Grafo arvore (G.N);

    for (Aresta e : S)
        arvore.add_aresta(e);
    
    return arvore;
}

int main(void) {
    int n, m;

    cin >> n >> m;

    Grafo G (n);
    
    for (int i = 0; i < m; i++) {
        int x, y, p;

        cin >> x >> y >> p;

        G.add_aresta(Aresta {x, y, p});
    }

    Grafo arvore = kruskal(G);

    arvore.exibir();

    return 0;
}
