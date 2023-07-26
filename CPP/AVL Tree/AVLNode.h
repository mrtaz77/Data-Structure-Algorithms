#include<bits/stdc++.h>
using namespace std;

template<typename E>
class AVLNode{
    E it;
    AVLNode<E>* lc;
    AVLNode<E>* rc;
public:
    AVLNode(){
        lc = rc = NULL;
    }

    AVLNode(E it,AVLNode<E>* lc=NULL,AVLNode<E>* rc=NULL){
        this->it = it;
        this->lc = lc;
        this->rc = rc;
    }

    AVLNode(const AVLNode<E>& avl){
        it = avl->it;
        left = avl->lc;
        right = avl->rc;
    }

    ~AVLNode(){
        delete lc;
        delete rc;
    }

    inline E element() const{return it;}
    AVLNode<E>* setElement(const E it){
        this->it = it;
        return this;
    }

    inline AVLNode<E>* left() const{return lc;}
    AVLNode<E>* setLeft(AVLNode<E>* lc){
        this->lc = lc;
        return this;
    }

    inline AVLNode<E>* right() const{ return rc; }
    AVLNode<E>* setRight(AVLNode<E>* rc){
        this->rc = rc;
        return this;
    }

    AVLNode<E>* operator =(const AVLNode<E>* node){
        this->it = node->it;
        this->lc = node->lc;
        this->rc = node->rc;
        return this;
    }
};