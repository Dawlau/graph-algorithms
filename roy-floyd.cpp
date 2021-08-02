#include <bits/stdc++.h>

using namespace std;

/*
 *
 * Input: cost matrix (0 means that there is no edge between two nodes)
 * Output: shortest paths matrix (0 means that there is no edge between two nodes)
 *
 */

class Graph {

    vector < vector <int> > costMatrix;
    int V;

public:

    static const int Inf = INT_MAX;

    explicit Graph(const char *Filename) {

        ifstream fin(Filename);

        int nodes;
        fin >> nodes;

        this->V = nodes;
        this->costMatrix.resize(nodes, vector <int>(nodes) );

        for(int i = 0; i < nodes; ++i)
            for(int j = 0; j < nodes; ++j) {
                fin >> this->costMatrix[i][j];

                if(this->costMatrix[i][j] == 0) // in case there is no edge from i to j
                    this->costMatrix[i][j] = Graph::Inf;
            }
    }


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

    Graph graph("royfloyd.in");

    ofstream fout("royfloyd.out");
    fout << graph.Roy_Floyd() << '\n';
}