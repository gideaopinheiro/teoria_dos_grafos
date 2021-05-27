#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::vector;

struct Aresta {
    int origem, destino, peso;
};

class Grafo {
    public:
        int N, M;
        vector<vector<Aresta>> adj_in;
        vector<vector<Aresta>> adj_out;

        Grafo(int n) {
            adj_in.resize(n);
            adj_out.resize(n);
            N = n;
            M = 0;
        }

        void add_edge(Aresta e) {
            if (e.origem > N || e.origem < 0 || e.destino > N || e.destino < 0)
                return;

            adj_out[e.origem].push_back(e);
            adj_in[e.destino].push_back(e);

            M++;    
        }

        void const exibirGrafo() {
            for (int i = 0; i < N; i++) {
                cout << i  << " --> ";

                for (Aresta e : adj_out[i])
                    cout << "(" << e.destino << ", peso: " << e.peso << ") ";
              cout << '\n';
            }
        }
};

vector<int> topological_sort(Grafo G, vector<int> &ordenado) {
    int S[G.N];
    int n_adj_in[G.N];

    for (int i = 0; i < G.N; i++) {
        S[i] = 0;
        n_adj_in[i] = G.adj_in[i].size();
    }

    while (ordenado.size() < G.N) {

        for (int v = 0; v < G.N; v++) {
            if (n_adj_in[v] == 0 && !S[v]) {
                S[v] = 1;
                ordenado.push_back(v);

                for (Aresta e : G.adj_out[v])
                    n_adj_in[e.destino]--;
                
                break;
            }
        }
    }
    return ordenado;
}

int main(void) {
    int n, m;

    cin >> n >> m;

    Grafo G (n);
    
    for (int i = 0; i < m; i++) {
        int x, y, p;

        cin >> x >> y >> p;

        G.add_edge(Aresta {x, y, p});
    }
    vector<int> ordenado;

    topological_sort(G, ordenado);

    for (int i : ordenado)
        cout << i << ' ';
    cout << '\n';

    return 0;
}