#include <bits/stdc++.h>

using namespace std;

struct Edge {

    int to, cost;
};

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

        vector <Edge> connEdge(V, {0, INT_MAX}); // minimal connection edge
        vector <bool> used(V);

        used[0] = true;
        for(const Edge &edge : this->adjList[0])
            connEdge[edge.to] = {0, edge.cost};

        vector <Edge> mst;
        mst.reserve(this->E);

        int mstCost = 0;
        for(int it = 1; it < V; ++it){

            // add edge to mst
            int minCost = INT_MAX;
            int addNode = -1;
            for(int node = 0; node < V; ++node) // find minimum
                if(!used[node] and connEdge[node].cost < minCost)
                    addNode = node, minCost = connEdge[node].cost;

            mstCost += minCost;
            mst.push_back({addNode, connEdge[addNode].to});
            used[addNode] = true;

            for(const Edge &edge : adjList[addNode])
                if(!used[edge.to] and edge.cost < connEdge[edge.to].cost)
                    connEdge[edge.to] = {addNode, edge.cost};
        }

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

    for(const Edge &edge : mst)
        fout << edge.to + 1 << ' ' << edge.cost + 1 << '\n'; // making abuse of the edge structure
}