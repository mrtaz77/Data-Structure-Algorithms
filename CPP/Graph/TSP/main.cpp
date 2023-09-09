#define V 20
#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

int main(){
    srand(time(NULL));
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int t;

    cin >> t;

    long double *exactTour = new long double[t];
    long double *approxTour = new long double[t];

    for(int i = 0; i < t; i++){
        Graph g = Create_Random_Graph(V);
        // cout<<g;

        exactTour[i] = Exact_TSP(g);
        approxTour[i] = Metric_Approximation_TSP(g);
        cout <<"("<<i+1<<", " <<approxTour[i]/exactTour[i]<<")" << endl;
        // cout<<endl;
    }
}