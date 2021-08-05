#include <bits/stdc++.h>
 
using namespace std;
 
struct Edge {
 
    int to;
    long long cost;
};
 
bool operator <(const Edge &e1, const Edge &e2) {

    if(e1.cost == e2.cost)
        return e1.to < e2.to;
    return e1.cost < e2.cost;
}
 
class Graph {
 
    vector < vector <Edge> > adjList;
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
 
    vector <long long> Dijkstra(int source) {
 
        vector <long long> dist(this->V, LLONG_MAX);
        dist[source] = 0;
 
        set <Edge> RB;
        RB.insert({source, dist[source]});

        while(!RB.empty()) {
 
            int node = RB.begin()->to;

            RB.erase(RB.begin());

            for(const Edge &edge : this->adjList[node]){
                if(dist[edge.to] > dist[node] + edge.cost){
 
                    if(RB.count({edge.to, dist[edge.to]})){
                        RB.erase({edge.to, dist[edge.to]});
                    }

                    dist[edge.to] = dist[node] + edge.cost;
                    RB.insert({edge.to, dist[edge.to]});

                }
            }
        }
 
        return dist;
    }
};
 
int main(){
 
    Graph graph("dijkstra.in");
    vector <long long> ans = graph.Dijkstra(0);
 
    ofstream fout("dijkstra.out");
    for(int node = 1; node < (int)ans.size(); ++node)
        if(ans[node] == LLONG_MAX)
            fout << 0 << ' ';
        else fout << ans[node] << ' ';
}
