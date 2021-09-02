#include <bits/stdc++.h>

using namespace std;

class Graph{

    int V, E;

    vector < vector <int> > adjList;

	const int Inf = INT_MAX;

	vector <bool> seen;

	vector < vector <int> > capacity, flow;
	vector <int> bfsTree;

	int source, sink;

public:

    Graph(const char *Filename) {

        ifstream fin(Filename);

        fin >> this->V >> this->E;

        this->adjList.resize(this->V);
        this->seen.resize(this->V);
        this->bfsTree.resize(this->V);

		capacity.resize(V, vector <int>(V));
		flow.resize(V, vector <int>(V));

		source = 0;
		sink = V - 1;

        for(int e = 0; e < this-> E; ++e){

            int from, to, c;
            fin >> from >> to >> c;

            --from; --to;

            this->adjList[from].push_back(to);
            this->adjList[to].push_back(from);
			capacity[from][to] = c;
        }
    }


	bool BFS(int source, int sink){

		deque <int> Queue;
		fill(seen.begin(), seen.end(), false);

		Queue.push_back(source);
		seen[source] = true;


		while(!Queue.empty()){

			int node = Queue.front();
			Queue.pop_front();

			if(node == sink)
				Queue.clear();
			else{
				for(const int &adjNode : adjList[node])
					if(!seen[adjNode] and capacity[node][adjNode] != flow[node][adjNode]){

						seen[adjNode] = true;
						Queue.push_back(adjNode);
						bfsTree[adjNode] = node;
					}
			}
		}

		return seen[sink];
	}

	int getMinimumCapacity(){

		int node, minimumCapacity = Inf;
		for(node = sink; node != source; node = bfsTree[node])
			minimumCapacity = min(minimumCapacity, capacity[bfsTree[node]][node] - flow[bfsTree[node]][node]);

		return minimumCapacity;
	}

	void changeCapacities(int minimumCapacity){

		int node;
		for(node = sink; node != source; node = bfsTree[node]){

			flow[bfsTree[node]][node] += minimumCapacity;
			flow[node][bfsTree[node]] -= minimumCapacity;
		}
	}

	int getMaxFlow(){

		int maxFlow = 0, minimumCapacity;

		while(BFS(source, sink))
			for(const int &adjNode : adjList[sink])
				if(capacity[adjNode][sink] != flow[adjNode][sink] and seen[adjNode]){

					bfsTree[sink] = adjNode;
					minimumCapacity = getMinimumCapacity();
					changeCapacities(minimumCapacity);
					maxFlow += minimumCapacity;
				}

		return maxFlow;
	}
};


int main(){

    Graph graph("maxflow.in");

    ofstream fout("maxflow.out");
    fout << graph.getMaxFlow();
}