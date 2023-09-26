#include <bits/stdc++.h>
using namespace std;
void print(int *arr,int start,int end){
    for(int i = start; i <= end; i++)cout<<arr[i]<<" "; 
    cout<<"\n";
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int* a, int low,int high){
    int pivot = a[high];
    int i = low-1;

    for(int j = low; j < high; j++){
        if(a[j] < pivot){
            i++;
            swap(a+i,a+j);
        }
    }
    swap(a+(i+1),a+high);
    return i+1;
}

int randomPartition(int* a,int low,int high){
    srand(time(NULL));
    int random = low + rand() % (high - low);
    swap(a+random, a+high);
    return partition(a,low,high);
}

void quickSort(int*a ,int low,int high){
    while(low < high){
        int pi = randomPartition(a,low,high);

        if(pi - low < high - pi){
            quickSort(a,low,pi-1);
            low = pi + 1;
        }

        else{
            quickSort(a,high,pi+1);
            high = pi-1;
        }
    }
}

int main(){
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
    quickSort(a,0,n-1);
    cout << "Sorting " << n << " numbers using quickSort takes "<< float(clock() - time_of_sort) / CLOCKS_PER_SEC << " seconds\n";
    print(a,0,10);
}