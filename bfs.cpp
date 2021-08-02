#include <bits/stdc++.h>

using namespace std;

class Graph{

    int V, E;
    int source;
    vector < vector <int> > adjList;

public:

    Graph(const char *Filename) {

        ifstream fin(Filename);

        fin >> this->V >> this->E >> this->source;
        --this->source;

        this->adjList.resize(this->V, vector <int>() );

        for(int e = 0; e < this-> E; ++e){

            int from, to;
            fin >> from >> to;

            --from; --to;

            this->adjList[from].push_back(to);
        }
    }

    // get distances
    vector <int> BFS() {

        vector <bool> seen;
        vector <int> dist;

        dist.resize(this->V);
        seen.resize(this->V);

        dist[this->source] = 0;
        seen[this->source] = true;

        deque <int> Queue;
        Queue.push_back(this->source);

        while(!Queue.empty()){

            int node = Queue.front();
            Queue.pop_front();

            for(const int &adjNode : this->adjList[node])
                if(!seen[adjNode]){

                    seen[adjNode] = true;
                    dist[adjNode] = dist[node] + 1;
                    Queue.push_back(adjNode);
                }
        }

        // if I can't reach a node make the distance to it -1
        for(int node = 0; node < V; ++node)
            if(!seen[node])
                dist[node] = -1;

        return dist;
    }
};

ofstream& operator <<(ofstream &out, const vector <int> &ans){

    for(int i = 0; i < (int)ans.size(); ++i)
        out << ans[i] << ' ';
    out << '\n';
    return out;
}

int main(){

    Graph graph("bfs.in");

    ofstream fout("bfs.out");
    fout << graph.BFS();
}