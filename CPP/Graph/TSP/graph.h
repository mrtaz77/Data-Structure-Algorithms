#define MAXG 1e17
#include<bits/stdc++.h>
using namespace std;


class Graph{
    int V;
    long double **adj;

public:

    Graph(int V) {
        this->V = V;
        adj = new long double*[V];
        for (int i = 0; i < V; i++){
            adj[i] = new long double[V];
        }

        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                if(i == j)adj[i][j] = 0;
                else adj[i][j] = MAXG;
            }
        }
    }

    ~Graph() {
        for(int i = 0; i < V; i++){
            delete [] adj[i];
        }
        delete [] adj;
        V = 0;
    }

    Graph(const Graph& g){
        this->V = g.V;
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                this->adj[i][j] = g.adj[i][j];
            }
        }
    }



    int inline getV() const { return V; }


    void addEdge(int u,int v,long double w=1.0){
        adj[u][v] = w;
    }

    long double edgeWeight(int u,int v){
        return adj[u][v];
    }

    void rmEdge(int u,int v){
        adj[u][v] = MAXG;
    }

    Graph& operator=(const Graph g){
        this->V = g.V;
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                this->adj[i][j] = g.adj[i][j];
            }
        }
        return *this;
    }



    friend ostream & operator<<(ostream &out,const Graph& g);
};

ostream & operator<<(ostream &out,const Graph& g){
    for (int i = 0;i < g.getV();i++){
        for (int j = 0; j < g.getV() ; j++) {
            out << g.adj[i][j]<<" " ;
        }
        out<<endl;
    }
    return out;
}