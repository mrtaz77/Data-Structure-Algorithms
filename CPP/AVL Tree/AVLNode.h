#include<bits/stdc++.h>
using namespace std;

template<typename E>
class AVLNode{
    E it;
    AVLNode<E>* lc;
    AVLNode<E>* rc;
    int h;
public:
    AVLNode(){
        lc = rc = NULL;
        h = 0;
    }

    AVLNode(E it,AVLNode<E>* lc=NULL,AVLNode<E>* rc=NULL){
        this->it = it;
        this->lc = lc;
        this->rc = rc;
        h = 1;
    }

    AVLNode(const AVLNode<E>& avl){
        it = avl->it;
        left = avl->lc;
        right = avl->rc;
        h = avl->h;
    }

    ~AVLNode(){
        delete lc;
        delete rc;
        h = 0;
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

    inline int height()const { return this == NULL ? 0 : h;}
    AVLNode<E>* setHeight(int height){
        this->h = height;
        return this;
    }

    AVLNode<E>* operator =(const AVLNode<E>* node){
        this->it = node->it;
        this->lc = node->lc;
        this->rc = node->rc;
        this->height = node->height;
        return this;
    }
};