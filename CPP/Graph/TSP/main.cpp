#define vertexCount 20
#include<bits/stdc++.h>
#include"GraphUtil.h"
using namespace std;

int main(){
    srand(20);
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int t;

    cin >> t;

    long double *exactTour = new long double[t];
    long double *approxTour = new long double[t];

    for(int i = 0; i < t; i++){
        Graph g = Create_Random_Graph(vertexCount);
        // cout<<g;

        auto bitTour = Exact_TSP(g);
        exactTour[i] = Calculate_Tour_Length(g,bitTour); 
        auto appTour = Metric_Approximation_TSP(g);
        approxTour[i] = Calculate_Tour_Length(g,appTour);

        // for(int i = 0; i < bitTour.size(); i++){
        //     cout<<bitTour[i];
        //     if(i != bitTour.size() -1)cout<<" -> ";
        // }
        // cout<<endl;

        // for(int i = 0; i < appTour.size(); i++){
        //     cout<<appTour[i];
        //     if(i != appTour.size() -1)cout<<" -> ";
        // }
        // cout<<endl;

        cout <<"("<<i+1<<", " <<approxTour[i]/exactTour[i]<<")" << endl;
        cout<<endl;
    }
    delete approxTour;
    delete exactTour;
}