#include <bits/stdc++.h>

using namespace std;

class Graph {

    vector < vector <int> > adjList;
    vector <int> inDegree;
    int V, E;

public:

    Graph(const char *Filename) {

        ifstream fin(Filename);

        fin >> this->V >> this->E;

        this->adjList.resize(this->V);
        this->inDegree.reserve(this->V);

        for(int e = 0; e < this->E; ++e){

            int from, to;
            fin >> from >> to;

            --from; --to;

            this->adjList[from].push_back(to);
            ++this->inDegree[to];
        }
    }

    vector <int> topologicalSort() {

        vector <int> topoSort;
        topoSort.reserve(this->V);

        deque <int> Queue;
        for(int node = 0; node < V; ++node)
            if(this->inDegree[node] == 0)
                Queue.push_back(node);

        while(!Queue.empty()){

            int node = Queue.front();
            Queue.pop_front();

            topoSort.push_back(node);

            for(const int &adjNode : this->adjList[node]){

                --this->inDegree[adjNode];
                if(this->inDegree[adjNode] == 0)
                    Queue.push_back(adjNode);
            }
        }

        return topoSort;
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