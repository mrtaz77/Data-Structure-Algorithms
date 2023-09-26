#include <bits/stdc++.h>
using namespace std;

void print(int *arr,int start,int end){
    for(int i = start; i <= end; i++)cout<<arr[i]<<" "; 
    cout<<"\n";
}

void mergeHelper(int *a,int start,int end){
    int mid = (start+end)/2;
    int *left = new int[mid-start+1],*right = new int[end-mid]; 
    int i = 0,l = 0,r = 0;

    for(i = start; i <= mid; i++)left[l++] = a[i];
    for(i = mid+1; i <= end; i++)right[r++] = a[i];
    i = start;

    int p1 = 0,p2 = 0;

    while(p1 < l && p2 < r){
        if(left[p1] <= right[p2])a[i++] = left[p1++];
        else a[i++] = right[p2++];
    } 
    if(p2 < r)while(p2 < r)a[i++] = right[p2++];
    else if(p1 < l)while(p1 < l)a[i++] = left[p1++];
    delete[] left,right;
}

void mergeSort(int *a,int start,int end){
    if(end == start+1){
        if(a[start] > a[end]){
            int temp = a[start];
            a[start] = a[end];
            a[end] = temp;
            return;
        }
    }
    else if(end > start+1){
        int mid = (start+end)/2;
        mergeSort(a,start,mid);
        mergeSort(a,mid+1,end);
        mergeHelper(a,start,end);
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
    int n = 29;
    int *a = new int[n];
    int i = 0;
    string myText;
    ifstream MyReadFile("input.txt");
    clock_t time_of_file_read = clock();
    while (i < n && getline(MyReadFile, myText))a[i++] = (atoi(myText.c_str()));
    cout<<"Time of reading file "<<float(clock() - time_of_file_read) / CLOCKS_PER_SEC << " seconds\n";
    MyReadFile.close();
    clock_t time_of_sort = clock();
    mergeSort(a,0,n-1);
    cout << "Sorting " << n << " numbers using mergeSort takes "<< float(clock() - time_of_sort) / CLOCKS_PER_SEC << " seconds\n";
    print(a,0,n);
    delete []a;
}