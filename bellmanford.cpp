#include <bits/stdc++.h>

using namespace std;

struct Edge {

    int to, cost;
};

class Graph {

    vector < vector <Edge> > adjList;
    const int Inf = INT_MAX;
    int V, E;

public:

    Graph(const char *Filename) {

        ifstream fin(Filename);
        fin >> this->V >> this->E;

        this->adjList.resize(this->V);

        for(int e = 0; e < this->E; ++e){

            int from, to, cost;
            fin >> from >> to >> cost;

            --from; --to;
            adjList[from].push_back({to, cost});
        }
    }

    vector <int> bellmanford(int source) {

        vector <int> dist(this->V, Inf);
        deque <int> Queue;

        Queue.push_back(source);
        dist[source] = 0;

         vector <int> seen;
         seen.resize(this->V);

        while(!Queue.empty()) {

            int node = Queue.front();
            Queue.pop_front();

            ++seen[node];
            if(seen[node] == V){

                fill(dist.begin(), dist.end(), Inf);
                return dist;
            }

            for(const Edge &edge : this->adjList[node]) {

                int adjNode = edge.to;
                int cost = edge.cost;

                if(dist[adjNode] > dist[node] + cost){

                    dist[adjNode] = dist[node] + cost;
                    Queue.push_back(adjNode);
                }
            }
        }

        return dist;
    }
};

int main(){

    Graph graph("bellmanford.in");
    vector <int> dist = graph.bellmanford(0);

    ofstream fout("bellmanford.out");

    int cntInf = 0;
    for(const int &x : dist)
        if(x == INT_MAX)
            ++cntInf;

    if(cntInf == (int)dist.size()) {
        fout << "Ciclu negativ!";
        return 0;
    }

    for(int node = 1; node < (int)dist.size(); ++node)
        fout << dist[node] << ' ';
}