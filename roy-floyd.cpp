#include <bits/stdc++.h>

using namespace std;

class Graph {

    vector < vector <int> > costMatrix;
    int V;

public:

    static const int Inf = INT_MAX;

    friend ifstream& operator >> (ifstream &in, Graph &graph);

    vector < vector <int> > Roy_Floyd() {

        int n = this->V;

        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    if (i != j and costMatrix[i][k] != Graph::Inf and costMatrix[k][j] != Graph::Inf and this->costMatrix[i][j] > this->costMatrix[i][k] + this->costMatrix[k][j])
                        this->costMatrix[i][j] = this->costMatrix[i][k] + this->costMatrix[k][j];

        return this->costMatrix;
    }
};

ifstream &operator>>(ifstream &in, Graph &graph) {

    int n;
    in >> n;

    graph.V = n;
    graph.costMatrix.resize(n, vector <int>(n) );

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            in >> graph.costMatrix[i][j];

            if(graph.costMatrix[i][j] == 0) // in case there is no edge from i to j
                graph.costMatrix[i][j] = Graph::Inf;
        }

    return in;
}

ofstream &operator<<(ofstream &out, const vector < vector <int> > &ans) {

    int n = (int)ans.size();

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j)
            if(ans[i][j] == Graph::Inf)
                out << 0 << ' ';
            else
                out << ans[i][j] << ' ';
        out << '\n';
    }

    return out;
}


int main(){

    ifstream fin("royfloyd.in");
    ofstream fout("royfloyd.out");

    Graph graph;
    fin >> graph;

    fout << graph.Roy_Floyd() << '\n';
}