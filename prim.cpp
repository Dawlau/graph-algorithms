#include <bits/stdc++.h>

using namespace std;

struct Edge {

    int to, cost;

    bool operator <(const Edge &other) {
        return this->cost < other.cost;
    }

    friend bool operator <(const Edge &e1, const Edge &e2);
};

bool operator <(const Edge &e1, const Edge &e2) {

    if(e1.cost == e2.cost)
        return e1.to < e2.to;
    return e1.cost < e2.cost;
}

class Graph {

    vector < vector < Edge > > adjList;
    int V, E;

public:

    Graph(const char *Filename) {

        ifstream fin(Filename);

        fin >> this->V >> this->E;
        this->adjList.resize(this->V);

        for(int e = 0; e < this->E; ++e){

            int u, v, cost;
            fin >> u >> v >> cost;

            --u; --v;
            this->adjList[u].push_back({v, cost});
            this->adjList[v].push_back({u, cost});
        }
    }

    pair <int, vector <Edge> > Prim() {

        vector <Edge> connEdge(this->V, {0, INT_MAX}); // minimal connection edge
        vector <bool> used(this->V);

        set <Edge> RB;

        used[0] = true;
        for(const Edge &edge : this->adjList[0])
            connEdge[edge.to] = {0, edge.cost}, RB.insert(edge);

        int mstCost = 0;
        for(int it = 1; it < this->V; ++it){

            // add edge to mst
            Edge Find = *RB.begin();
            RB.erase(RB.begin());

            int minCost = Find.cost;
            int addNode = Find.to;

            mstCost += minCost;
            used[addNode] = true;

            for(const Edge &edge : this->adjList[addNode])
                if(!used[edge.to] and edge.cost < connEdge[edge.to].cost){

                    if(RB.count({edge.to, connEdge[edge.to].cost}))
                        RB.erase({edge.to, connEdge[edge.to].cost});

                    connEdge[edge.to] = {addNode, edge.cost};
                    RB.insert(edge);
                }
        }

        vector <Edge> mst;
        mst.reserve(this->V - 1);

        for(int node = 1; node < this->V; ++node)
            mst.push_back({node, connEdge[node].to});

        return {mstCost, mst};
    }
};

int main() {

    Graph graph("apm.in");

    pair <int, vector <Edge> > ans = graph.Prim();

    int cost = ans.first;
    vector <Edge> mst = ans.second;

    ofstream fout("apm.out");
    fout << cost << '\n' << mst.size() << '\n';

    for(Edge &edge : mst)
        fout << edge.to + 1 << ' ' << edge.cost + 1 << '\n'; // making abuse of the edge structure
}