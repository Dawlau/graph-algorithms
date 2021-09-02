#include <bits/stdc++.h>

using namespace std;

class Graph {

    vector < vector <int> > adjList;
    vector < vector <int> > adjListT;
    int V, E;

    vector <bool> seen;
    vector <int> Stack;

    int sccCount;

    vector < vector <int> > scc;

public:

    Graph(const char *Filename) {

        ifstream fin(Filename);

        fin >> this->V >> this->E;

        this->seen.resize(this->V, false);
        this->adjList.resize(this->V);
        this->adjListT.resize(this->V);
        this->Stack.reserve(this->V);
        this->scc.resize(this->V);

        for(int e = 0; e < this->E; ++e){

            int from, to;
            fin >> from >> to;

            --from; --to;
            this->adjList[from].push_back(to);
            this->adjListT[to].push_back(from);
        }
    }

    void DFS1(int node) {

        seen[node] = true;

        for(const int &adjNode : this->adjList[node])
            if(!seen[adjNode])
                DFS1(adjNode);

        Stack.push_back(node);
    }

    void topoSort() {
        for(int node = 0; node < this->V; ++node)
            if(!seen[node])
                DFS1(node);

        reverse(this->Stack.begin(), this->Stack.end());
    }

    void DFS2(int node) {

        seen[node] = false;
        this->scc[this->sccCount].push_back(node);

        for(const int &adjNode : this->adjListT[node])
            if(seen[adjNode])
                DFS2(adjNode);
    }

    pair < int, vector < vector <int> > > kosaraju() {

        topoSort();

        for(int idx = 0; idx < this->V; ++idx)
            if(seen[this->Stack[idx]]){

                DFS2(this->Stack[idx]);
                ++this->sccCount;
            }

        return {this->sccCount, this->scc};
    }
};

int main(){

    Graph graph("date.in");

    pair <int, vector < vector <int> > > ans = graph.kosaraju();

    int sccCount = ans.first;
    vector < vector <int> > scc = ans.second;

    ofstream fout("date.out");

    fout << sccCount << '\n';
    for(int idx = 0; idx < sccCount; ++idx){
        for(const int &node : scc[idx])
            fout << node + 1 << ' ';
        fout << '\n';
    }
}