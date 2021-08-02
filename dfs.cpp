#include <bits/stdc++.h>

using namespace std;

class Graph{

    int V, E;
    vector < vector <int> > adjList;
    vector <bool> seen;

public:

    Graph(const char *Filename) {

        ifstream fin(Filename);

        fin >> this->V >> this->E;

        this->adjList.resize(this->V);

        for(int e = 0; e < this-> E; ++e){

            int from, to;
            fin >> from >> to;

            --from; --to;

            this->adjList[from].push_back(to);
            this->adjList[to].push_back(from);
        }
    }

    void DFS(int node) {

        this->seen[node] = true;

        for(const int &adjNode : this->adjList[node])
            if(!seen[adjNode])
                DFS(adjNode);
    }

    int connectedComponents_count() {

        this->seen.resize(V);

        int ans = 0;
        for(int node = 0; node < V; ++node)
            if(!this->seen[node]){

                ++ans;
                DFS(node);
            }

        return ans;
    }
};

int main(){

    Graph graph("dfs.in");

    ofstream fout("dfs.out");
    fout << graph.connectedComponents_count() << '\n';
}