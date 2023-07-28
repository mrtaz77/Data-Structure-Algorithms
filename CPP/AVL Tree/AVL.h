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
        
        prevRoot = prevRoot->setHeight(1+max(prevRoot->left()->height(),prevRoot->right()->height()));
        newRoot = newRoot->setHeight(1+max(newRoot->left()->height(),newRoot->right()->height()));	

        root = newRoot;
        return root;
    }

    AVLNode<E>* leftRot(AVLNode<E>* root){
        AVLNode<E>* prevRoot = root;
        AVLNode<E>* newRoot = root->right();
        AVLNode<E>* newRootLeft = root->right()->left();

        prevRoot = prevRoot->setRight(newRootLeft);
        newRoot = newRoot->setLeft(prevRoot);

        prevRoot = prevRoot->setHeight(1+max(prevRoot->left()->height(),prevRoot->right()->height()));
        newRoot = newRoot->setHeight(1+max(newRoot->left()->height(),newRoot->right()->height()));	

        root = newRoot;
        return root;
    }

    AVLNode<E>* leftRightRot(AVLNode<E>* root){
        root = root->setLeft(leftRot(root->left()));
        root = root->setHeight(1+max(root->left()->height(),root->right()->height()));
        return rightRot(root);
    }

    AVLNode<E>* rightLeftRot(AVLNode<E>* root){
        root = root->setRight(rightRot(root->right()));
        root = root->setHeight(1+max(root->left()->height(),root->right()->height()));
        return leftRot(root);
    }

    AVLNode<E>* balance(AVLNode<E>* root){
        if(root == NULL)return NULL;
        int leftH = root->left()->height();
        int rightH = root->right()->height();
        if(abs(leftH - rightH) <= 1)return root;
        else{
            if(leftH > rightH + 1){
                int leftLeftH = root->left()->left()->height();
                int leftRightH = root->left()->right()->height();
                if(leftLeftH >= leftRightH)return rightRot(root);
                else  return leftRightRot(root);
            }
            else{
                int rightLeftH = root->right()->left()->height();
                int rightRightH = root->right()->right()->height();
                if(rightRightH >= rightLeftH)return leftRot(root);
                else return rightLeftRot(root);
            }
        }
        return root;
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
        return root->height();
    }

    int depth(AVLNode<E>* root,E element){
        if(root == NULL)return -1;
        else if(root->element() == element)return 0;
        else if(root->element() < element)return 1+depth(root->right(), element);
        else return 1+depth(root->left(), element);
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
            // string str = to_string(root->element())+"["+to_string(root->height())+"]";
            if(root->left() != NULL || root->right() != NULL){
                return str+"("+show(root->left())+","+show(root->right())+")";
            }
            else return str;
        }
    }

    AVLNode<E>* insert(AVLNode<E>* root,E element){
        if(root==NULL)return new AVLNode<E>(element);
        else if(root->element() <= element){
            root = root->setRight(insert(root->right(),element));
            root = root->setHeight(1+max(root->right()->height(),root->left()->height()));
        }
        else {
            root = root->setLeft(insert(root->left(),element));
            root = root->setHeight(1+max(root->right()->height(),root->left()->height()));
        }
        root = balance(root);
        return root;    
    }

    AVLNode<E>* erase(AVLNode<E>* root,E element){
        if(root==NULL)return NULL;
        else if(root->element() < element){
            root = root->setRight(erase(root->right(),element));
        }
        else if(root->element() > element){
            root = root->setLeft(erase(root->left(),element));
        }
        else{
            if(root->left() == NULL && root->right() == NULL)root = NULL;
            else if(root->right() == NULL){
                root = root->left();
            }
            else if(root->left() == NULL){
                root = root->right();
            }
            else{
                AVLNode<E>* inSuccessor = root->right();    
                while(inSuccessor->left() != NULL)inSuccessor = inSuccessor->left();
                root = root->setElement(inSuccessor->element());
                root = root->setRight(erase(root->right(),inSuccessor->element()));
            }
        }
        if(root != NULL)root = root->setHeight(1+max(root->left()->height(),root->right()->height()));
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