#include <bits/stdc++.h>

using namespace std;

class Graph{

	struct Edge{
		int u, v;

		bool operator !=(const Edge &other){
			return this->u != other.u && this->v != other.v;
		}
	};

    int V, E;
    int source;
    vector < vector <int> > adjList;
	vector <int> lowlink, depth;
	vector < set <int> > biconnected_components;

	stack <Edge> Stack;

public:

    Graph(const char *Filename) {

        ifstream fin(Filename);

        fin >> this->V >> this->E;
        --this->source;

        this->adjList.resize(this->V);
        this->lowlink.resize(this->V);
        this->depth.resize(this->V, 0);
        this->biconnected_components.reserve(this->V);

        for(int e = 0; e < this-> E; ++e){

            int from, to;
            fin >> from >> to;

            --from; --to;

            this->adjList[from].push_back(to);
            this->adjList[to].push_back(from);
        }

    }


	void cacheBCCs(const Edge &edge){

		Edge stackEdge;

		set  <int> BC;

		do{

			stackEdge = Stack.top();
			Stack.pop();

			BC.insert(stackEdge.u);
			BC.insert(stackEdge.v);

		}while(stackEdge != edge);
		biconnected_components.push_back(BC);
	}

	void DFS(int node, int dad, int d){

		depth[node] = lowlink[node] = d;

		for(const int &nextNode : adjList[node])
			if(nextNode != dad){
				if(depth[nextNode] == 0){

					Stack.push({node, nextNode});
					DFS(nextNode, node, d + 1);

					lowlink[node] = min(lowlink[node], lowlink[nextNode]);

					// if(lowlink[nextNode] > depth[node]){ // bridges

					// }

					if(lowlink[nextNode] >= depth[node]){ // articulation point
						cacheBCCs({node, nextNode});
					}
				}
				else lowlink[node] = min(lowlink[node], depth[nextNode]);
			}
	}

	vector < set  <int> > getBCCs() {

		for(int node = 0; node < V; ++node)
			if(depth[node] == 0){
				DFS(node, -1, 1);
			}

		return biconnected_components;
	}
};

int main(){

    Graph graph("biconex.in");

	vector < set  <int> > ans = graph.getBCCs();

    ofstream fout("biconex.out");

	fout << ans.size() << '\n';
	for(int bcc = 0; bcc < (int)ans.size(); ++bcc){
		for(const int &node : ans[bcc]){
			fout << node + 1 << ' ';
		}
		fout << '\n';
	}
}