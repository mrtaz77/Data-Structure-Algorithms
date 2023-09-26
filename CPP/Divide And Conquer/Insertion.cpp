#include <bits/stdc++.h>
using namespace std;

void print(int *arr,int start,int end){
    for(int i = start; i <= end; i++)cout<<arr[i]<<" "; 
    cout<<"\n";
}

void insertionSort(int* a,int n){
    int i,j,pivot;
    for(int i = 1; i < n; i++){
        pivot = a[i];
        j = i-1;

        while(j>=0 && a[j] > pivot){
            a[j+1] =a[j];
            j--;
        }
        a[j+1] = pivot;
    }
}


int main(){
    // int n;
    // cin >> n;
    // int *stocks;
    // stocks = new int[n];

    // for(int i = 0; i < n; i++)cin >>stocks[i];

    // mergeSort(stocks,0,n-1);

    // print(stocks,0,n-1);
    int n = 1000000;
    int *a = new int[n];
    int i = 0;
    string myText;
    ifstream MyReadFile("numbers.txt");
    clock_t time_of_file_read = clock();
    while (i < n && getline(MyReadFile, myText))a[i++] = (atoi(myText.c_str()));
    cout<<"Time of reading file "<<float(clock() - time_of_file_read) / CLOCKS_PER_SEC << " seconds\n";
    MyReadFile.close();
    clock_t time_of_sort = clock();
    insertionSort(a,n);
    cout << "Sorting " << n << " numbers using insertion Sort takes "<< float(clock() - time_of_sort) / CLOCKS_PER_SEC << " seconds\n";
    print(a,0,10);
}