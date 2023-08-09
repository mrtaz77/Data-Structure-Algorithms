#include<bits/stdc++.h>
using namespace std;

template<typename E>
class BinNode{
    E it;
    int deg;
    BinNode<E>* p;
    BinNode<E>* c;
    BinNode<E>* s;

public:
    BinNode(){
        p = c = s = NULL;
        deg = -1;
    }

    BinNode(E it,int deg=0,BinNode<E>* p=NULL,BinNode<E>* c=NULL,BinNode<E>* s=NULL){
        this->it = it;
        this->p = p;
        this->c = c;
        this->s = s;
        this->deg = deg;
    }

    BinNode(const BinNode<E>& bin){
        it = bin->it;
        p = bin->p;
        c = bin->c;
        s = bin->s;
        deg = bin->deg;
    }

    ~BinNode(){
        delete p;
        delete c;
        delete s;
        deg = -1;
    }

    inline E element() const{return it;}
    BinNode<E>* setElement(const E it){
        this->it = it;
        return this;
    } 

    inline BinNode<E>* parent() const{return p;}
    BinNode<E>* setParent(BinNode<E>* p){
        this->p = p;
        return this;
    }

    inline BinNode<E>* child() const{return c;}
    BinNode<E>* setChild(BinNode<E>* c){
        this->c = c;
        return this;
    }

    inline BinNode<E>* sibling() const{return s;}
    BinNode<E>* setSibling(BinNode<E>* s){
        this->s = s;
        return this;
    }

    inline int degree() const{return this == NULL ?-1:deg;}
    BinNode<E>* setDegree(int d){
        this->deg = d;
        return this;
    }

    BinNode<E>* set(BinNode<E>* node){
        this->s = node->s;
        this->c = node->c;
        this->p = node->p;
        this->it = node->it;
        this->deg = node->deg;
        return this;
    }

    BinNode<E>* operator =(const BinNode<E>* node){
        this->s = node->s;
        this->c = node->c;
        this->p = node->p;
        this->it = node->it;
        this->deg = node->deg;
        return this;
    }

    BinNode<E>* unionNode(BinNode<E>* node) {
        if(node == NULL)return this;
        if(this == NULL)return node;
        auto greater = (it >= node->it) ? this : node;
        auto smaller = (it < node->it) ? this : node ;
        cout<<greater->it<<" "<<smaller->it<<endl;
        cout<<boolalpha<<(greater->child() == NULL)<<" "<<(smaller->child() == NULL)<<endl;

        if(smaller->child() != NULL)greater = greater->setSibling(smaller->child());
        greater = greater->setParent(smaller);
        smaller = smaller->setChild(greater);
        cout<<greater->it<<" "<<smaller->it<<endl;
        smaller->deg += 1;

        cout<<element()<<endl;
        if(parent() != NULL)cout<<"Parent : "<<parent()->element()<<endl;
        if(child() != NULL)cout<<"Child :"<<child()->element()<<endl;
        cout<<smaller->element()<<endl;
        cout<<smaller->child()->element()<<endl;
        cout<<"================================================================\n";
        
        // set(smaller);
        cout<<smaller->element()<<endl;
        cout<<smaller->child()->element()<<endl;
        
        cout<<element()<<endl;
        
        if(parent() != NULL)cout<<"Parent : "<<parent()->element()<<endl;
        if(child() != NULL)cout<<"Child : "<<child()->element()<<endl;
        cout<<"================================================================\n";
        
        // cout<<greater->parent()->element()<<" "<<element()<<endl;
        cout<<degree()<<endl;

        return smaller;
    }

    string printNode(){
        string out = "";
        int level = 0;
        queue<pair<BinNode<E>*,int>> q;
        q.push({this,level});
        while(!q.empty()){
            level = q.front().second;
            out+= "Level "+to_string(level)+": ";
            cout<<"Level "+to_string(level)+": ";
            while(!q.empty() && q.front().second == level){
                out += to_string(q.front().first->element())+" ";
                cout<<q.front().first->element()<<" ";
                if(q.front().first->child()!=NULL){
                    BinNode<E>* node = q.front().first->child();
                    while(node != NULL){
                        q.push({node,level+1});
                        node = node->sibling();
                    }
                }
                q.pop();
            }
            cout<<endl;
            out+="\n";
        }
        return out;
    }
};