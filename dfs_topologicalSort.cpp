#include <bits/stdc++.h>

using namespace std;

class Graph {

    vector < vector <int> > adjList;
    int V, E;
    vector <bool> seen;
    vector <int> topoSort;

public:

    Graph(const char *Filename) {

        ifstream fin(Filename);

        int nodes, edges;
        fin >> nodes >> edges;

        this->V = nodes;
        this->E = edges;

        this->adjList.resize(nodes);
        this->seen.resize(nodes);
        this->topoSort.reserve(nodes);

        for(; edges; --edges){

            int from, to;
            fin >> from >> to;

            --from; --to;

            this->adjList[from].push_back(to);
        }
    }

    void DFS(int node){

        this->seen[node] = true;

        for(const int &adjNode : this->adjList[node])
            if(!seen[adjNode])
                DFS(adjNode);

        this->topoSort.push_back(node);
    }

    vector <int> topologicalSort() {

        for(int node = 0; node < this->V; ++node)
            if(!this->seen[node])
                DFS(node);

        reverse(this->topoSort.begin(), this->topoSort.end());
        return this->topoSort;
    }
};

ofstream& operator << (ofstream &out, const vector <int> &ans) {
    for(const int &x : ans)
        out << x + 1 << ' ';
    out << '\n';

    return out;
}

int main(){

    Graph graph("sortaret.in");

    ofstream fout("sortaret.out");
    fout << graph.topologicalSort();
}