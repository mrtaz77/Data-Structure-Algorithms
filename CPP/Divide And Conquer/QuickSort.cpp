#include <bits/stdc++.h>
using namespace std;
void print(int *arr,int start,int end){
    for(int i = start; i <= end; i++)cout<<arr[i]<<" "; 
    cout<<"\n";
}

void quickSort(int *arr,int start,int end){
    if(start < end){
        int pivot = arr[end];
        int p = start;
        for(int i = start; i < end;i++){
            if(arr[i] <= pivot){
                int temp = arr[i];
                arr[i] = arr[p];
                arr[p] = temp;
                p++;
            }
        }

        int temp = arr[p];
        arr[p] = arr[end];
        arr[end] = temp;
            
        quickSort(arr,0,p-1);
        quickSort(arr,p+1,end);
    }
}

int main(){
    int n = 1940;
    int *a = new int[n];
    int i = 0;
    string myText;
    ifstream MyReadFile("numbers.txt");
    clock_t time_of_file_read = clock();
    while (i < n && getline(MyReadFile, myText))a[i++] = (atoi(myText.c_str()));
    cout<<"Time of reading file "<<float(clock() - time_of_file_read) / CLOCKS_PER_SEC << " seconds\n";
    MyReadFile.close();
    clock_t time_of_sort = clock();
    quickSort(a,0,n-1);
    cout << "Sorting " << n << " numbers using quickSort takes "<< float(clock() - time_of_sort) / CLOCKS_PER_SEC << " seconds\n";
    print(a,0,10);
}