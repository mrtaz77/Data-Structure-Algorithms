#include<bits/stdc++.h>
#include"BinNode.h"
using namespace std;

template<typename E>
class BinMinHeap{
    vector<BinNode<E>*> heap;

public:
    BinMinHeap(){
    }

    BinMinHeap(BinNode<E>* node){
        heap.push_back(node);
    }


    ~BinMinHeap<E>(){
        for (BinNode<E>* node : *heap) {
            delete node;  
        }
        delete heap;  
    }

    int len(){ return heap.size(); }

    void Union(BinMinHeap<E>* other){
        cout<<"In Union"<<endl;
        if(other == NULL) return;
        BinMinHeap<E>* newHeap = new BinMinHeap<E>();
        int i = 0 , j = 0;
        while(i < heap.size() || j < other->heap.size()){
            if(heap[i]->degree() >= other->heap[j]->degree()){
                newHeap->heap.push_back(other->heap[j++]);
            }
            if(heap[i]->degree() <= other->heap[j]->degree()){
                newHeap->heap.push_back(heap[i++]);
            }
        }
        cout<<"New Heap init done : size "<<newHeap->heap.size()<<endl;

        i = 0;
        for(; i < newHeap->heap.size() - 2 ;i++){
            cout<<"In first for loop\n";
            int curDegree = newHeap->heap[i]->degree();
            int nextDegree = newHeap->heap[i+1]->degree();
            int nextNextDegree = newHeap->heap[i+2]->degree();

            if(curDegree == nextDegree && nextDegree != nextNextDegree){
                newHeap->heap[i+1] = newHeap->heap[i]->unionNode(newHeap->heap[i+1]);
                newHeap->heap.erase(newHeap->heap.begin()+i);
                i--;
            }
            cout<<i<<" "<<newHeap->heap.size()<<endl;
        }

        


        if(i == (newHeap->heap.size() - 2)){
            int curDegree = newHeap->heap[i]->degree();
            int nextDegree = newHeap->heap[i+1]->degree();
            cout<<curDegree<<" "<<nextDegree<<endl;

            if(curDegree == nextDegree){
                newHeap->heap[i+1] = newHeap->heap[i]->unionNode(newHeap->heap[i+1]);
                newHeap->heap.erase(newHeap->heap.begin()+i);
            }
        }
        cout<<"Insertion Complete"<<endl;

        
        this->heap = newHeap->heap;
    }

    E findMin(){
        E min = heap[0]->element();
        for (int i = 1; i < heap.size(); i++){
            if(min>heap[i]->element())min = heap[i]->element();
        }
        return min;
    }

    E extractMin(){
        cout<<"Milking min"<<endl;
        int minIndex = 0;
        for (int i = 1; i < heap.size(); i++){
            if(heap[minIndex]->element()>heap[i]->element())minIndex = i;
        }
        cout<<"Milked minIndex\n";
        E min = heap[minIndex]->element();
        BinMinHeap<E>* newHeap = new BinMinHeap<E>();
        BinNode<E>* lc = heap[minIndex]->child();
        heap[minIndex]->setChild(NULL);
        while(lc!=NULL){
            auto temp = lc;
            lc = lc->sibling();
            temp = temp->setParent(NULL);
            temp = temp->setSibling(NULL);
            cout<<temp->printNode()<<endl;
            if(newHeap->len()==0)newHeap->heap.push_back(temp);
            else newHeap->Union(new BinMinHeap<E>(temp));
            cout<<"Printing New MinHeap..."<<endl;
            cout<<newHeap->print()<<endl;
        }
        
        heap.erase(heap.begin()+minIndex);
        Union(newHeap);
        return min;
    }

    void insert(E it){
        cout<<"Inserting "<<it<<endl;
        auto newHeap = new BinMinHeap<E>();
        newHeap->heap.push_back(new BinNode<E>(it));
        cout<<"Inserted "<<it<<" in new Heap"<<endl;
        if(heap.size() == 0)heap = newHeap->heap;
        else{ 
            Union(newHeap);
        }
    }

    string print(){
        cout<<"Printing Binomial Heap..."<<heap.size()<<endl;
        string out = "";
        out += "Printing Binomial Heap...\n";
        for(int i = 0; i < heap.size(); i++){
            cout<<"Binomial Tree, B"<<heap[i]->degree()<<" "<<heap[i]->element()<<"\n";
            out += "Binomial Tree, B"+to_string(heap[i]->degree())+"\n";
            out+= heap[i]->printNode();
        }
        return out;
    }
};