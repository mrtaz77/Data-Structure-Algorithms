#include<bits/stdc++.h>
#include"AVLNode.h"
template<typename E>
class AVL{
    AVLNode<E>* root;
    int nodeCount;
public:
    AVL(){
        root = new AVLNode<>();
        nodeCount = 0;
    }

    AVL(E element){
        root = new AVLNode<>(element);
        nodeCount = 1;
    }

    ~AVL(){
        delete root;
        nodeCount = 0;
    }

    bool isLeaf(AVLNode<E>* root,E element){
        if(root == NULL)return false;
        else if(root->element() == element)return root->left() == NULL && root->right() == NULL;
        else if(root->element() < element)return isLeaf(root->right(), element);
        else return isLeaf(root->left(), element);
    }

    int maxHeight(AVLNode<E>* root){
        if(root == NULL)return -1;
        else return 1 + max(maxHeight(root->left()),maxHeight(root->right()));
    }

    int height(AVLNode<E>* root,E element){
        if(root == NULL)return -1;
        else if(root->element() == element)return 0;
        else if(root->element() < element)return height(root->right(), element);
        else return height(root->left(), element);
    }

    string inOrder(AVLNode<E>* root){
        if(root == NULL)return "";
        else{
            return inOrder(root->left())+root->element()+" "+inOrder(root->right());
        }
    }

    string preOrder(AVLNode<E>* root){
        if(root == NULL)return "";
        else{
            return root->element()+" "+preOrder(root->left())+preOrder(root->right());
        }
    }

    string postOrder(AVLNode<E>* root){4
        if(root == NULL)return "";
        else{
            return postOrder(root->left())+postOrder(root->right())+root->element()+" ";
        }
    }

    string levelOrder(AVLNode<E>* root){
        if(root == NULL)return "";
        else{
            string level = "";
            queue<AVLNode<E>*> q;
            q.push(root);
            while(!q.isEmpty()){
                AVLNode<E> *temp = q.pop();
                level += temp->element()+" ";
                if(temp->left() != NULL)q.add(temp->left());
                if(temp->right() != NULL)q.add(temp->right());
            }
            return level;
        }
    }

    friend ostream& operator<<(ostream& os,const AVLNode<E>* root){
        if(root==NULL)os<<"";
        else{
            if(root->left() != NULL || root->right() != NULL)os<<root->element()<<"("<<root->left()<<","<<root->right()<<")";
            else os<<root->element();
        }
        return os;
    }

    AVLNode<E>* insert(AVLNode<E>* root,E element){
        if(root==NULL)return new AVLNode<E>(root);
        else if(root->element() <= element)root->setRight(insert(root->right(),element));
        else root->setLeft(insert(root->left,element));
        return root;    
    }

    AVLNode<E>* delete(AVLNode<E>* root,E element){
        if(root==NULL)return NULL;
        else if(root->element() < element)root.setRight(delete(root->right(),element));
        else if(root->element() > element)root.setLeft(delete(root->left(),element));
        else{
            if(root->left() == NULL && root->right() == NULL)return NULL;
            else if(root->right() == NULL)return root->left();
            else if(root->left() == NULL)return root->right();
            else{
                AVLNode<E>* inSuccessor = root->right();    
                while(inSuccessor->left() != NULL)inSuccessor = inSuccessor->left();
                root.setElement(inSuccessor->element);
                root.setRight(delete(root->right(),inSuccessor->element));
            }
        }
        return root;
    }

};