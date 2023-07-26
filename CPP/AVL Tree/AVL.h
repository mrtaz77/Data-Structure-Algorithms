#include<bits/stdc++.h>
using namespace std;
template<typename E>
class AVL{
    AVLNode<E>* root;

    AVLNode<E>* rightRot(AVLNode<E>* root){
        AVLNode<E>* prevRoot = root;
        AVLNode<E>* newRoot = root->left();
        AVLNode<E>* newRootRight = root->left()->right();

        prevRoot = prevRoot->setLeft(newRootRight);
        newRoot = newRoot->setRight(prevRoot);

        root = newRoot;
        return root;
    }

    AVLNode<E>* leftRot(AVLNode<E>* root){
        AVLNode<E>* prevRoot = root;
        AVLNode<E>* newRoot = root->right();
        AVLNode<E>* newRootLeft = root->right()->left();

        prevRoot = prevRoot->setRight(newRootLeft);
        newRoot = newRoot->setLeft(prevRoot);

        root = newRoot;
        return root;
    }

    AVLNode<E>* leftRightRot(AVLNode<E>* root){
        root = root->setLeft(leftRot(root->left()));
        return rightRot(root);
    }

    AVLNode<E>* rightLeftRot(AVLNode<E>* root){
        root = root->setRight(rightRot(root->right()));
        return leftRot(root);
    }

    AVLNode<E>* balance(AVLNode<E>* root){
        if(root == NULL)return NULL;
        int leftH = maxHeight(root->left());
        int rightH = maxHeight(root->right());
        if(abs(leftH - rightH) <= 1)return root;
        else{
            if(leftH > rightH + 1){
                int leftLeftH = maxHeight(root->left()->left());
                int leftRightH = maxHeight(root->left()->right());
                if(leftLeftH > leftRightH)return rightRot(root);
                else return leftRightRot(root);
            }
            else{
                int rightLeftH = maxHeight(root->right()->left());
                int rightRightH = maxHeight(root->right()->right());
                if(rightRightH > rightLeftH)return leftRot(root);
                else return rightLeftRot(root);
            }
        }
    }
public:
    AVL(){
        root = NULL;
    }

    AVL(E element){
        root = new AVLNode<E>(element);
    }

    ~AVL(){
        delete root;
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
            string str = to_string(root->element());
            return inOrder(root->left())+str+" "+inOrder(root->right());
        }
    }

    string preOrder(AVLNode<E>* root){
        if(root == NULL)return "";
        else{
            string str = to_string(root->element());
            return str+" "+preOrder(root->left())+preOrder(root->right());
        }
    }

    string postOrder(AVLNode<E>* root){
        if(root == NULL)return "";
        else{
            string str = to_string(root->element());
            return postOrder(root->left())+postOrder(root->right())+str+" ";
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
                string str = to_string(temp->element());
                level += str+" ";
                if(temp->left() != NULL)q.add(temp->left());
                if(temp->right() != NULL)q.add(temp->right());
            }
            return level;
        }
    }

    string show(AVLNode<E>* root){
        if(root==NULL)return "";
        else{
            string str = to_string(root->element());
            if(root->left() != NULL || root->right() != NULL){
                return str+"("+show(root->left())+","+show(root->right())+")";
            }
            else return str;
        }
    }

    AVLNode<E>* insert(AVLNode<E>* root,E element){
        if(root==NULL)return new AVLNode<E>(element);
        else if(root->element() <= element)root = root->setRight(insert(root->right(),element));
        else root = root->setLeft(insert(root->left(),element));
        root = balance(root);
        return root;    
    }

    AVLNode<E>* erase(AVLNode<E>* root,E element){
        if(root==NULL)return NULL;
        else if(root->element() < element)root = root->setRight(erase(root->right(),element));
        else if(root->element() > element)root = root->setLeft(erase(root->left(),element));
        else{
            if(root->left() == NULL && root->right() == NULL)root = NULL;
            else if(root->right() == NULL)root = root->left();
            else if(root->left() == NULL)root = root->right();
            else{
                AVLNode<E>* inSuccessor = root->right();    
                while(inSuccessor->left() != NULL)inSuccessor = inSuccessor->left();
                root = root->setElement(inSuccessor->element());
                root = root->setRight(erase(root->right(),inSuccessor->element()));
            }
        }
        root = balance(root);
        return root;
    }

    bool find(AVLNode<E>* root,E element) {
        if(root == NULL)return false;
        else if(root->element() == element)return true;
        else if(root->element() < element)return find(root->right(),element);
        else find(root->left(),element);
    }
};