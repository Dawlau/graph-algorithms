#include <bits/stdc++.h>

using namespace std;

class Union_Find {

    vector <int> dad;
    vector <int> rank;

public:

    Union_Find(const int &size) {

        this->dad.resize(size);
        this->rank.resize(size);

        for(int node = 0; node < size; ++node){
            dad[node] = -1;
            rank[node] = 1;
        }
    }

    int Find(int node) {

        int root;
        for(root = node; this->dad[root] != -1; root = this->dad[root]);

        while(node != root) {

            int auxNode = node;
            node = this->dad[node];
            this->dad[auxNode] = root;
        }

        return root;
    }

    void Union(int a, int b) {

        if(this->rank[a] > this->rank[b])
            this->dad[b] = a;
        else this->dad[a] = b;

        if(this->rank[a] == this->rank[b])
            ++this->rank[b];
    }
};

struct Edge {

    int u, v, cost;
};

class Graph {

    vector <Edge> edges;
    int V, E;

public:

    Graph(const char *Filename) {

        ifstream fin(Filename);

        fin >> this->V >> this->E;
        this->edges.reserve(this->E);

        for(int e = 0; e < this->E; ++e){

            int u, v, cost;
            fin >> u >> v >> cost;

            --u; --v;
            this->edges.push_back({u, v, cost});
        }
    }

    pair <int, vector <Edge> > Kruskal() {

        sort(this->edges.begin(), this->edges.end(), [&](const Edge &e1, const Edge &e2){
           return e1.cost < e2.cost;
        });

        Union_Find unionFind(this->V);
        vector <Edge> mst;
        mst.reserve(this->V - 1);

        int cost = 0;
        for(const Edge &edge : this->edges) {

            int u = edge.u;
            int v = edge.v;
            int c = edge.cost;

            int root1 = unionFind.Find(u);
            int root2 = unionFind.Find(v);


            if(root1 != root2) {

                cost += c;
                mst.push_back({u, v, c});
                unionFind.Union(root1, root2);
            }
        }

        return {cost, mst};
    }
};

int main() {

    Graph graph("apm.in");

    pair <int, vector <Edge> > ans = graph.Kruskal();

    int cost = ans.first;
    vector <Edge> mst = ans.second;

    ofstream fout("apm.out");
    fout << cost << '\n' << mst.size() << '\n';

    for(const Edge &edge : mst)
        fout << edge.u + 1 << ' ' << edge.v + 1 << '\n';
}