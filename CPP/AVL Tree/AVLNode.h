#include<bits/stdc++.h>
using namespace std;

template<typename E>
class AVLNode{
    E element;
    AVLNode* left;
    AVLNode* right;
public:
    AVLNode(){
        left = right = NULL;
    }

    AVLNode(E element,AVLNode<E>* left=NULL,AVLNode<E>* right=NULL){
        this->element = element;
        this->left = left;
        this->right = right;
    }

    AVLNode(const AVLNode<E>& avl){
        element = avl->element;
        left = avl->left;
        right = avl->right;
    }

    ~AVLNode(){
        delete left;
        delete right;
    }

    inline E& element() const{return element;}
    AVLNode<E>& setElement(const E& element){
        this->element = element;
        return this;
    }

    inline AVLNode<E>& left() const{return left;}
    AVLNode<E>& setLeft(AVLNode<E>* left){
        this->left = left;
        return this;
    }

    inline AVLNode<E>& right() const{return right;}
    AVLNode<E>& setRight(AVLNode<E>* right){
        this->right = right;
        return this;
    }
};